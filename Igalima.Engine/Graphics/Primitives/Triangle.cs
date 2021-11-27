using OpenTK.Mathematics;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Igalima.Engine.Graphics.Primitives
{
    [StructLayout(LayoutKind.Sequential)]
    public readonly struct Triangle : IEquatable<Triangle>
    {
        // Note: Vertices ordered in screen-space counter-clockwise order.

        public readonly Vector2 Point0;

        public readonly Vector2 Point1;

        public readonly Vector2 Point2;

        public Triangle(Vector2 point0, Vector2 point1, Vector2 point2)
        {
            Point0 = point0;
            Point1 = point1;
            Point2 = point2;
        }

        public ReadOnlySpan<Vector2> Vertices => MemoryMarshal.CreateReadOnlySpan(ref Unsafe.AsRef(in Point0), 3);

        public bool Contains(Vector2 point)
        {
            // See https://en.wikipedia.org/wiki/Barycentric_coordinate_system
            // and https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle for more information.

            var area = Point0.Y * (Point2.X - Point1.X) + Point0.X * (Point1.Y - Point2.Y) + Point1.X * Point2.Y - Point1.Y * Point2.X;
            if (area == 0)
                return false;

            var s = (Point0.Y * Point2.X - Point0.X * Point2.Y + (Point2.Y - Point0.Y) * point.X + (Point0.X - Point2.X) * point.Y) / area;
            if (s < 0)
                return false;

            var t = (Point0.X * Point1.Y - Point0.Y * Point1.X + (Point0.Y - Point1.Y) * point.X + (Point1.X - Point0.X) * point.Y) / area;
            if (t < 0 || s + t > 1)
                return false;

            return true;
        }

        public bool Equals(Triangle other)
        {
            return Point0 == other.Point0 && Point1 == other.Point1 && Point2 == other.Point2;
        }

        public override bool Equals(object? obj)
        {
            return obj is Triangle triangle && Equals(triangle);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Point0.GetHashCode(), Point1.GetHashCode(), Point2.GetHashCode());
        }
    }
}
