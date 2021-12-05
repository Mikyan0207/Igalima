using System.ComponentModel.DataAnnotations;
using System.Diagnostics;
using System.Reflection;
using System.Runtime.ExceptionServices;
using Igalima.Engine.Common.Exceptions;
using Igalima.Engine.Common.Extensions;

namespace Igalima.Engine.Injection;

public class DependencyProvider
{
    private readonly IDictionary<DependencyCache, object> _dependencyCache = new Dictionary<DependencyCache, object>();

    public void Resolve<T>(T instance) where T : class
    {
        Resolve(instance.GetType(), instance);
        ResolveMethod(instance.GetType(), instance);
    }

    public void Register(object instance)
        => Register(instance.GetType(), default, instance);

    internal void Register(Type type, DependencyCache cache, object instance)
    {
        cache = cache.CreateWithType(type.GetUnderlyingNullableType() ?? type);

        var instanceType = instance.GetType();
        instanceType = instanceType.GetUnderlyingNullableType() ?? instanceType;

        if (cache.Type != null && !cache.Type.IsInstanceOfType(instance))
            throw new ArgumentException($"{instanceType} must be a subclass of {cache.Type}.", nameof(instance));

        if (_dependencyCache.TryGetValue(cache, out _))
            throw new TypeAlreadyRegisteredException(cache);

        _dependencyCache[cache] = instance;
    }

    internal object? Get(Type type, DependencyCache cache)
    {
        cache = cache.CreateWithType(type.GetUnderlyingNullableType() ?? type);

        return _dependencyCache.TryGetValue(cache, out var instance) ? instance : null;
    }

    internal void Resolve(Type type, object target)
    {
        var properties = type.GetProperties().Where(x => x.GetCustomAttribute<InjectAttribute>() != null);

        foreach (var property in properties)
        {
            if (!property.CanWrite)
                throw new PropertyNotWritableException(type, property.Name);

            var attribute = property.GetCustomAttribute<InjectAttribute>();
            Debug.Assert(attribute != null);

            var cache = new DependencyCache(attribute.Name);
            var dependency = GetDependency(property.PropertyType, cache);

            property.SetValue(target, dependency);
        }
    }

    internal void ResolveMethod(Type type, object target)
    {
        var methodsToResolve = type.GetMethods().Where(x => x.GetCustomAttribute<ResolveAttribute>() != null).ToArray();

        switch (methodsToResolve.Length)
        {
            case 0:
                break;
            case 1:
            {
                var method = methodsToResolve[0];

                var attribute = method.GetCustomAttribute<ResolveAttribute>();
                Debug.Assert(attribute != null);

                var parameters = method.GetParameters().Select(x => x.ParameterType)
                    .Select(t => GetDependency(t, type, attribute.Nullable || t.IsNullable())).ToArray();

                try
                {
                    var parametersArray = new object?[parameters.Length];
                    for (var i = 0; i < parameters.Length; i++)
                        parametersArray[i] = parameters[i];

                    method.Invoke(target, parametersArray);
                }
                catch (TargetInvocationException e)
                {
                    ExceptionDispatchInfo.Capture(e.InnerException ?? e).Throw();
                }
            } break;
            default:
                throw new InvalidOperationException(
                    $"The type {type} has more than one method marked with a {nameof(ResolveAttribute)}. Any given type may only have one such method.");
        }
    }

    internal object? GetDependency(Type type, Type requestedType, bool nullable)
    {
        var val = Get(type, default);

        if (val == null && !nullable)
            throw new DependencyNotRegisteredException(type, requestedType);

        return val;
    }

    internal object? GetDependency(Type type, DependencyCache cache)
    {
        return Get(type, cache);
    }
}