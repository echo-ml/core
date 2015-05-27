#include <echo/type_traits.h>
#include <catch.hpp>

using namespace echo;
using namespace echo::type_traits;

double f1(int) { return 2.7; }

struct A {
  int f1(int);
  int f2(int) const;
  int f3(int) volatile;
  int f4(int) const volatile;
};

struct B { int operator()() const; };
struct C { int operator()(); };

TEST_CASE("type_traits") {
  using P1 = ConvertToConstPointer<int*>::type;
  CHECK(std::is_same<P1, const int*>::value);

  using P2 = ConvertToConstPointer<const int*>::type;
  CHECK(std::is_same<P2, const int*>::value);

  using R1 = type_traits::function_return_type<decltype(f1)>;
  CHECK(std::is_same<R1, double>::value);

  CHECK(std::is_same<type_traits::function_return_type<decltype(&A::f1)>,
                       int>::value);
  CHECK(std::is_same<type_traits::function_return_type<decltype(&A::f2)>,
                       int>::value);
  CHECK(std::is_same<type_traits::function_return_type<decltype(&A::f3)>,
                       int>::value);
  CHECK(std::is_same<type_traits::function_return_type<decltype(&A::f4)>,
                       int>::value);

  CHECK(type_traits::function_arity<decltype(f1)>() == 1);

  CHECK(type_traits::is_const_functor<B>());
  CHECK(!type_traits::is_const_functor<C>());
}
