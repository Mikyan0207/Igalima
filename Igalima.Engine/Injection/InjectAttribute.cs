namespace Igalima.Engine.Injection;

[AttributeUsage(AttributeTargets.Parameter | AttributeTargets.Property | AttributeTargets.Field)]
public class InjectAttribute : Attribute
{
    public string? Name { get; private set; }

    public InjectAttribute()
    {
    }

    public InjectAttribute(string name)
    {
        Name = name;
    }
}