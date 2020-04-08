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
  operator Building(); // NOLINT
  void AddFoundation(const Building&);
  void BindCostMove(const Creature&, int);
  void BindCostSeeThrough(const Creature&, int);
  void SetDestroy(const Building&);

 private:
  class Implementation;
  std::shared_ptr<Implementation> impl_;
};
#endif  // UNNAMING_GAME_SRC_MAP_BUILDING_BASEBUILDING_H_
