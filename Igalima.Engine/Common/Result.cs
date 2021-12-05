using System.Runtime.InteropServices;

namespace Igalima.Engine.Common;

[StructLayout(LayoutKind.Sequential)]
public struct Result
{
    public ResultStatus Status;

    public IList<string> Errors;
}