// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "LinkBuilding.h"
#include <cassert>
#include "../map_cmake.h"
#include "./building_implementation.h"
#include "./BaseBuilding.h"
#include "../../Map/Map.h"
class LinkBuilding::Implementation: public Building::Implementation {
 public:
  inline size_t index() const override {return base_->index();}
  inline void set_map(Map* const map) {map_ = map;}
  inline void set_pos(const MapPoint& pos) {pos_ = pos;}

 private:
  const Building* base_;
  Map* map_;
  MapPoint pos_;
};
MAP_EXPORT LinkBuilding::LinkBuilding()
    : impl_(std::make_unique<Implementation>()) {}
MAP_EXPORT LinkBuilding::~LinkBuilding() = default;
MAP_EXPORT LinkBuilding::operator Building() {
  return Building(impl_.get());
}
MAP_EXPORT void LinkBuilding::SetMap(Map* const map) {impl_->set_map(map);}
MAP_EXPORT void LinkBuilding::SetPosition(const MapPoint& pos) {
  impl_->set_pos(pos);
}
