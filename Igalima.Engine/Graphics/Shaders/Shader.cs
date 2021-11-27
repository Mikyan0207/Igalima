using OpenTK.Graphics.OpenGL4;
using OpenTK.Mathematics;
using System.Text;

namespace Igalima.Engine.Graphics.Shaders
{
    public class Shader
    {
        public readonly int Handle;

        public bool IsLoaded { get; private set; }

        private IUniform[] _uniformsValues = Array.Empty<IUniform>();

        internal readonly Dictionary<string, IUniform> Uniforms = new();

        internal bool IsBound { get; private set; }

        public Shader(byte[] vertexBytes, byte[] fragmentBytes)
        {
            #region Vertex Shader

            var shaderSource = LoadFile(vertexBytes);
            var vertexShader = GL.CreateShader(ShaderType.VertexShader);

            GL.ShaderSource(vertexShader, shaderSource);
            CompileShader(vertexShader);

            #endregion

            #region Fragment Shader

            shaderSource = LoadFile(fragmentBytes);
            var fragmentShader = GL.CreateShader(ShaderType.FragmentShader);

            GL.ShaderSource(fragmentShader, shaderSource);
            CompileShader(fragmentShader);

            #endregion

            #region Program Shader

            Handle = GL.CreateProgram();

            GL.AttachShader(Handle, vertexShader);
            GL.AttachShader(Handle, fragmentShader);

            LinkProgram(Handle);

            GL.DetachShader(Handle, vertexShader);
            GL.DetachShader(Handle, fragmentShader);
            GL.DeleteShader(fragmentShader);
            GL.DeleteShader(vertexShader);

            #endregion

            IsLoaded = true;

            SetupUniforms();
        }

        public void Bind()
        {
            if (IsBound)
                return;

            GL.UseProgram(Handle);

            foreach (var uniform in _uniformsValues)
                uniform.Update();

            IsBound = true;
        }

        public void Unbind()
        {
            if (!IsBound)
                return;

            GL.UseProgram(0);
            IsBound = false;
        }

        public int GetAttribLocation(string attribName)
        {
            return GL.GetAttribLocation(Handle, attribName);
        }

        public Uniform<T> GetUniform<T>(string name) where T : struct, IEquatable<T>
        {
            return (Uniform<T>)Uniforms[name];
        }

        private void SetupUniforms()
        {
            GL.GetProgram(Handle, GetProgramParameterName.ActiveUniforms, out int uniformCount);

            _uniformsValues = new IUniform[uniformCount];

            for (var i = 0; i < uniformCount; i++)
            {
                GL.GetActiveUniform(Handle, i, 100, out _, out _, out var type, out var uniformName);

                IUniform? uniform = type switch
                {
                    ActiveUniformType.Bool => CreateUniform<bool>(uniformName),
                    ActiveUniformType.Float => CreateUniform<float>(uniformName),
                    ActiveUniformType.Int => CreateUniform<int>(uniformName),
                    ActiveUniformType.FloatMat3 => CreateUniform<Matrix3>(uniformName),
                    ActiveUniformType.FloatMat4 => CreateUniform<Matrix4>(uniformName),
                    ActiveUniformType.FloatVec2 => CreateUniform<Vector2>(uniformName),
                    ActiveUniformType.FloatVec3 => CreateUniform<Vector3>(uniformName),
                    ActiveUniformType.FloatVec4 => CreateUniform<Vector4>(uniformName),
                    ActiveUniformType.Sampler2D => CreateUniform<int>(uniformName),
                    _ => null
                };

                if (uniform == null)
                    continue;

                Uniforms.Add(uniformName, uniform);
                _uniformsValues[i] = uniform;
            }
        }

        private IUniform CreateUniform<T>(string uniformName) where T : struct, IEquatable<T>
        {
            var location = GL.GetUniformLocation(Handle, uniformName);

            return new Uniform<T>(this, uniformName, location);
        }

        private static string LoadFile(byte[] bytes)
        {
            if (bytes == null)
                throw new ArgumentNullException(nameof(bytes));

            using var ms = new MemoryStream(bytes);
            using var sr = new StreamReader(ms);

            return sr.ReadToEnd();
        }

        private static void CompileShader(int shader)
        {
            GL.CompileShader(shader);
            GL.GetShader(shader, ShaderParameter.CompileStatus, out var code);

            if (code != (int)All.True)
            {
                throw new Exception($"Error occured whilst compiling Shader({shader}).\n\n{GL.GetShaderInfoLog(shader)}");
            }
        }

        private static void LinkProgram(int handle)
        {
            GL.LinkProgram(handle);
            GL.GetProgram(handle, GetProgramParameterName.LinkStatus, out var code);

            if (code != (int)All.True)
            {
                throw new Exception($"Error occured whilst linking Program({handle})");
            }
        }
    }
}
