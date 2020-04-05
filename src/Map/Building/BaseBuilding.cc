// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "BaseBuilding.h"
#include <cassert>
#include <list>
#include "../map_cmake.h"
#include "./building_implementation.h"
class BaseBuilding::Implementation: public Building::Implementation {
 public:
  inline Implementation() {index_ = kBaseBuildingSize++;}
  inline static size_t BaseBuildingSize() {return kBaseBuildingSize;}
  inline size_t index() const override {return index_;}
  inline void AddFoundation(const Building& foundation) {
    foundation_.push_back(foundation);
  }
  inline const std::list<Building>& Foundation() const override {
    return foundation_;
  }
  inline const Building& Destroy() const override {
    return destroy_;
  }
  inline void Interact(Creature*) override {}
  inline void SetDestroy(const Building& destroy) {destroy_ = destroy;}

 private:
  static size_t kBaseBuildingSize;
  std::list<Building> foundation_;
  size_t index_;
  Building destroy_;
};
size_t BaseBuilding::Implementation::kBaseBuildingSize = 0;
MAP_EXPORT BaseBuilding::BaseBuilding()
    : impl_(std::make_shared<Implementation>()) {}
MAP_EXPORT size_t BaseBuilding::BaseBuildingSize() {
  return BaseBuilding::Implementation::BaseBuildingSize();
}
MAP_EXPORT BaseBuilding::operator Building() {return Building(impl_);}
MAP_EXPORT void BaseBuilding::AddFoundation(const Building& foundation) {
  impl_->AddFoundation(foundation);
}
MAP_EXPORT void BaseBuilding::SetDestroy(const Building& destroy) {
  impl_->SetDestroy(destroy);
}
