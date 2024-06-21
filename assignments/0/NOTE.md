# NOTE

專案一直建置不起來，卡在不熟悉 CMake 與 C++ 怎麼安裝 Eigen

## CMake

自動產生專案建置程式碼，在 Unix 系統會產生 gnu makefile，Windows 則是產生 Visual Studio 專案  
Visual Studio 可以直接開啟 CMake 的專案，不一定要用 Cmake 產生 .sln  
CMake 並不能像 npm 一樣下載套件，Eigen 要自行處理  
詳細的指令與注意事項寫在 `./code/CMakeLists.txt` 與 `./code/package.json`

## Eigen

最簡單粗暴的安裝方法是去 [Eigen 的 Gitlab](https://gitlab.com/libeigen/eigen) 下載，並且放入 includePath 中  
如果想用套件管理工具，Ubuntu 可以直接 `apt-get install libeigen3-dev`，或是 macOS 可以 `brew install eigen`  
Windows 則是用 `vcpkg install eigen3` （有夠難拼）  
vcpkg 是微軟開發跨平台 C++ package manager，Unix 系也可以用  
vcpkg 也可以與 VisualStudio、CMake 整合  
vcpkg 的安裝方法可以參考 [vcpkg 的 Github](https://github.com/microsoft/vcpkg)，安裝套件的指令是 `vcpkg install eigen3`  
安裝完後輸入 `vcpkg integrate install`，VisualStudio 就可以使用 vcpkg 安裝的套件了  
要在 CMake 使用 vcpkg 安裝的套件，則必須在 CMakeLists.txt 設置 CMAKE_TOOLCHAIN_FILE  
或是透過指令設定 CMAKE_TOOLCHAIN_FILE：

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"
```

## CMakeLists.txt

CMAKE_TOOLCHAIN_FILE 設置完成後，可以使用 find_package 自動搜尋 vcpkg 安裝的套件  
通常是放在 `$VCPKG_ROOT/installed/$TRIPLETS/share/eigen3`，檔名叫做 `Eigen3Config.cmake` 或是 `FindEigen3.cmake`  
並且會將 includePath 放在名為 `EIGEN3_INCLUDE_DIR`，但變數名稱要看該檔案如何實作  
接下來只要 `target_include_directories(Transformation PRIVATE ${EIGEN3_INCLUDE_DIRS})` 就會 include 了  
注意 `${}` 的部分很重要，不然不會被 CMake 當作變數解析

如何修正原本的 CMakeLists.txt 與 main.cpp 可以參考同學的留言：

<https://games-cn.org/forums/topic/graphics-intro-hw0/#post-7498>

> guoliang 於 2020 年 12 月 20 日上午 12:24：
>
> 1. CMakeLists.txt
>    EiGEN3_INCLUDE_DIR -> ${EIGEN3_INCLUDE_DIR}
> 2. main.cpp
>    头文件包含 删除 eigen3
>
> 可以在 CMakeLists.txt 中加入 **message (“${EIGEN3_INCLUDE_DIR}”)** 来查看自己的系统中 eigen 库的头文件目录。
