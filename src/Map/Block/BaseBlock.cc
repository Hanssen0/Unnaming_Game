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
class BaseBlock::Implementation: public Block::Implementation {
 public:
  inline Implementation() : index_(kBaseBlockSize++), destroy_(nullptr) {}
  inline static size_t BaseBlockSize() {return kBaseBlockSize;}
  inline size_t index() const override {return index_;}
  inline const Block& Destroy() const override {
    if (destroy_ != nullptr) return *destroy_;
    return NullBlock;
  }
  inline void SetDestroy(const Block& destroy) {destroy_ = &destroy;}

 private:
  static size_t kBaseBlockSize;
  size_t index_;
  const Block* destroy_;
};
size_t BaseBlock::Implementation::kBaseBlockSize = 0;
MAP_EXPORT size_t BaseBlock::BaseBlockSize() {
  return BaseBlock::Implementation::BaseBlockSize();
}
MAP_EXPORT BaseBlock::BaseBlock(): impl_(std::make_shared<Implementation>()) {}
MAP_EXPORT BaseBlock::operator Block() {return Block(impl_);}
MAP_EXPORT void BaseBlock::SetDestroy(const Block& destroy) {
  impl_->SetDestroy(destroy);
}