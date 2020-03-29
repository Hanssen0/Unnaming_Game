// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "Building.h"
#include "../map_cmake.h"
#include "./building_implementation.h"
MAP_EXPORT size_t Building::index() const {return impl_->index();}
MAP_EXPORT const std::list<Block>& Building::Foundation() const {
  return impl_->Foundation();
}
MAP_EXPORT void Building::Interact(Creature* creature) const {
  impl_->Interact(creature);
}
