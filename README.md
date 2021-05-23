# Groot for Windows

+ This is a forked modified Groot repo by [Aoi-hosizora](https://github.com/Aoi-hosizora). This is used by SCUT xxx (private) project.
+ For old README, please visit [README_old.md](./README_old.md).
+ Note that depended [BehaviorTree.CPP](https://github.com/BehaviorTree/BehaviorTree.CPP), [cppzmq](https://github.com/zeromq/cppzmq) and [libzmq](https://github.com/zeromq/libzmq) are all submodule-deinited.

## Build Groot on Windows and MinGW-x64

```bash
# Change to Your Qt path (line 12)
vim CMakeLists.txt

set PATH=D:\Development\Qt\5.15.2\mingw81_64\bin;%PATH%
mkdir build
cd build

cmake .. -G "MinGW Makefiles"
make -j8

# make 中途可能会报未找到 `-lzmq` 的错误
# 需要把已经编译出来的 build\depend\libzmq\lib 的 libzmq.a 和 libzmq.dll.a 复制到 mingw 的 lib 下，然后继续编译即可
# xxx\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\lib
```
