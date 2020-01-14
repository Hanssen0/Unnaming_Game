# Map.h & Map.cc

大多数函数都非常短，所以我把它们放在了头文件里。

---

```cpp
Point Map::PickARandomPointInGroundOrPath(
    const std::function< int32_t(int32_t, int32_t) >& ran) const;
```

> 这个函数会返回地图中一个完全随机的合法`Point`（点）。
  合法表示它是`Ground`（地面）或`Path`（路径）。`ran`是一个函数，
  它返回一个在两个参数之间的随机数。

---

```cpp
struct Point;
```

> 它包含两个整数，一个表示`x`且另一个表示`y`。我们用它来表示平面上的一个点。

---

```cpp
strcut Rect;
```

> 几乎和`Point`（点）一样，但两个整数分别代表`width`（宽度）和`height`（长度）。

---

```cpp
struct RectWithPos;
```

> `Point`（点）和`Rect`（矩形）的结合，储存一个矩形以及它的位置。

---

```cpp
inline bool operator<(const Point& a, const Point& b);
```

> 两个`Point`（点）之间的比较，在物理上毫无意义。但我们需要它来做到更好的搜索。

---

```cpp
class Map;
```

> 这个文件中最重要的部分！它描述了一个供角色探索的游戏地图。
>
> ---
>
> ```cpp
> enum BlockType;
> ```
>
> > 一些用来描述地图中每个方格类型的常数。
>
> ---
>
> ```cpp
> enum BuildingType;
> ```
>
> > 我们需要一些建筑进行其它行为，例如环绕世界旅行！
>
> ---
>
> ```cpp
>  struct Target;
> ```
>
> > 它记录了一个在另一张`Map（地图）`中的位置。
>
> ---
>
> ```cpp
> inline Map(const int32_t& w, const int32_t& h) : width_(w), height_(h);
> ```
>
> > 创建一张`Map（地图）`。我们可以通过改变`w`或`h`创建不同大小的`Map（地图）`。
>
> ---
>
> ```cpp
> inline const int32_t id();
> ```
>
> > 返回这张`Map（地图）`的`id`。如果它没有`id`，那就创建一个。
>
> ---
>
> ```cpp
> inline const BlockType& block(const Point& pos) const;
> inline void set_block(const Point& pos, const BlockType& block);
> inline const BuildingType& building(const Point& pos) const;
> inline void set_building(const Point& pos, const BuildingType& building);
> ```
> > 设置或者读取`Map（地图）`的信息。
>
> ---
>
> ```cpp
> inline const Target& portal_target(const Point& pos) const;
> inline void set_portal_target(const Point& pos, const Target& target);
> ```
>
> > 当存在一个`Portal（传送门）`时，
    我们可以通过这些函数获取或设定它的`Target（目标）`。
>
> ---
>
> ```cpp
> inline void FillWithBlock(const BlockType& block);
> inline void FillWithBuilding(const BuildingType& building);
> ```
>
> > 填满整张`Map（地图）`。
