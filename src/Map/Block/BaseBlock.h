// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_MAP_BLOCK_BASEBLOCK_H_
#define UNNAMING_GAME_SRC_MAP_BLOCK_BASEBLOCK_H_
#include <memory>
#include "Block.h"
class BaseBlock final {
 public:
  BaseBlock();
  ~BaseBlock();
  operator Block() const; // NOLINT
  static size_t BaseBlockSize();
  void SetDestroy(const Block&);

 private:
  class Implementation;
  std::shared_ptr<Implementation> impl_;
};
#endif  // UNNAMING_GAME_SRC_MAP_BLOCK_BASEBLOCK_H_
