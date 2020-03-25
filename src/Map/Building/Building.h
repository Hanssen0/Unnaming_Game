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
#include <memory>
class Building final {
 public:
  class Implementation;
  explicit Building(const Implementation* impl = nullptr) : impl_(impl) {}
  operator bool() const {return impl_ != nullptr;}
  size_t index() const;

 private:
  const Implementation* impl_;
};
#endif  // UNNAMING_GAME_SRC_MAP_BUILDING_BUILDING_H_
