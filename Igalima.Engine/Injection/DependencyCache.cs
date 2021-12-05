namespace Igalima.Engine.Injection;

public readonly struct DependencyCache
{
    public readonly string? Name;

    public readonly Type? Type;

    public DependencyCache(string? name)
    {
        Name = name;
        Type = null;
    }

    public DependencyCache(string? name, Type type)
    {
        Name = name;
        Type = type;
    }

    internal DependencyCache CreateWithType(Type type) => new(Name, type);
}