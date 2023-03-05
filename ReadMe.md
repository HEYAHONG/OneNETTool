# 说明

本工具主要用于OneNET开发过程中的辅助工作。主要目的为符合本人习惯。

现有以下功能:

- Token计算。

## 源代码下载

由于本源代码包含第三方源代码,故直接下载可能有部分源代码缺失，需要通过以下方法解决:

- 在进行git clone 使用--recurse-submodules参数。

- 若已通过git clone下载,则在源代码目录中执行以下命令下载子模块:

  ```bash
   git submodule update --init --recursive
  ```


# 依赖库

- [wxWidgets](https://github.com/wxWidgets/wxWidgets):C++ GUI库
- [mbedtls](https://github.com/Mbed-TLS/mbedtls):可移植的TLS库，可移植到多种嵌入式场景。

