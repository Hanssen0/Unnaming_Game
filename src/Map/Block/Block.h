// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_MAP_BLOCK_BLOCK_H_
#define UNNAMING_GAME_SRC_MAP_BLOCK_BLOCK_H_
#include <cstddef>
#include <memory>
#include <iostream>
class Block final {
 public:
  class Implementation;
  explicit Block(const std::shared_ptr<Implementation>& impl)
      : impl_(impl) {}
  operator bool() const {return static_cast<bool>(impl_);}
  bool operator==(const Block& block) const {return index() == block.index();}
  bool operator!=(const Block& block) const {return index() != block.index();}
  const std::shared_ptr<Implementation>& impl() const {return impl_;}
  size_t index() const;

 private:
  Block() = delete;
  std::shared_ptr<Implementation> impl_;
};
#endif  // UNNAMING_GAME_SRC_MAP_BLOCK_BLOCK_H_
