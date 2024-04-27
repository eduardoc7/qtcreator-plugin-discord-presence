# Discord Rich Presence plugin for Qt Creator
This plugin adds Discord Rich Presence support to Qt Creator, with a decent chunk of recognized file types, and handmade icons for some of the more obscure file types without icons of their own.

![](screenshots/demo_cycle_20fps.gif?raw=true)

## Recognized File Types
| Category    | Extensions |
|-------------|------------|
| Qt/QMake    | `.pro` `.pri` `.ui` `.qrc` `.qml` `.qss` 
| C/C++       | `.cpp` `.hpp` `.cxx` `.hxx` `.cc` `.hh` `.c` `.h` `.i`
| Other Langs | `.py` `.rb` `.rs` `.js` `.css` `.html` `.lua` `.java` `.asm`
| Data & Text | `.json` `.xml` `.txt` `.md`
| Misc        | `.gitignore` `Makefile` `CMakeLists.txt`

## Supported Platforms
The plugin currently supports the following operating systems:
- Windows 64-bit
- Linux Derived 

## How to install the plugin on Qt Creator
Download the plugin archive from the [release page](https://github.com/eduardoc7/qtcreator-plugin-discord-presence/releases/tag/latest) and follow the installation tutorial provided in [Qt Documentation](https://doc.qt.io/qtcreator/creator-how-to-install-plugins.html)

## How to use with different versions of Qt Creator
To use the plugin with different versions of Qt Creator, you need to generate a new build by specifying the target Qt Creator version and the corresponding Qt version in the build process. Modify the variables `${qt_dir}` and `${qtc_dir}` in the [CMakeLists.txt](https://github.com/eduardoc7/qtcreator-plugin-discord-presence/blob/main/CMakeLists.txt). Alternatively, you can adjust the ENV variables in the [Github Action Workflow](https://github.com/eduardoc7/qtcreator-plugin-discord-presence/blob/main/.github/workflows/build_cmake.yml) to match the desired Qt and Qt Creator versions.

## How to Build
Create a build directory and run
```bash
    cmake -DCMAKE_PREFIX_PATH=<path_to_qt_framework>;<path_to_qtcreator> -DCMAKE_BUILD_TYPE=RelWithDebInfo <path_to_plugin_source>
    cmake --build .
```
where `<path_to_qtcreator>` is the relative or absolute path to a Qt Creator build directory, or to a
combined binary and development package (Windows / Linux), or to the `Qt Creator.app/Contents/Resources/`
directory of a combined binary and development package (macOS), and `<path_to_plugin_source>` is the
relative or absolute path to this plugin directory.

## How to Run
Run a compatible Qt Creator with the additional command line argument
    -pluginpath <path_to_plugin>

where `<path_to_plugin>` is the path to the resulting plugin library in the build directory
(`<plugin_build>/lib/qtcreator/plugins` on Windows and Linux,
`<plugin_build>/Qt Creator.app/Contents/PlugIns` on macOS).

You might want to add `-temporarycleansettings` (or `-tcs`) to ensure that the opened Qt Creator
instance cannot mess with your user-global Qt Creator settings.

When building and running the plugin from Qt Creator, you can use
    -pluginpath "%{buildDir}/lib/qtcreator/plugins" -tcs

on Windows and Linux, or
    -pluginpath "%{buildDir}/Qt Creator.app/Contents/PlugIns" -tcs

for the `Command line arguments` field in the run settings.

## Thanks and Credits
- [@PsychedelicShayna](https://github.com/PsychedelicShayna)
