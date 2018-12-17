# Input.h

这个头文件定义了输入的接口。

---

```cpp
class Input;
```

> 一个接口类。它的继承类应该定义这些函数。
>
> ```cpp
> class Command;
> ```
>
> > 它代表了单一条命令。你给它一些信息之后执行它，然后会得到一些你想要的反应。
>
> ---
>
> ```cpp
> virtual Command& HandleInput() = 0;
> ```
>
> > 当这个函数被调用时，它应当根据用户的输入返回一个`Command`类。
    如果用户什么都没做，返回一个什么都不做的`Command`。
