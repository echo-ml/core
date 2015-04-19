#include <echo/const_algorithm.h>
#include <echo/test.h>
#include <catch.hpp>

using namespace echo::const_algorithm;

template<int I>
using Int = std::integral_constant<int, I>;

struct Inc {
  constexpr int operator()(int x) const {
    return x+1;
  }
};

TEST_CASE("const algorithm tests") {
  using Empty    = fatal::constant_sequence<int>;
  using S1       = fatal::constant_sequence<int, 1, 2, 3, 4, 5>;
  using S2       = fatal::constant_sequence<int, 1, 1, 2>;
  using Bool1    = fatal::constant_sequence<bool, true, true>;
  using Bool2    = fatal::constant_sequence<bool, true, false>;
  using Bool3    = fatal::constant_sequence<bool, false, false>;



  SECTION("sum") {
    STATIC_EQUAL(int, sum(Empty()), 0);
    STATIC_EQUAL(int, sum(S1()), 15);
  }
  SECTION("product") {
    STATIC_EQUAL(int, product(Empty()), 1);
    STATIC_EQUAL(int, product(S1()), 120);
  }
  SECTION("logic") {
    //and
    STATIC_EQUAL(bool, and_(Bool1()), true);
    STATIC_EQUAL(bool, and_(Bool2()), false);

    //or
    STATIC_EQUAL(bool, or_(Bool2()), true);
    STATIC_EQUAL(bool, or_(Bool3()), false);

  }
  SECTION("tail") {
    echo::type_equal<decltype(tail<1>(S2())), fatal::constant_sequence<int, 1, 2>>();
    echo::type_equal<decltype(tail<3>(S2())), fatal::constant_sequence<int>>();
  }
  SECTION("count") {
    STATIC_EQUAL(int, count(S1(), Int<3>()), 1);
    STATIC_EQUAL(int, count(S1(), Int<0>()), 0);
    STATIC_EQUAL(int, count(S2(), Int<1>()), 2);
  }
  SECTION("contains") {
    STATIC_EQUAL(bool, contains(S1(), Int<2>()), true);
    STATIC_EQUAL(bool, contains(S1(), Int<6>()), false);
  }
  SECTION("find") {
    STATIC_EQUAL(int, find(S1(), Int<2>()), 1);
    STATIC_EQUAL(int, find(S1(), Int<6>()), kNotFound);
  }
  SECTION("find_last") {
    STATIC_EQUAL(int, find_last(S2(), Int<1>()), 1);
  }
  SECTION("slice") {
    echo::type_equal<fatal::constant_sequence<int, 2, 3>
                   , decltype(slice<1, 3>(S1()))>();
    STATIC_EQUAL(bool, contains(slice<1, 3>(S1()), Int<2>()), true);
  }
  SECTION("remove") {
    echo::type_equal<fatal::constant_sequence<int, 2>
                   , decltype(remove(S2(), Int<1>()))>();
  }
}
