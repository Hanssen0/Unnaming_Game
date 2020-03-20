// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_MAP_LINKBUILDING_H_
#define UNNAMING_GAME_SRC_MAP_LINKBUILDING_H_
#include <memory>
#include "./Building.h"
#include "../../Map/Map.h"
class LinkBuilding final {
 public:
  operator Building();
  LinkBuilding(const Building&);
  void SetMap(Map* const);
  void SetPosition(const Point&);

 private:
  class Implementation;
  std::shared_ptr<Implementation> impl_;
};
#endif  // UNNAMING_GAME_SRC_MAP_LINKBUILDING_H_
