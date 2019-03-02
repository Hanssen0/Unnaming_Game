# main.cc

这个文件包含了程序的`main`函数。我暂时还没法让它保持整洁，
因为不得不用一大堆东西来测试它们。

---

```cpp
void Init(LivingThing* role); 
```

> > [`Creature`](../../../src/Object/Creature.h)(No doc yet).
>
> 初始化游戏中几乎所有必要的数据。
>
> > 1. 设置`Role`的某些属性。
> > 2. 设置`Renderer`的某些属性。

---

```cpp
int main();
```

> 游戏的主循环。首先，准备一些重要的东西，比如[`Map`][]或[`World`][]。
>
> [`Map`]: Map/Map_source.mdfdss2勒
> [`World`]: Map/World_source.md
>
> 然后，定义按键所代表的动作。我把一些函数绑定到了按键上，
  由此它们可以被[`CinInput`][](`cin`输入)类调用。
>
> [`CinInput`]: ../../zh_cn/src/FrontEnd/CinInput_source.md
>
> 终于，我们在`while`中处理输入。注意，我们只在一些东西改变后更新显示。
