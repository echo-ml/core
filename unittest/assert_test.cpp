#include <echo/assert.h>
#include <catch.hpp>

using namespace echo;

TEST_CASE("assert") {
  //ECHO_ASSERT_MSG("this fails", std::false_type()); //fails statically
  ECHO_ASSERT(std::true_type());
  ECHO_ASSERT(1 == 1);
}
