#pragma once

#include <echo/index.h>
#include <echo/test.h>
#include <catch.hpp>

using namespace echo;

TEST_CASE("index") {
  SECTION("construction") {
    Index<3> index1;
    Index<3> index2(1,2,3);
    REQUIRE(index2[0] == 1);
    REQUIRE(index2[1] == 2);
    REQUIRE(index2[2] == 3);
    //Index<3> index3(1); //compile error

    Index<1> index4(4);
    REQUIRE(index4 == 4);
  }
}

TEST_CASE("static index") {
  SECTION("comparison") {
    type_equal<
        decltype(StaticIndex<1>() < StaticIndex<3>())
      , std::true_type
    >();
    type_equal<
        decltype(StaticIndex<1>() == StaticIndex<3>())
      , std::false_type
    >();
  }
  SECTION("arithmetic") {
    type_equal<
        decltype(StaticIndex<1>() + StaticIndex<2>())
      , StaticIndex<3>
    >();
  }
}
