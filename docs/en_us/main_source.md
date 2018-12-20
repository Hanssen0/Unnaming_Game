# main.cc

It contains the `main` function of the program. I can't keep it clean yet
because having to add lots of things there to test them.

---

```cpp
class DefaultUIRandom : public UniformIntRandom;
```

> An class inherit from
  [`UniformIntRandom` interface](./Interface/Random_header.md).
  Use `STL` libs to implement functions.

---

```cpp
class CommandFor* : public Input::Command;
```

> Classes inherit from [`Command` interface](./Interface/Input_header.md).
  They defined what will happened after you hit a key on your keyboard.
  
---

```cpp
void Init(LivingThing* role); 
```

> > [`LivingThing` class (No doc yet)](../../src/Object/LivingThing.h).
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
  [`Map`](./Map/Map_source.md) or [`World` (No doc yet)](./Map/World_source).
>
> Then, define what every keys means. I use some classes inherit from `Command`
  class, so they can be call through a interface.
>
> Finally, we handle inputs in a `while`. Notice that we only re-disaply
  things after something changed.
