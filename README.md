# domanek_project_2
NVS Projekt 2 Domanek

## Aufgabenstellung
Netzwerk‐basiertes RobotGame wie robowiki mit zentralem Server.


## verwendete Software
- [asio](https://think-async.com/Asio/)
- [CLI11](https://github.com/CLIUtils/CLI11)
- [criterion](https://github.com/p-ranav/criterion)
- [fmt](https://github.com/fmtlib/fmt)
- [spdlog](https://github.com/gabime/spdlog)

- [protocol-buffers](https://developers.google.com/protocol-buffers/)
- [gRPC](http://www.grpc.io/)

- [hello_imgui](https://github.com/pthom/hello_imgui)

## hello_imgui Installation WIP

git clone https://github.com/pthom/hello_imgui.git
cd hello_imgui
git submodule update --init
python3 ./tools/vcpkg_install_third_parties.py
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -DHELLOIMGUI_USE_SDL_OPENGL3=ON ..
make -j4