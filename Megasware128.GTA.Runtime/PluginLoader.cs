using Microsoft.VisualStudio.Composition;
using System.Reflection;
using System.Runtime.Loader;

namespace Megasware128.GTA.Runtime;

internal class PluginLoader(DirectoryInfo directory) : IAssemblyLoader
{
    private readonly Dictionary<string, PluginLoadContext> _assemblyLoaders = directory.EnumerateFiles("*.dll")
        .ToDictionary(file => file.Name[..^4], file => new PluginLoadContext(file.FullName));

    public Assembly LoadAssembly(string assemblyFullName, string? codeBasePath)
    {
        var assemblyName = new AssemblyName(assemblyFullName);

        if (string.IsNullOrEmpty(codeBasePath))
        {
            return LoadAssembly(assemblyName);
        }

        var context = new PluginLoadContext(codeBasePath);

        return context.LoadFromAssemblyName(assemblyName);
    }

    public Assembly LoadAssembly(AssemblyName assemblyName)
    {
        return assemblyName.Name is not null && _assemblyLoaders.TryGetValue(assemblyName.Name, out var context)
            ? context.LoadFromAssemblyName(assemblyName)
            : throw new FileNotFoundException($"Assembly {assemblyName.Name} not found");
    }

    private class PluginLoadContext(string fullName) : AssemblyLoadContext
    {
        private readonly AssemblyDependencyResolver _resolver = new(fullName);

        protected override Assembly? Load(AssemblyName assemblyName)
        {
            var assemblyPath = _resolver.ResolveAssemblyToPath(assemblyName);

            return assemblyPath is not null ? LoadFromAssemblyPath(assemblyPath) : null;
        }
    }
}