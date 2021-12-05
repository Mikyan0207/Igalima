namespace Igalima.Engine.Common.Exceptions;

public class PropertyNotWritableException : Exception
{
    public PropertyNotWritableException(Type type, string name)
        : base($"Attempting to resolve into non-writable property {name} of type {type}.")
    {
    }
}