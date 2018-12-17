# Random.h

这个头文件定义了随机类东西的接口。

---

```cpp
class UniformIntRandom;
```

> 他是一个用来生成随机数接口类，你应该自己定义这些函数。
>
> ---
>
> ```cpp
> virtual const int32_t rand(const int32_t& from, const int32_t& to) = 0;
> ```
>
> > 它应该返回一个不小于`from`，同时不大于`to`的数字。
>
> ---
>
> ```cpp
> virtual void set_seed(const int32_t& seed) = 0;
> ```
>
> > 设置随机数的`seed`（种子），它非常重要。
