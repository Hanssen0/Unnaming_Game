// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_MAP_BUILDING_H_
#define UNNAMING_GAME_SRC_MAP_BUILDING_H_
#include <memory>
class Building;
typedef std::shared_ptr<Building> BuildingPtr;
class Building final {
 public:
  static BuildingPtr Create();
  static size_t BuildingSize();
  inline size_t index() const {return index_;}

 private:
  Building();
  static size_t kBuildingSize;
  size_t index_;
};
#endif  // UNNAMING_GAME_SRC_MAP_BUILDING_H_
