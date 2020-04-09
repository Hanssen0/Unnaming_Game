// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_MAP_BUILDING_BUILDING_IMPLEMENTATION_H_
#define UNNAMING_GAME_SRC_MAP_BUILDING_BUILDING_IMPLEMENTATION_H_
#include "Building.h"
#include <list>
class Building::Implementation {
 public:
  virtual ~Implementation() {}
  virtual const size_t& Index() const = 0;
  virtual const size_t& Size() const = 0;
  virtual const std::list<Building>& Foundation() const = 0;
  virtual int CostMove(const Creature&) const = 0;
  virtual int CostSeeThrough(const Creature&) const = 0;
  virtual const Building& Destroy() const = 0;
  virtual void Interact(Creature* creature) = 0;
};
#endif  // UNNAMING_GAME_SRC_MAP_BUILDING_BUILDING_IMPLEMENTATION_H_
