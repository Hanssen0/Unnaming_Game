// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_MAP_BUILDING_BASEBUILDING_H_
#define UNNAMING_GAME_SRC_MAP_BUILDING_BASEBUILDING_H_
#include <list>
#include <memory>
#include "Building.h"
class BaseBuilding final {
 public:
  BaseBuilding();
  BaseBuilding(const BaseBuilding&) = delete;
  BaseBuilding& operator=(const BaseBuilding&) = delete;
  static size_t BaseBuildingSize();
  operator Building(); // NOLINT
  void AddFoundation(const Block&);

 private:
  class Implementation;
  std::shared_ptr<Implementation> impl_;
};
#endif  // UNNAMING_GAME_SRC_MAP_BUILDING_BASEBUILDING_H_
