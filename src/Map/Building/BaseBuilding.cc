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
  inline void AddFoundation(const Block& foundation) {
    foundation_.push_back(foundation);
  }
  inline const std::list<Block>& Foundation() const override {
    return foundation_;
  }
  inline void Interact(Creature*) override {}

 private:
  static size_t kBaseBuildingSize;
  std::list<Block> foundation_;
  size_t index_;
};
size_t BaseBuilding::Implementation::kBaseBuildingSize = 0;
MAP_EXPORT BaseBuilding::BaseBuilding()
    : impl_(std::make_shared<Implementation>()) {}
MAP_EXPORT size_t BaseBuilding::BaseBuildingSize() {
  return BaseBuilding::Implementation::BaseBuildingSize();
}
MAP_EXPORT BaseBuilding::operator Building() {return Building(impl_);}
MAP_EXPORT void BaseBuilding::AddFoundation(const Block& foundation) {
  impl_->AddFoundation(foundation);
}
