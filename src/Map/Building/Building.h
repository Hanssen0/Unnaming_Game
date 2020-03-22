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
class BuildingImplementation;
class Building final {
 public:
  size_t index() const;
  explicit Building(const std::shared_ptr<BuildingImplementation>& impl)
      : impl_(impl) {}
  const std::shared_ptr<BuildingImplementation>& impl() const {return impl_;}
  operator bool() const {return static_cast<bool>(impl_);}

 private:
  Building() = delete;
  std::shared_ptr<BuildingImplementation> impl_;
};
#endif  // UNNAMING_GAME_SRC_MAP_BUILDING_BUILDING_H_
