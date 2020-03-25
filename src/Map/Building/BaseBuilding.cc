// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "BaseBuilding.h"
#include <cassert>
#include <iostream>
#include "../map_cmake.h"
#include "./building_implementation.h"
class BaseBuilding::Implementation: public Building::Implementation {
 public:
  inline size_t index() const override {return index_;}
  inline static size_t BaseBuildingSize() {return kBaseBuildingSize;}
  inline Implementation() {index_ = kBaseBuildingSize++;}

 private:
  static size_t kBaseBuildingSize;
  size_t index_;
};
size_t BaseBuilding::Implementation::kBaseBuildingSize = 0;
MAP_EXPORT BaseBuilding::BaseBuilding():
    impl_(std::make_unique<Implementation>()) {}
MAP_EXPORT BaseBuilding::~BaseBuilding() = default;
MAP_EXPORT BaseBuilding::operator Building() {
  return Building(impl_.get());
}
MAP_EXPORT size_t BaseBuilding::BaseBuildingSize() {
  return BaseBuilding::Implementation::BaseBuildingSize();
}
