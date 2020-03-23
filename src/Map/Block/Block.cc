// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "Block.h"
#include "../map_cmake.h"
#include "block_implementation.h"
MAP_EXPORT size_t Block::index() const {return impl_->index();}
MAP_EXPORT const Block& Block::Destroy() const {return impl_->Destroy();}
