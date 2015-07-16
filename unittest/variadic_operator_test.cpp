#include <echo/variadic_operator.h>
#include <echo/test.h>
using namespace echo;

TEST_CASE("variadic_operator") {
  CHECK(and_(true, true));
  CHECK(!and_(true, false, true));

  CHECK(or_(false, true, false));
  CHECK(!or_(false, false, false));
}
