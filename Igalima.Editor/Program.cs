// See https://aka.ms/new-console-template for more information

using Igalima.Engine;
using OpenTK.Mathematics;
using OpenTK.Windowing.Common;
using OpenTK.Windowing.Desktop;

using var game = new Window(GameWindowSettings.Default, new NativeWindowSettings
{
    Size = new Vector2i(1920, 1080),
    Title = "Igalima Engine",
    Flags = ContextFlags.ForwardCompatible,
});

game.Run();