namespace Igalima.Engine.Common.Exceptions;

public class DependencyNotRegisteredException : Exception
{
    public DependencyNotRegisteredException(Type type, Type requestedType)
        : base($"The type {type} has a dependency on {requestedType}, but the dependency is not registered.")
    {
    }
}