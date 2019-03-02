# main.cc

It contains the `main` function of the program. I can't keep it clean yet
because having to add lots of things there to test them.

---

```cpp
void Init(Creature* role); 
```

> > [`Creature`](../../../src/Object/Creature.h)(No doc yet).
>
> Initiate almost every necessery data in this game.
>
> > 1. Setup some attributes about `Role`.
> > 2. Setup some attributes about `Renderer`.

---

```cpp
int main();
```

> The main loop of this game. 
>
> First, prepare some important things such as
  [`Map`][] or [`World`][].
>
> [`Map`]: Map/Map_source.md
> [`World`]: Map/World_source.md
>
> Then, define what every keys means. I bind some functions to the keys, so
  they can be call by the [`CinInput`][](No doc yet) class.
>
> [`CinInput`]: ../../zh_cn/src/FrontEnd/CinInput_source.md
>
> Finally, we handle inputs in a `while`. Notice that we only re-disaply
  things after something changed.
