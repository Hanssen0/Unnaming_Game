# KeyBoardInput.h

定义键盘输入

---

```cpp
class Input;
```

> 终端输入类，它继承自 [class Input](../Interface/Input_header.md)
>
> ```cpp
> std::map< char, Command* > command_for_key_;
> ```
>
> > 它记录了输入->命令的映射。
>
> ---
>
> ```cpp
> Command* null_command_;
> ```
>
> > 它定义了未被记录的输入对应的命令，它在构造函数中被你提供的参数初始化。
>
> ---
>
> ```cpp
> void set_command_for_key(const char& key, Command* com);
> ```
>
> > 它构建一个输入->命令的映射并存储进command_for_key_，你应该在构造该类后优先调用这个函数。
>
> ---
>
> ```cpp
> virtual Command& HandleInput();
> ```
>
> > 它读取一个输入并返回输入映射到的命令，当这个映射不存在时，它返回 null_command_。
