#include <echo/enabled_apply.h>
#include <catch.hpp>

using namespace echo;

struct A {
  int f() { return 2; }
};

struct B {};

struct C {
  int f() { return 3; }
};

TEST_CASE("enabled_apply") {
  auto f = [](auto&& x) -> decltype(x.f()) { return x.f(); };
  A a; B b; C c;
  REQUIRE(invoke_if_applicable(f, a) == 2);
  invoke_if_applicable(f, b);

  auto ab = std::make_tuple(a, b);
  auto bb = std::make_tuple(b, b);
  auto ac = std::make_tuple(a, c);
  auto abc = std::make_tuple(a, b, c);
  static_assert(is_any_applicable<decltype(f), decltype(ab)>(),"");
  static_assert(!is_any_applicable<decltype(f), decltype(bb)>(),"");
  
  REQUIRE(invoke_first_applicable(f, std::make_tuple(a, c)) == 2);
  invoke_all_applicable(f, abc);
}
