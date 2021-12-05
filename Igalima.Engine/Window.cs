using Igalima.Engine.Common;
using Igalima.Engine.Graphics.Batches;
using Igalima.Engine.Graphics.OpenGL.Buffers;
using Igalima.Engine.Graphics.OpenGL.Vertices;
using Igalima.Engine.Graphics.Primitives;
using Igalima.Engine.Graphics.Shaders;
using Igalima.Engine.IO.Stores;
using Igalima.Resources;
using OpenTK.Graphics.OpenGL4;
using OpenTK.Mathematics;
using OpenTK.Windowing.Common;
using OpenTK.Windowing.Desktop;

namespace Igalima.Engine
{
    public class Window : GameWindow
    {
        private int _vertexArrayObject;

        private VertexBatch<Vertex> _vertexBatch;

        private Shader? _shader;

        private readonly ResourceStore _store;

        private Triangle _triangle;


        public Window(GameWindowSettings gameWindowSettings, NativeWindowSettings nativeWindowSettings) : base(gameWindowSettings, nativeWindowSettings)
        {
            _store = new ResourceStore(typeof(IgalimaResourcesAssembly).Assembly);
        }

        protected override void OnLoad()
        {
            base.OnLoad();

            _triangle = new Triangle(new Vector2(-0.5f, -0.5f), new Vector2(0.5f, -0.5f), new Vector2(0f, 0.5f));

            GL.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            _vertexArrayObject = GL.GenVertexArray();
            GL.BindVertexArray(_vertexArrayObject);

            _vertexBatch = new VertexBatch<Vertex>(3, 1);

            _shader = new Shader();
            if (_shader.Initialize(_store.Get("Shaders/Sh_Triangle.vs")!, _store.Get("Shaders/Sh_Triangle.fs")!).Status != ResultStatus.Success)
                return;

            _shader.Bind();
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            base.OnRenderFrame(e);

            GL.Clear(ClearBufferMask.ColorBufferBit);

            _shader?.Bind();

            GL.BindVertexArray(_vertexArrayObject);

            _vertexBatch.Add(new Vertex
            {
                Position = _triangle.Point0,
                Color = Color4.BlueViolet
            });
            _vertexBatch.Add(new Vertex
            {
                Position = _triangle.Point1,
                Color = Color4.DarkGoldenrod
            });
            _vertexBatch.Add(new Vertex
            {
                Position = _triangle.Point2,
                Color = Color4.IndianRed
            });

            _vertexBatch.Draw();

            _shader?.Unbind();
            SwapBuffers();
        }

        protected override void OnResize(ResizeEventArgs e)
        {
            base.OnResize(e);

            GL.Viewport(0, 0, Size.X, Size.Y);
        }

        protected override void OnUnload()
        {
            _shader?.Unbind();

            base.OnUnload();
        }
    }
}