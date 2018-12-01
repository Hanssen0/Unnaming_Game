# Input.h

This header define a interface for input.

---

```cpp
class Input;
```

> A interface class. Its inheritance classes should define these functions:
>
> ```cpp
> class Command;
> ```
>
> > It represent a single command. you give it some informations and execute it,
    then getting some reactions as you wish.
>
> ```cpp
> virtual Command& HandleInput() = 0;
> ```
>
> ---
>
> > When this function is called, it should return a `Command` for user's input.
    If user doesn't do anything, return a `Command` which do nothing.
