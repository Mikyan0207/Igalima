using Igalima.Engine.Graphics.OpenGL.Buffers;
using Igalima.Engine.Graphics.OpenGL.Vertices;
using OpenTK.Graphics.OpenGL4;

namespace Igalima.Engine.Graphics.Batches;

public sealed class VertexBatch<T> where T : struct, IVertex, IEquatable<T>
{
    public List<VertexBuffer<T>> VertexBuffers = new();

    public readonly Action<T> AddAction;

    public int Size { get; }

    private readonly int _maxBuffers;

    private int _changeBeginIndex = -1;
    private int _changeEndIndex = -1;

    private int _currentBufferIndex;
    private int _currentVertexIndex;

    private VertexBuffer<T> CurrentVertexBuffer => VertexBuffers[_currentBufferIndex];

    public VertexBatch(int bufferSize, int maxBuffers)
    {
        Size = bufferSize;
        _maxBuffers = maxBuffers;

        AddAction = Add;
    }

    public void Add(T vertex)
    {
        if (_currentBufferIndex < VertexBuffers.Count && _currentVertexIndex >= CurrentVertexBuffer.Size)
            Draw();

        while (_currentBufferIndex >= VertexBuffers.Count)
            VertexBuffers.Add(new VertexBuffer<T>(Size, BufferUsageHint.DynamicDraw));

        if (CurrentVertexBuffer.SetVertex(_currentVertexIndex, vertex))
        {
            if (_changeBeginIndex == -1)
                _changeBeginIndex = _currentVertexIndex;

            _changeEndIndex = _currentVertexIndex + 1;
        }

        ++_currentVertexIndex;
    }

    public int Draw()
    {
        if (_currentVertexIndex == 0)
            return 0;

        var vertexBuffer = CurrentVertexBuffer;

        if (_changeBeginIndex >= 0)
            vertexBuffer.UpdateRange(_changeBeginIndex, _changeEndIndex);

        vertexBuffer.DrawRange(0, _currentVertexIndex);

        var count = _currentVertexIndex;

        _currentBufferIndex = (_currentBufferIndex + 1) % _maxBuffers;
        _currentVertexIndex = 0;
        _changeBeginIndex = -1;

        return count;
    }
}