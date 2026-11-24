const path = require("path");
const fs = require("fs");
const { setupArtifact } = require("@nodegui/artifact-installer");

const nodeguiPkg = require.resolve("@nodegui/nodegui/package.json");
const miniQtBase = path.join(
    path.dirname(nodeguiPkg),
    "miniqt",
    "6.10.2",
);
const platform = process.platform;

let setupDir, downloadLink, libCheck;
if (platform === "linux") {
    setupDir = path.join(miniQtBase, "gcc_64");
    downloadLink =
        "https://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt6_6102/qt6_6102/qt.qt6.6102.addons.qtmultimedia.linux_gcc_64/6.10.2-0-202601261212qtmultimedia-Linux-RHEL_9_4-GCC-Linux-RHEL_9_4-X86_64.7z";
    libCheck = path.join(setupDir, "lib", "libQt6Multimedia.so.6");
} else if (platform === "darwin") {
    setupDir = path.join(miniQtBase, "macos");
    downloadLink =
        "https://download.qt.io/online/qtsdkrepository/mac_x64/desktop/qt6_6102/qt6_6102/qt.qt6.6102.addons.qtmultimedia.clang_64/6.10.2-0-202601261210qtmultimedia-MacOS-MacOS_15-Clang-MacOS-MacOS_15-X86_64-ARM64.7z";
    libCheck = path.join(
        setupDir,
        "lib",
        "QtMultimedia.framework",
        "QtMultimedia",
    );
} else if (platform === "win32") {
    setupDir = path.join(miniQtBase, "msvc2022_64");
    downloadLink =
        "https://download.qt.io/online/qtsdkrepository/windows_x86/desktop/qt6_6102/qt6_6102/qt.qt6.6102.addons.qtmultimedia.win64_msvc2022_64/6.10.2-0-202601261212qtmultimedia-Windows-Windows_11_24H2-MSVC2022-Windows-Windows_11_24H2-X86_64.7z";
    libCheck = path.join(setupDir, "bin", "Qt6Multimedia.dll");
}

async function setup() {
    if (fs.existsSync(libCheck)) return;

    console.log(`Downloading Qt Multimedia to ${setupDir}...`);
    await setupArtifact({
        outDir: setupDir,
        id: "nodegui-mini-qtmultimedia",
        displayName: "Qt Multimedia for NodeGUI",
        downloadLink: downloadLink,
        skipSetup: () => false,
    });
}

setup().catch((err) => {
    console.error("Failed to setup Qt Multimedia:", err);
    process.exit(1);
});
