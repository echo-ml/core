#include <echo/array.h>
#include <echo/test.h>
using namespace echo;

TEST_CASE("array") {
  auto x = make_array(3, 4,5);
  type_equal<std::array<int, 3>, decltype(x)>();
}
