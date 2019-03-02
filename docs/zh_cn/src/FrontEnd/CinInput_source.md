# CinInput.h

定义键盘输入

---

```cpp
class CinInput;
```

> 终端输入类。
>
> ```cpp
> const std::function< void() > null_function_;
> ```
>
> > 记录了键盘输入对应的回调函数。
>
> ---
>
> ```cpp
> const std::function< void() > null_function_;
> ```
>
> > 它指定了在默认状态下调用的回调函数，在构造函数中初始化。
>
> ---
>
> ```cpp
> void BindKey(const char& key, const std::function< void() > function);
> ```
>
> > 它绑定了一个键盘输入对应的回调函数。
>
> ---
>
> ```cpp
> void HandleInput();
> ```
>
> > 它读取输入并返回调用对应的回调函数，如果找不到合适的回调函数，
    它调用`null_function_`（空函数）。
