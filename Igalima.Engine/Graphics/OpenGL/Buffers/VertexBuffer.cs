using System.Buffers;
using System.Dynamic;
using Igalima.Engine.Graphics.OpenGL.Vertices;
using OpenTK.Graphics.OpenGL4;
using SixLabors.ImageSharp.Memory;

namespace Igalima.Engine.Graphics.OpenGL.Buffers;

public class VertexBuffer<T> where T : struct, IVertex, IEquatable<T>
{
    private static readonly int Stride = VertexWrapper<T>.Stride;

    public int Size { get; }

    protected virtual PrimitiveType Type => PrimitiveType.Triangles;

    private readonly BufferUsageHint _usage;

    private Memory<T> _vertexMemory;
    private IMemoryOwner<T>? _memoryOwner;

    private int _vboId = -1;
    private int _eboId = -1;

    public VertexBuffer(int size, BufferUsageHint usage)
    {
        Size = size;
        _usage = usage;
    }

    protected virtual void Initialize()
    {
        GL.GenBuffers(1, out _vboId);
        GL.BindBuffer(BufferTarget.ArrayBuffer, _vboId);
        VertexWrapper<T>.Bind();
        GL.BufferData(BufferTarget.ArrayBuffer, (IntPtr)(Size * Stride), IntPtr.Zero, _usage);

        var indices = new ushort[3]
        {
            0, 1, 2
        };

        GL.GenBuffers(1, out _eboId);
        GL.BindBuffer(BufferTarget.ElementArrayBuffer, _eboId);
        GL.BufferData(BufferTarget.ElementArrayBuffer, (IntPtr)(indices.Length * sizeof(ushort)), indices, _usage);
    }

    public bool SetVertex(int index, T vertex)
    {
        ref var currentVertex = ref GetMemory().Span[index];

        var isNew = !currentVertex.Equals(vertex);

        currentVertex = vertex;

        return isNew;
    }

    public virtual void Bind()
    {
        if (_vboId == -1)
            Initialize();
        else
        {
            GL.BindBuffer(BufferTarget.ArrayBuffer, _vboId);
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, _eboId);
            VertexWrapper<T>.Bind();
        }
    }

    public virtual void Unbind()
    {
    }

    protected virtual int ToElements(int vertices) => vertices;

    protected virtual int ToElementsIndex(int index) => index;

    public void Draw()
    {
        DrawRange(0, Size);
    }

    public void DrawRange(int start, int end)
    {
        Bind();
        GL.DrawElements(PrimitiveType.Triangles, ToElements(end - start), DrawElementsType.UnsignedShort, (IntPtr)(ToElementsIndex(start) * sizeof(ushort)));
        Unbind();
    }

    public void Update()
    {
        UpdateRange(0, Size);
    }

    public void UpdateRange(int start, int end)
    {
        Bind();
        GL.BufferSubData(BufferTarget.ArrayBuffer, (IntPtr)(start * Stride), (IntPtr)((end - start) * Stride), ref GetMemory().Span[start]);
        Unbind();
    }

    private ref Memory<T> GetMemory()
    {
        if (_memoryOwner != null)
            return ref _vertexMemory;

        _memoryOwner = MemoryPool<T>.Shared.Rent(Size);
        _vertexMemory = _memoryOwner.Memory;

        return ref _vertexMemory;
    }
}