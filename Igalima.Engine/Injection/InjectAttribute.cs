using JetBrains.Annotations;

namespace Igalima.Engine.Injection;

[MeansImplicitUse(ImplicitUseKindFlags.Assign)]
[AttributeUsage(AttributeTargets.Property)]
public class InjectAttribute : Attribute
{
    public string? Name { get; }

    public InjectAttribute()
    {
    }

    public InjectAttribute(string name)
    {
        Name = name;
    }
}