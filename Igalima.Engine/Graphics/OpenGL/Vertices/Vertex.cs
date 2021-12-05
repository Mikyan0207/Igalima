using System.Runtime.InteropServices;
using OpenTK.Graphics.OpenGL4;
using OpenTK.Mathematics;

namespace Igalima.Engine.Graphics.OpenGL.Vertices;

[StructLayout(LayoutKind.Sequential)]
public struct Vertex : IEquatable<Vertex>, IVertex
{
    [VertexField(2, VertexAttribPointerType.Float)]
    public Vector2 Position;

    [VertexField(4, VertexAttribPointerType.Float)]
    public Color4 Color;

    public override bool Equals(object? obj)
    {
        return obj is Vertex vertex && Equals(vertex);
    }

    public bool Equals(Vertex other)
    {
        return Position.Equals(other.Position) && Color.Equals(other.Color);
    }

    public static bool operator ==(Vertex left, Vertex right)
    {
        return left.Equals(right);
    }

    public static bool operator !=(Vertex left, Vertex right)
    {
        return !(left == right);
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Position, Color);
    }
}