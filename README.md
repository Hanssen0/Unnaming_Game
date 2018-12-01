# What's this?

This is a expermintal rogue-like game.

We hope it can offer a better experience for the normal player, instead of
just a game for geekers.

If you need any help (on code), you could find some documents in `docs\`.

# How can I play it?

We haven't release any binary file yet, so you should compile these source
codes by youself. Fortunately we have created some `cmake` files for it, so you
can easily `make` your own binary file by following commands (on `Linux`):

```bash
  mkdir build
  cd build
  cmake ..
  make
```

Make sure you have installed `cmake` and `make` tools. You should get
`Unnaming.out` if everything goes well.

Haven't tested on `Windows` platform, but almost everything should works fine
except 

```cpp
  system("clear");
```

in `main.cc`. You should edit it to

```cpp
  system("cls");
```

manually now. Going to fix it later.

Open an `issue` if you found any bug.

---

# 这是什么？

这是一个实验性的 Rouge-like 游戏。

我们希望它能为普通玩家提供更好的体验，而不仅仅是极客们的游戏。

如果你需要一些（代码上的）帮助，可以在 docs 文件夹中找到一些文档。

# 我怎么能玩到它？

我们尚未发布任何二进制文件，所以你应该自己编译这些源码文件。
幸运的是我们为它创建了一些`cmake`文件，所以（在`Linux`上）
你可以用这些指令轻松地通过`make`编译你自己的二进制文件：

```bash
  mkdir build
  cd build
  cmake ..
  make
```

确保你已经安装了`cmake`和`make`工具。如果一切正常,应你该能得到`Unnaming.out`。

尚未在`Windows`平台上测试，但大部分应该能正常工作。除了在`main.cc`里的

```cpp
  system("clear");
```

语句。你目前应该手动把它改为：

```cpp
  system("cls");
```

将会在之后修复它。

如果你找到了任何 bug ，创建一个`issue`。
