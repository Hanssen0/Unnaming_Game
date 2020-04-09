// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_MAP_BUILDING_BUILDING_H_
#define UNNAMING_GAME_SRC_MAP_BUILDING_BUILDING_H_
#include <cstddef>
#include <list>
#include <memory>
class Creature;
class Building final {
 public:
  class Implementation;
  explicit Building(std::shared_ptr<Implementation> impl = nullptr)
      : impl_(impl) {}
  operator bool() const {return static_cast<bool>(impl_);}
  bool operator==(const Building& b) const {return Index() == b.Index();}
  bool operator!=(const Building& b) const {return Index() != b.Index();}
  const size_t& Index() const;
  const size_t& Size() const;
  const std::list<Building>& Foundation() const;
  int CostMove(const Creature&) const;
  int CostSeeThrough(const Creature&) const;
  const Building& Destroy() const;
  void Interact(Creature*) const;

 private:
  std::shared_ptr<Implementation> impl_;
};
#endif  // UNNAMING_GAME_SRC_MAP_BUILDING_BUILDING_H_
