# SpaceInvaders - Galaga-like Raylib Prototype

This is a minimal C++ prototype implementing basic Galaga-like mechanics using Raylib.

Features
- Player ship moves left/right and shoots.
- Enemy formation and simple dive behavior.
- Scoring when enemies are destroyed.

Building on Windows (using vcpkg)
1. Install vcpkg and raylib via vcpkg:

```powershell
# example
git clone https://github.com/microsoft/vcpkg.git C:\vcpkg; C:\vcpkg\bootstrap-vcpkg.bat
C:\vcpkg\vcpkg.exe install raylib:x64-windows
```

2. Configure and build with CMake (from project root):

```powershell
mkdir build; cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

3. Run the executable from the build output.

Controls
- A / Left: move left
- D / Right: move right
- Space: shoot

Notes
- This is intentionally minimal to demonstrate core systems. You can extend with animations, sounds, capture mechanics, and better dive selection.
