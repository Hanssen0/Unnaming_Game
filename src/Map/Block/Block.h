// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_MAP_BLOCK_BLOCK_H_
#define UNNAMING_GAME_SRC_MAP_BLOCK_BLOCK_H_
#include <memory>
class Block;
typedef std::shared_ptr<Block> BlockPtr;
class Block final {
 public:
  static BlockPtr Create();
  static size_t BlockSize();
  inline size_t index() const {return index_;}

 private:
  Block();
  static size_t kBlockSize;
  size_t index_;
};
#endif  // UNNAMING_GAME_SRC_MAP_BLOCK_BLOCK_H_
