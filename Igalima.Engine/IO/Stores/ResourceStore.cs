using System.Reflection;

namespace Igalima.Engine.IO.Stores
{
    public class ResourceStore
    {
        private readonly Assembly assembly;

        private readonly string prefix;

        public ResourceStore(string dllName)
        {
            var dllPath = Path.Combine(Path.GetDirectoryName(Assembly.GetCallingAssembly().Location) ?? string.Empty, dllName);

            assembly = File.Exists(dllPath) ? Assembly.LoadFrom(dllPath) : Assembly.LoadFrom(Path.GetFileNameWithoutExtension(dllName));
            prefix = Path.GetFileNameWithoutExtension(dllName);
        }

        public ResourceStore(Assembly assembly)
        {
            this.assembly = assembly;
            prefix = assembly.GetName().Name ?? string.Empty;
        }

        public ResourceStore(AssemblyName assemblyName) : this(Assembly.Load(assemblyName))
        {
        }

        public byte[]? Get(string name)
        {
            using var stream = GetStream(name);

            if (stream == null)
                return null;

            byte[] result = new byte[stream.Length];
            stream.Read(result, 0, result.Length);

            return result;
        }

        public async Task<byte[]?> GetAsync(string name)
        {
            using var stream = GetStream(name);

            if (stream == null)
                return null;

            byte[] result = new byte[stream.Length];
            await stream.ReadAsync(result.AsMemory()).ConfigureAwait(false);

            return result;
        }

        public string GetResourcePath(string name)
        {
            if (string.IsNullOrEmpty(name))
                throw new ArgumentNullException(nameof(name));

            return assembly.GetManifestResourceNames().FirstOrDefault(x =>
            {
                x = x[(x.StartsWith(prefix, StringComparison.Ordinal) ? prefix.Length + 1 : 0)..];

                var lastDot = x.LastIndexOf('.');
                var chars = x.ToCharArray();

                for (var i = 0; i < lastDot; i++)
                {
                    if (chars[i] == '.')
                        chars[i] = '/';
                }

                return new string(chars) == name;
            }) ?? string.Empty;
        }

        public IEnumerable<string> GetAvailableResources()
        {
            return assembly.GetManifestResourceNames().Select(x =>
            {
                x = x[(x.StartsWith(prefix, StringComparison.Ordinal) ? prefix.Length + 1 : 0)..];

                var lastDot = x.LastIndexOf('.');
                var chars = x.ToCharArray();

                for (var i = 0; i < lastDot; i++)
                {
                    if (chars[i] == '.')
                        chars[i] = '/';
                }

                return new string(chars);
            });
        }

        public Stream GetStream(string name)
        {
            string[] split = name.Split('/');

            for (var i = 0; i < split.Length; i++)
                split[i] = split[i].Replace('-', '_');

            return assembly.GetManifestResourceStream($@"{prefix}.{string.Join('.', split)}")
                ?? throw new Exception($"File not found: {name}.");
        }
    }
}
