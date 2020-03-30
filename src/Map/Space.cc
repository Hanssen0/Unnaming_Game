#include "Space.h"
#include "map_cmake.h"
MAP_EXPORT Map_ref Space::NewMap() {
  Map_ref tmp = Map::Create(this, next_map_size_);
  maps_.push_front(tmp);
  auto map_iterator = maps_.begin();
  tmp->SetDestroy([map_iterator, this](){maps_.erase(map_iterator);});
  builder_->set_target_map(tmp.get());
  builder_->Build();
  return tmp;
}
