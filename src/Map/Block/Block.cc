// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "Block.h"
#include "../map_cmake.h"
size_t Block::kBlockSize = 0;
MAP_EXPORT BlockPtr Block::Create() {
  return BlockPtr(new Block());
}
MAP_EXPORT size_t Block::BlockSize() {return kBlockSize;}
MAP_NO_EXPORT Block::Block() {
  index_ = kBlockSize++;
}
