using System.Diagnostics;
using System.Reflection;
using System.Runtime.InteropServices;
using OpenTK.Graphics.OpenGL4;

// ReSharper disable StaticMemberInGenericType

namespace Igalima.Engine.Graphics.OpenGL.Vertices;

public static class VertexWrapper<T> where T : struct, IVertex
{
    public static readonly int Stride = Marshal.SizeOf(default(T));

    private static readonly List<VertexFieldAttribute> Attributes = new();

    private static int _enabledAttributesCount;

    static VertexWrapper()
    {
        AddAttributes(typeof(T), 0);
    }

    public static void Bind()
    {
        EnableAttributes(Attributes.Count);

        for (var i = 0; i < Attributes.Count; i++)
            GL.VertexAttribPointer(i, Attributes[i].Count, Attributes[i].Type, Attributes[i].Normalized, Stride, Attributes[i].Offset);
    }

    private static void AddAttributes(Type type, int currentOffset)
    {
        foreach (var field in type.GetFields(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic))
        {
            var fieldOffset = currentOffset + Marshal.OffsetOf(type, field.Name).ToInt32();

            if (typeof(IVertex).IsAssignableFrom(field.FieldType))
                AddAttributes(field.FieldType, fieldOffset);
            else if (field.IsDefined(typeof(VertexFieldAttribute), true))
            {
                var attribute = field.GetCustomAttribute(typeof(VertexFieldAttribute));
                Debug.Assert(attribute != null);

                var vertexAttribute = (VertexFieldAttribute)attribute;
                vertexAttribute.Offset = new IntPtr(fieldOffset);

                Attributes.Add(vertexAttribute);
            }
        }
    }

    private static void EnableAttributes(int count)
    {
        if (count == _enabledAttributesCount)
            return;

        if (count > _enabledAttributesCount)
        {
            for (var i = _enabledAttributesCount; i < count; ++i)
                GL.EnableVertexAttribArray(i);
        }
        else
        {
            for (var i = _enabledAttributesCount - 1; i >= count; --i)
                GL.DisableVertexAttribArray(i);
        }

        _enabledAttributesCount = count;
    }
}