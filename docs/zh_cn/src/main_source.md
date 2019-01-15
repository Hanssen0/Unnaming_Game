# main.cc

这个文件包含了程序的`main`函数。我暂时还没法让它保持整洁，
因为不得不用一大堆东西来测试它们。

---

```cpp
class DefaultUIRandom : public UniformIntRandom;
```

> 继承自`UniformIntRandom`接口类。
>
> > 你可以在`Interface\`目录下找到接口类的更多信息。
>
> `STL`库实现其功能。

---

```cpp
class CommandFor* : public Input::Command;
```

> 继承自`Command`接口类。
>
> > 你可以在`Interface\`目录下找到接口类的更多信息。
>
> 它们定义了在你敲下键盘上的按钮后会发生什么。
  
---

```cpp
void Init(LivingThing* role); 
```

> > 你可以在`Object\`目录下找到`LivingThing`类的更多信息。
>
> 初始化游戏中几乎所有必要的数据。
>
> > 1. 设置`Role`的某些属性。
> > 2. 设置`Renderer`的某些属性。

---

```cpp
int main();
```

> 游戏的主循环。首先，准备一些重要的东西，比如`Map`或`World`。
>
> > 你可以在`Object\`目录下找到它们的更多信息。
>
> 然后，定义按键所代表的动作。我使用了一些继承自`Command`的类，
  因此它们可以通过接口被调用。
>
> > 你可以在`Interface\`目录下找到接口类的更多信息。
>
> 终于，我们在`while`中处理输入。注意，我们只在一些东西改变后更新显示。
