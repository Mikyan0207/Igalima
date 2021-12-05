using OpenTK.Graphics.OpenGL4;
using OpenTK.Mathematics;

namespace Igalima.Engine.Graphics.Shaders
{
    public class Uniform<T> : IUniform where T : struct, IEquatable<T>
    {
        public Shader Owner { get; }

        public string Name { get; }

        public int Location { get; }

        public bool HasChanged { get; private set; } = true;

        public Uniform(Shader owner, string name, int uniformLocation)
        {
            Owner = owner;
            Name = name;
            Location = uniformLocation;
        }

        private T _value;

        public T Value
        {
            get => _value;
            set
            {
                if (value.Equals(_value)) return;

                _value = value;
                HasChanged = true;

                if (Owner.IsBound)
                    Update();
            }
        }

        public ref T GetValueByRef() => ref _value;

        public void UpdateValue(ref T newValue)
        {
            if (newValue.Equals(_value)) return;

            _value = newValue;
            HasChanged = true;

            if (Owner.IsBound)
                Update();
        }

        public void Update()
        {
            if (!HasChanged) return;

            SetUniform(this);
            HasChanged = false;
        }

        internal static void SetUniform(Uniform<T> uniform)
        {
            switch (uniform)
            {
                case Uniform<bool> b:
                    {
                        GL.Uniform1(uniform.Location, b.Value ? 1 : 0);
                    } break;
                case Uniform<float> f:
                    {
                        GL.Uniform1(uniform.Location, f.Value);
                    } break;
                case Uniform<int> i:
                    {
                        GL.Uniform1(uniform.Location, i.Value);
                    } break;
                case Uniform<Vector2> vec2:
                    {
                        GL.Uniform2(uniform.Location, vec2.Value);
                    } break;
                case Uniform<Vector3> vec3:
                    {
                        GL.Uniform3(uniform.Location, vec3.Value);
                    } break;
                case Uniform<Vector4> vec4:
                    {
                        GL.Uniform4(uniform.Location, vec4.Value);
                    } break;
                case Uniform<Matrix2> mat2:
                    {
                        GL.UniformMatrix2(uniform.Location, false, ref mat2.GetValueByRef());
                    } break;
                case Uniform<Matrix3> mat3:
                    {
                        GL.UniformMatrix3(uniform.Location, false, ref mat3.GetValueByRef());
                    } break;
                case Uniform<Matrix4> mat4:
                    {
                        GL.UniformMatrix4(uniform.Location, false, ref mat4.GetValueByRef());
                    } break;
                default:
                    throw new InvalidOperationException($"Unsupported Uniform<{typeof(T)}> type.");
            }
        }
    }
}
