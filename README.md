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
Currently the release is being generated only for Linux using Qt 6 for the latest released versions of Qt Creator. Who knows, in the future, the Windows version will work by adjusting dependencies.

## How to Build
Create a build directory and run
```bash
    cmake -DCMAKE_PREFIX_PATH=<path_to_qtcreator> -DCMAKE_BUILD_TYPE=RelWithDebInfo <path_to_plugin_source>
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