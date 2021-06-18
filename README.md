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
```

## Note

+ Allow to define your owned builtin models and styles in `customized.xml`.

```xml
<root>
    <TreeNodesModel>
        <Decorator ID="IgnoreAndFailure"/>
        <Decorator ID="IgnoreAndSuccess"/>
    </TreeNodesModel>
    <TreeNodesStyle>
        <Decorator ID="IgnoreAndFailure">
            <icon>svg/failure.svg</icon>
            <caption_color>#ff2222</caption_color>
        </Decorator>
        <Decorator ID="IgnoreAndSuccess">
            <icon>svg/success.svg</icon>
            <caption_color>#00FF00</caption_color>
        </Decorator>
    </TreeNodesStyle>
</root>
```
