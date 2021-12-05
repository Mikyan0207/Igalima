using System.Runtime.InteropServices;
using Igalima.Engine.Injection;
using Igalima.Engine.IO.Stores;
using OpenTK.Graphics.OpenGL4;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.PixelFormats;
using SixLabors.ImageSharp.Processing;

namespace Igalima.Engine.Graphics.Textures;

public class Texture
{
    public PixelInternalFormat InternalFormat { get; private set; }

    [Inject]
    private ResourceStore TextureStore { get; }

    public Texture(ResourceStore textureStore)
    {
        TextureStore = textureStore;
        InternalFormat = PixelInternalFormat.Rgba;
    }

    public Texture Create(string path)
    {
        var image = LoadImage(path);

        // TODO: Contiguous memory allocation for image pixels.
        // GL.TexImage2D(TextureTarget.Texture2D, 0, InternalFormat, image.Width, image.Height, 0, PixelFormat.Bgra, PixelType.UnsignedByte);

        return null;
    }

    public Image<Rgba32> LoadImage(string path)
    {
        var bytes = TextureStore.Get(path);

        if (bytes == null)
            throw new ArgumentNullException(nameof(path), $"File {path} not found.");

        var image = Image.Load(bytes);

        image.Mutate(x => x.Flip(FlipMode.Vertical));

        return image;
    }
}