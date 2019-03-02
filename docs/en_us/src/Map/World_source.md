# World.h

This file contains things about how to manage maps.

---

```cpp
class World;
```

> Most important part in this file.
>
> ---
>
> ```cpp
> struct MemoryOfMap;
> ```
>
> > Role's memory of a [`Map`][]. Two [`Point`][] and a Vector array, store the
    viewable area, and a `Map` class saves details.
> >
> > [`Map`]: Map_source.md
> > [`Point`]: Map_source.md
>    
> ---
>
> ```cpp
> inline World(const std::function< int32_t(int32_t, int32_t) >& ran,
>              MapBuilder* builder, const Rect& nms) :
>              builder_(builder), random_gen_(ran), next_map_size_(nms);
> ```
>
> > The variable `ran` is a function, which returns a random
    number between two arguments.
>
> ---
>
> ```cpp
> inline Map* const NewMap();
> ```
>
> > Create a map and build things for it. Then insert it to a sorted Map list.
>
> ---
>
> ```cpp
> inline const Map::Target GetTarget(Map& map, const Point& pos);
> ```
>
> > Get the target of a portal. If it have no target, create a new map and pick
    a random target for it.
>
> ---
>
> ```cpp
> inline void Arrive(Map& map);
> inline void Left(Map& map);
> ```
>
> > To manage how many links to this map. If a map have no link, it'll be
    deleted.
>
> ---
>
> ```cpp
> inline MemoryOfMap& GetMemory(int32_t obj_id, Map& map);
> ```
>
> > Get the role's memory of the map by search in the memory list.
