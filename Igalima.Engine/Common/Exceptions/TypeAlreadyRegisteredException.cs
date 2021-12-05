using Igalima.Engine.Injection;

namespace Igalima.Engine.Common.Exceptions;

public class TypeAlreadyRegisteredException : Exception
{
    public TypeAlreadyRegisteredException(DependencyCache dependencyCache)
        : base($"An instance of the member ({dependencyCache}) has already been cached to the dependency container.")
    {
        
    }
}