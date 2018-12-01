# main.cc

It contains the `main` function of the program. I can't keep it clean yet
because having to add lots of things there to test them.

---

* ```c++
  class DefaultUIRandom : public UniformIntRandom;
  ```

> An class inherit from `UniformIntRandom` interface.
>
> > You can find more informations about interface in `Interface\`.
>
> Use `STL` libs to implement functions.

* ```c++
  class CommandFor* : public Input::Command;
  ```

> Classes inherit from `Command` interface.
>
> > You can find more informations about interface in `Interface/`.
>
> They defined what will happened after you hit a key on your keyboard.
  
* ```c++
  void Init(LivingThing* role); 
  ```

> > You can find more informations about `LivingThing` class in `Object/`.
>
> Initiate almost every necessery data in this game.
>
> > 1. Setup some attributes about `Role`.
> > 2. Setup some attributes about `Renderer`.

* ```c++
  int main();
  ```

> The main loop of this game. 
> First, prepare some important things such as `Map` or `World`.
>
> > You can find more informations about them in `Map/`.
>
> Then, define what every keys means. I use some classes inherit from `Command`
> class so they can be call through a interface.
>
> > You can find more informations about `Command` class in `Input/`.
>
> Finally, we handle inputs in a `while`. Notice that we only re-disaply
> things after something changed.
