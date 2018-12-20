# KeyBoardInput.h

定义键盘输入

---

```cpp
class Input;
```

> 终端输入类，它继承自[`Input`类](../Interface/Input_header.md)
>
> ```cpp
> std::map< char, Command* > command_for_key_;
> ```
>
> > 记录了键盘输入对应的`Command（指令）`。
>
> ---
>
> ```cpp
> Command* null_command_;
> ```
>
> > 它定义了一个空`Command（指令）`，在构造函数中初始化。
>
> ---
>
> ```cpp
> void set_command_for_key(const char& key, Command* com);
> ```
>
> > 它设置了一个键盘输入对应的`Command（指令）`。
>
> ---
>
> ```cpp
> virtual Command& HandleInput();
> ```
>
> > 它读取输入并返回输入对应的`Command（指令）`，如果找不到合适的返回值，
    它返回`null_command_（空指令）`。
