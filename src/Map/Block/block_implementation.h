// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_MAP_BLOCK_BLOCK_IMPLEMENTATION_H_
#define UNNAMING_GAME_SRC_MAP_BLOCK_BLOCK_IMPLEMENTATION_H_
#include <cstddef>
#include "Block.h"
class Block::Implementation {
 public:
  virtual size_t index() const = 0;
  virtual const Block& Destroy() const = 0;
};
#endif  // UNNAMING_GAME_SRC_MAP_BLOCK_BLOCK_IMPLEMENTATION_H_
