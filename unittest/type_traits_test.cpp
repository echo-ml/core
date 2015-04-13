#include <echo/type_traits.h>
#include <catch.hpp>

using namespace echo;
using namespace echo::type_traits;

double f1(int) { return 2.7; }

TEST_CASE("type_traits") {
  using P1 = ConvertToConstPointer<int*>::type;
  REQUIRE(std::is_same<P1, const int*>::value);

  using P2 = ConvertToConstPointer<const int*>::type;
  REQUIRE(std::is_same<P2, const int*>::value);

  using R1 = type_traits::function_return_type<decltype(f1)>;
  REQUIRE(std::is_same<R1, double>::value);
}
