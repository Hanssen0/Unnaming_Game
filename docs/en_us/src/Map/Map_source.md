# Map.h & Map.cc

These file contain things about gaming map.

---

```cpp
Point Map::PickARandomPointInGroundOrPath(
    const std::function< int32_t(int32_t, int32_t) >& ran) const;
```

> This function will return a totally valid random `Point` in map. Valid means
  that it's `Ground` or `Path`. `ran` is a function, which returns a random
  number between two arguments.

---

```cpp
struct Point;
```

> It contaions two intergents, one means `x` and another means `y`. We use it to
  represent a point on a plane.

---

```cpp
strcut Rect;
```

> Almost same as `Point`, but two intergents means `width` and `height`.

---

```cpp
struct RectWithPos;
```

> Combination of `Point` and `Rect`, save a rect and its position.

---

```cpp
inline bool operator<(const Point& a, const Point& b);
```

> Comparation between two `Point`, totally meaningless in physics. However we
  need it for better search.

---

```cpp
class Map;
```

> Most important part in this file! It describe a gaming map for role to
  explore.
>
> ---
>
> ```cpp
> enum BlockType;
> ```
>
> > Some constant value to describe the type of each blocks in map.
>
> ---
>
> ```cpp
> enum BuildingType;
> ```
>
> > We need some buildings for other thing such as travelling around the world!
>
> ---
>
> ```cpp
>  struct Target;
> ```
>
> > It record a position in another `Map`.
>
> ---
>
> ```cpp
> inline Map(const int32_t& w, const int32_t& h) : width_(w), height_(h);
> ```
>
> > Create a `Map`. We can create different `Map` in size by changing `w` or
    `h`.
>
> ---
>
> ```cpp
> inline const int32_t id();
> ```
>
> > Return `id` of this `Map`. If it doesn't have `id`, create one.
>
> ---
>
> ```cpp
> inline const BlockType& block(const Point& pos) const;
> inline void set_block(const Point& pos, const BlockType& block);
> inline const BuildingType& building(const Point& pos) const;
> inline void set_building(const Point& pos, const BuildingType& building);
> ```
> > Set or read informations about `Map`.
>
> ---
>
> ```cpp
> inline const Target& portal_target(const Point& pos) const;
> inline void set_portal_target(const Point& pos, const Target& target);
> ```
>
> > When there is a `Portal`, we can get or set its `Target` by these functions.
>
> ---
>
> ```cpp
> inline void FillWithBlock(const BlockType& block);
> inline void FillWithBuilding(const BuildingType& building);
> ```
>
> > Fill entire `Map`.
