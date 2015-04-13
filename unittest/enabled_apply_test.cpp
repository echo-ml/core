// #include <echo/enabled_apply.h>
// #include <catch.hpp>
//
// using namespace echo;
//
// struct A {
//   int f() { return 2; }
// };
//
// struct B {};
//
// struct C {
//   int f() { return 3; }
// };
//
// namespace myns {
// template<int I, class Functor, class Arguments>
// decltype(auto) invoke(Functor&& func, Arguments&& args) {
//   return func(std::get<I>(args));
// }
// }
//
// template<class Functor, class Arguments>
// decltype(auto) invoke(Functor&& func, Arguments&& args) {
//   return myns::invoke<0>(std::forward<Functor>(func), std::forward<Arguments>(args));
// }
//
//
// template<class... Funcs>
// class FUnion {
//  public:
//   FUnion(Funcs... funcs) : _funcs(funcs...) {}
//
//   // template<class Arg1, class Arg2>
//   // auto operator()(const Arg1& arg1, const Arg2& arg2) {
//   //   auto apply = 
//   //     [&](const auto& f) -> decltype(f(arg1, arg2)) {
//   //       return f(arg1, arg2);
//   //     };
//   //   // return detail::enabled_apply::invoke_first_applicable<0>(apply, _funcs);
//   //   // return invoke(apply, _funcs);
//   //   return invoke_first_applicable(apply, _funcs);
//   // }
//   template<class... Args>
//   auto operator()(const Args&... args) {
//     auto apply = 
//       [&](const auto& f) -> decltype(f(args...)) {
//         return f(args...);
//       };
//     return invoke_first_applicable(apply, _funcs);
//   }
//  private:
//   std::tuple<Funcs...> _funcs;
// };
//
// TEST_CASE("enabled_apply") {
//   auto f = [](auto&& x) -> decltype(x.f()) { return x.f(); };
//   A a; B b; C c;
//   REQUIRE(invoke_if_applicable(f, a) == 2);
//   invoke_if_applicable(f, b);
//
//   auto ab = std::make_tuple(a, b);
//   auto bb = std::make_tuple(b, b);
//   auto ac = std::make_tuple(a, c);
//   auto abc = std::make_tuple(a, b, c);
//   static_assert(is_any_applicable<decltype(f), decltype(ab)>(),"");
//   static_assert(!is_any_applicable<decltype(f), decltype(bb)>(),"");
//   
//   REQUIRE(invoke_first_applicable(f, std::make_tuple(a, c)) == 2);
//   invoke_all_applicable(f, abc);
// }
//
// TEST_CASE("variadic_enabled_apply") {
//   auto f = [](int x, double y) { return x+y; };
//   FUnion<decltype(f)> funion(f);
//   REQUIRE(funion(3, 7.0) == 10.0);
// }
