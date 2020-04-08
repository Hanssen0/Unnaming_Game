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
MAP_EXPORT const size_t& Building::Index() const {return impl_->Index();}
MAP_EXPORT const size_t& Building::Size() const {return impl_->Size();}
MAP_EXPORT const std::list<Building>& Building::Foundation() const {
  return impl_->Foundation();
}
MAP_EXPORT const Building& Building::Destroy() const {return impl_->Destroy();}
MAP_EXPORT void Building::Interact(Creature* creature) const {
  impl_->Interact(creature);
}
