// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "BaseBlock.h"
#include <cassert>
#include <iostream>
#include "../map_cmake.h"
#include "./block_implementation.h"
class BaseBlock::Implementation: public BlockImplementation {
 public:
  inline size_t index() const override {return index_;}
  inline static size_t BaseBlockSize() {return kBaseBlockSize;}
  inline Implementation() {index_ = kBaseBlockSize++;}

 private:
  static size_t kBaseBlockSize;
  size_t index_;
};
size_t BaseBlock::Implementation::kBaseBlockSize = 0;
MAP_EXPORT size_t BaseBlock::BaseBlockSize() {
  return BaseBlock::Implementation::BaseBlockSize();
}
MAP_EXPORT BaseBlock::BaseBlock() : impl_(std::make_shared<Implementation>()) {}
MAP_EXPORT BaseBlock::operator Block() {return Block(impl_);}
