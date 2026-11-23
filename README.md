# NodeGui Multimedia Plugin

This is a plugin for [NodeGui](https://docs.nodegui.org) meant to provide bindings to 
[Qt Multimedia's Module,](https://doc.qt.io/qt-6/qtmultimedia-module.html)
primarily developed for the future programs NEPChat and NEPTube.
Please keep in mind that this is in early development and is not meant
to be used in production yet.

Below is a table of functions/properties/etc that are not gonna be supported due to lack of support on NodeGUI
(***may*** be implemented in this plugin or in a NodeGUI PR in the future.) 
This list is nonexhaustive but if the type isn't supported in NodeGUI itself and is outside of Qt Multimedia, 
it likely won't be supported.

| Name | Type | Unsupported Type |
|------|------|------------------|
| QAudioBuffer.byteCount() | Function | qsizetype |
| QAudioBuffer.frameCount() | Function | qsizetype |
| QAudioBuffer.sampleCount() | Function | qsizetype |
| QMediaPlayer.sourceDevice() | Function | QIODevice |
| QMediaPlayer.setSourceDevice() | Slot |  QIODevice |
| QPlaybackOptions.probeSize | Property | qsizetype |
| QPlaybackOptions.probeSize() | Function | qsizetype |
| QPlaybackOptions.setProbeSize() | Function | qsizetype |
| QVideoSink.rhi() | Function | QRhi |

## TODO
* Write typescript side
* Test
* Anything under TODO in comments

## Building
Note that this project began when 6.10.2 was the latest and was built from there.
It may work fine on later versions though.

### Linux
Assuming you already have Node.JS, gcc, etc.
```sh
# Install qt 6.10.2 w/ multimedia
python -m pip install aqtinstall
aqt install-qt linux desktop 6.10.2 linux_gcc_64 -m qtmultimedia -O ~/Qt
# Export QT_INSTALL_DIR and install + build
export QT_INSTALL_DIR="$HOME/Qt/6.10.2/gcc_64"
yarn
yarn build
```
### Windows 
Note: You **need** MSVC2022's C++ toolchain and NOT other ones, like MinGW. Later versions may work fine too.

To download this by itself, [download and run build tools](https://aka.ms/vs/stable/vs_BuildTools.exe),
select "Desktop development with C++", deselect everything and select "Windows 11 SDK" (whatever is latest),
"C++ CMake Tools", and "MSVC v143 - VS 2022".
```powershell
# Install qt 6.10.2 w/ multimedia
python -m pip install aqtinstall
aqt install-qt windows desktop 6.10.2 win64_msvc2022_64 -m qtmultimedia -O C:\Qt
# export QT_INSTALL_DIR and install + build
$env:QT_INSTALL_DIR = "C:/Qt/6.10.2/msvc2022_64"
yarn
yarn build
```
### Mac
Assuming you already have Node.JS and Xcode command line tools (`xcode-select --install`)

**Important note:** The core maintainer and writer, [ggtyler](https://github.com/ggtyler), does not own a device with Apple Silicon. 
*(I don't want to waste like $300 on a test device that I'd barely use. Sorry, not sorry.)* 
Therefore, arm64 support is *completely* untested. Theoretically, it should work fine, but no stability is guaranteed.
***You have been warned.***
```sh
# Install qt 6.10.2 w/ multimedia
python -m pip install aqtinstall
aqt install-qt mac desktop 6.10.2 clang_64 -m qtmultimedia -O ~/Qt 
# Export QT_INSTALL_DIR and install + build
export QT_INSTALL_DIR="$HOME/Qt/6.10.2/clang_64"
yarn
yarn build
```

## Documentation
All typescript classes have extensive documentation included, to the point where
you likely will not need to use Qt's own docs. If you need to refer to
them though, a link is provided in the class definition.

Auto-generated web docs will be provided in the near future. (Note: generated 
as in with something like [typedoc](https://github.com/TypeStrong/typedoc), NOT
as in generative AI.)

## Development / Contributing
***DO NOT*** use AI!!! [Seriously, don't.](https://codeberg.org/ethical-foss/ai-free-foss-alternatives/src/branch/main/why_not_llms.md)
Any PRs, issues, etc. made with AI will get you ***immediately banned*** from the repo.
Oh, and, [you might get a surprise if you try it anyways.](https://codeberg.org/ggtyler/nodegui-plugin-multimedia/src/branch/main/AGENTS.md)
Just *don't* use it!!!

*\*Ahem.\** Anyways.

For writing code, you may want to refer to [nodegui's source code,](https://github.com/nodegui/nodegui/tree/master/src)
and of course, [Qt's own Multimedia docs.](https://doc.qt.io/qt-6/qtmultimedia-modules.html)
As of writing, there is no strict code style, except for keeping jsdoc's
max column count at 70 unless necessary. (You may want to collapse all 
block comments while working on the typescript side. Sorry.)

Depending on the IDE, you may have trouble getting C++ intellisense to work,
since it'll likely automatically use nodegui's miniqt version, and that
does not include the multimedia module.

To fix it on VSC (NOT VSCodium, as OpenVSX doesn't seem to have any good C++ plugins rn):
1. [Install the C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
2. Select an appropriate gcc toolkit (see above in building)
3. Under `cmake.environment` in the settings (or "CMake: Configure Environment" in the settings UI,) set
   the `QT_INSTALL_DIR` variable (again, see above)
   - Should look something like `"QT_INSTALL_DIR": "$HOME/Qt/6.10.2/gcc_64"`
4. Reload/restart

On CLion:
1. In Settings, go to "Build, Execution, Deployment", then "CMake"
   - This screen may show up when you're importing the project for the first time anyways
2. In Environment, write `QT_INSTALL_DIR=(your qt install path)` (see above in building for path.) 
3. Double check Toolchain (again, see above)
4. Apply

On Neovim / Helix / Any editor with a language server:

0. This assumes the LSP supports and relies on `compile_commands.json`. For other LSPs refer to their docs. 
1. Set `QT_INSTALL_DIR` (see above in building)
2. Generate `compile_commands` with `cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`
3. Link/move `build/compile_commands.json` to the project's root:
   * Linux/Mac: `ln -s build/compile_commands.json .`
   * Windows: `mklink compile_commands.json build/compile_commands.json`

For other IDEs please look up how to use an environment variable or
`compile_commands.json` in their documentation.

# License

This project is licensed under LGPL3.0, which means you can have your
own project under any license, but any forks of this plugin must keep
the same license. For more information, [see here.](https://www.gnu.org/licenses/lgpl-3.0.en.html)

Please note that Qt itself is dual licensed, with both GPL and LGPL.
If you want to be safe, use GPL.
