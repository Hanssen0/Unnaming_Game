// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "LinkBuilding.h"
#include <cassert>
#include <list>
#include "../map_cmake.h"
#include "./building_implementation.h"
#include "./BaseBuilding.h"
#include "../Map.h"
#include "../../Object/Creature.h"
class LinkBuilding::Implementation: public Building::Implementation {
 public:
  inline Implementation() = default;
  explicit inline Implementation(const Building& base)
      : base_(base), has_pos_(false) {}
  inline size_t index() const override {return base_.index();}
  inline void set_base(const Building& base) {base_ = base;}
  inline void set_map(const Map_ref& map) {map_ = map;}
  inline void set_pos(const MapPoint& pos) {pos_ = pos;}
  inline const Building& Destroy() const override {return base_.Destroy();}
  inline const std::list<Building>& Foundation() const override {
    return base_.Foundation();
  }
  inline void Interact(Creature* creature) override {
    if (map_ == nullptr) set_map(creature->map()->space()->NewMap());
    if (!has_pos_) set_pos(map_->PickRandomPointIn(Foundation()));
    creature->Teleport(map_, pos_);
  }

 private:
  Building base_;
  Map_ref map_;
  bool has_pos_;
  MapPoint pos_;
};
MAP_EXPORT LinkBuilding::LinkBuilding()
    : impl_(std::make_shared<Implementation>()) {}
MAP_EXPORT LinkBuilding::LinkBuilding(const Building& base)
    : impl_(std::make_shared<Implementation>(base)) {}
MAP_EXPORT LinkBuilding::operator Building() {return Building(impl_);}
MAP_EXPORT void LinkBuilding::SetMap(const Map_ref& map) {impl_->set_map(map);}
MAP_EXPORT void LinkBuilding::SetPosition(const MapPoint& pos) {
  impl_->set_pos(pos);
}
