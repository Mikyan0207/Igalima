using JetBrains.Annotations;

namespace Igalima.Engine.Injection;

/// <summary>
///     Marks a method as an initialization method.
///     Allow automatic injection of dependencies via the parameters of the method at runtime.
/// </summary>
/// <remarks>
///     The initialization method can be asynchronous.
/// </remarks>
[MeansImplicitUse]
[AttributeUsage(AttributeTargets.Method)]
public class ResolveAttribute : Attribute
{
    /// <summary>
    ///     Indicates if a method supports nullable parameters.
    /// </summary>
    /// <remarks>
    ///     If a parameter is marked with ?, it will be considered as nullable.
    /// </remarks>
    public bool Nullable { get; }

    /// <summary>
    ///     Marks this method as an initializer for this class in the context of dependency injection.
    /// </summary>
    public ResolveAttribute()
    {
    }

    /// <summary>
    ///     Marks this method as an initializer for this class in the context of dependency injection.
    /// </summary>
    /// <param name="nullable">
    ///     If true, the dependency provider will pass a null value if the dependency cannot be resolved.
    /// </param>
    public ResolveAttribute(bool nullable)
    {
        Nullable = nullable;
    }
}