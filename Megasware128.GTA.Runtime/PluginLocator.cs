using Microsoft.Extensions.Options;

namespace Megasware128.GTA.Runtime;

public interface IPluginLocator
{
    IEnumerable<FileInfo> Plugins { get; }
}

internal class PluginLocator : IPluginLocator
{
    private readonly DirectoryInfo _pluginPath;
    private readonly PluginLoaderOptions _options;

    public PluginLocator(IOptions<PluginLoaderOptions> options)
    {
        _options = options.Value;
        _pluginPath = new(_options.PluginsPath);

        if (!_pluginPath.Exists)
        {
            _pluginPath.Create();
        }
    }

    public IEnumerable<FileInfo> Plugins => _pluginPath.EnumerateFiles(_options.PluginSearchPattern);
}
