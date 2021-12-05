using System.Collections.Concurrent;
using System.Reflection;

namespace Igalima.Engine.Common.Extensions;

internal static class TypeExtensions
{
    private static readonly ConcurrentDictionary<Type, Type?> UnderlyingTypeCache = new();

    internal static AccessModifier GetAccessModifier(this MethodInfo method)
    {
        var modifiers = AccessModifier.None;

        if (method.IsPublic)
            modifiers |= AccessModifier.Public;
        if (method.IsAssembly)
            modifiers |= AccessModifier.Internal;
        if (method.IsFamily)
            modifiers |= AccessModifier.Protected;
        if (method.IsPrivate)
            modifiers |= AccessModifier.Private;
        if (method.IsFamilyOrAssembly)
            modifiers |= AccessModifier.Protected | AccessModifier.Internal;

        return modifiers;
    }

    internal static bool IsNullable(this Type type) => type.GetUnderlyingNullableType() != null;

    internal static Type? GetUnderlyingNullableType(this Type type)
    {
        // ReSharper disable once ConvertClosureToMethodGroup
        return !type.IsGenericType
            ? null
            : UnderlyingTypeCache.GetOrAdd(type, t => Nullable.GetUnderlyingType(t));
    }

    [Flags]
    internal enum AccessModifier
    {
        None = 0,
        Public = 1,
        Internal = 1 << 1,
        Protected = 1 << 2,
        Private = 1 << 3
    }
}