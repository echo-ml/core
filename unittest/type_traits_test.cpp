#pragma once

#include <echo/type_traits.h>
#include <catch.hpp>

using namespace echo::type_traits;

TEST_CASE("type_traits") {
  using P1 = ConvertToConstPointer<int*>::type;
  REQUIRE(std::is_same<P1, const int*>::value);

  using P2 = ConvertToConstPointer<const int*>::type;
  REQUIRE(std::is_same<P2, const int*>::value);
}
