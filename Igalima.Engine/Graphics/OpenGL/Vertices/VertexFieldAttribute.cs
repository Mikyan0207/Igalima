using OpenTK.Graphics.OpenGL4;

namespace Igalima.Engine.Graphics.OpenGL.Vertices;

[AttributeUsage(AttributeTargets.Field)]
public class VertexFieldAttribute : Attribute
{
    public int Count { get; init; }

    public VertexAttribPointerType Type { get; init; }

    public bool Normalized { get; init; }

    internal IntPtr Offset { get; set; }

    public VertexFieldAttribute(int count, VertexAttribPointerType type)
    {
        Count = count;
        Type = type;
    }

    public VertexFieldAttribute(int count, VertexAttribPointerType type, bool normalized)
    {
        Count = count;
        Type = type;
        Normalized = normalized;
    }
}