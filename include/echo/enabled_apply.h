#pragma once

#include <echo/enable_if.h>
#include <echo/concept2.h>
#include <echo/concept.h>
#include <tuple>

namespace echo {

// struct IsFunctorApplicable : Concept {
//   template<class Functor, class Argument>
//   auto require(Functor&& functor, Argument&& argument) -> list<
//       valid<decltype(functor(argument))>()
//   >;
// };
//
// template<class Functor, class Argument>
// constexpr bool is_functor_applicable2() {
//   return models<IsFunctorApplicable, Functor, Argument>();
// }
//
// ///////////////////////////
// // is_functor_applicable //
// ///////////////////////////
//
// TICK_TRAIT(is_functor_applicable) {
//   template <class Functor, class Argument>
//   auto requires_(Functor && functor, Argument && argument)
//       ->tick::valid<decltype(functor(argument))>;
// };
//
// ///////////////////////
// // is_any_applicable //
// ///////////////////////
//
// namespace detail {
// namespace enabled_apply {
//
// template <
//     int I, class Functor, class Arguments,
//     enable_if_c<
//         I == std::tuple_size<typename std::decay<Arguments>::type>::value> = 0>
// auto is_any_applicable() -> std::false_type {
//   return {};
// }
//
// template <
//     int I, class Functor, class Arguments,
//     enable_if_c<
//         I != std::tuple_size<typename std::decay<Arguments>::type>::value> = 0,
//     enable_if<is_functor_applicable<
//         decltype(std::declval<Functor>()),
//         decltype(std::get<I>(std::declval<Arguments>()))>> = 0>
// auto is_any_applicable() -> std::true_type {
//   return {};
// }
//
// template <
//     int I, class Functor, class Arguments,
//     enable_if_c<
//         I != std::tuple_size<typename std::decay<Arguments>::type>::value> = 0,
//     disable_if<is_functor_applicable<
//         decltype(std::declval<Functor>()),
//         decltype(std::get<I>(std::declval<Arguments>()))>> = 0>
// auto is_any_applicable() {
//   return is_any_applicable<I + 1, Functor, Arguments>();
// }
// }  // namespace enabled_apply
// }  // namespace detail
//
// template <class Functor, class Arguments>
// constexpr bool is_any_applicable() {
//   using Result = decltype(
//       detail::enabled_apply::is_any_applicable<0, Functor, Arguments>());
//   return Result();
// }
//
// //////////////////////////
// // invoke_if_applicable //
// //////////////////////////
//
// template <class Functor, class Argument,
//           enable_if<is_functor_applicable<Functor, Argument>> = 0>
// decltype(auto) invoke_if_applicable(Functor&& functor, Argument&& argument) {
//   return functor(argument);
// }
//
// template <class Functor, class Argument,
//           disable_if<is_functor_applicable<Functor, Argument>> = 0>
// void invoke_if_applicable(Functor&& functor, Argument&& argument) {}
//
// /////////////////////////////
// // invoke_first_applicable //
// /////////////////////////////
//
// namespace detail {
// namespace enabled_apply {
// template <int I, class Functor, class Arguments,
//           CONCEPT_REQUIRES(is_functor_applicable2<
//               Functor, decltype(std::get<I>(std::declval<Arguments>()))>())>
// // enable_if<is_functor_applicable<
// //     decltype(std::declval<Functor>()),
// //     decltype(std::get<I>(std::declval<Arguments>()))>> = 0>
// decltype(auto) invoke_first_applicable(Functor&& functor,
//                                        Arguments&& arguments) {
//   return functor(std::get<I>(arguments));
// }
//
// template <int I, class Functor, class Arguments,
//           CONCEPT_REQUIRES(!is_functor_applicable2<
//               Functor, decltype(std::get<I>(std::declval<Arguments>()))>())>
//           // disable_if<is_functor_applicable<
//           //     decltype(std::declval<Functor>()),
//           //     decltype(std::get<I>(std::declval<Arguments>()))>> = 0>
// decltype(auto) invoke_first_applicable(Functor&& functor,
//                                        Arguments&& arguments) {
//   return invoke_first_applicable<I + 1>(std::forward<Functor>(functor),
//                                         std::forward<Arguments>(arguments));
// }
// }  // namespace enabled_apply
// }  // namespace detail
//
// template <class Functor, class Arguments>
// decltype(auto) invoke_first_applicable(Functor&& functor,
//                                        Arguments&& arguments) {
//   // static_assert(is_any_applicable<Functor, Arguments>(),
//   //               "functor is not applicable to any arguments");
//   return detail::enabled_apply::invoke_first_applicable<0>(
//       std::forward<Functor>(functor), std::forward<Arguments>(arguments));
// }
//
// ///////////////////////////
// // invoke_all_applicable //
// ///////////////////////////
//
// namespace detail {
// namespace enabled_apply {
//
// template <
//     int I, class Functor, class Arguments,
//     enable_if_c<
//         I == std::tuple_size<typename std::decay<Arguments>::type>::value> = 0>
// void invoke_all_applicable(Functor&& functor, Arguments&& arguments) {}
//
// template <
//     int I, class Functor, class Arguments,
//     enable_if_c<
//         I != std::tuple_size<typename std::decay<Arguments>::type>::value> = 0,
//     disable_if<is_functor_applicable<
//         decltype(std::declval<Functor>()),
//         decltype(std::get<I>(std::declval<Arguments>()))>> = 0>
// void invoke_all_applicable(Functor&& functor, Arguments&& arguments);
//
// template <
//     int I, class Functor, class Arguments,
//     enable_if_c<
//         I != std::tuple_size<typename std::decay<Arguments>::type>::value> = 0,
//     enable_if<is_functor_applicable<
//         decltype(std::declval<Functor>()),
//         decltype(std::get<I>(std::declval<Arguments>()))>> = 0>
// void invoke_all_applicable(Functor&& functor, Arguments&& arguments) {
//   functor(std::get<I>(arguments));
//   invoke_all_applicable<I + 1>(std::forward<Functor>(functor),
//                                std::forward<Arguments>(arguments));
// }
//
// template <int I, class Functor, class Arguments,
//           enable_if_c<I != std::tuple_size<
//                                typename std::decay<Arguments>::type>::value>,
//           disable_if<is_functor_applicable<
//               decltype(std::declval<Functor>()),
//               decltype(std::get<I>(std::declval<Arguments>()))>>>
// void invoke_all_applicable(Functor&& functor, Arguments&& arguments) {
//   invoke_all_applicable<I + 1>(std::forward<Functor>(functor),
//                                std::forward<Arguments>(arguments));
// }
// }  // namespace enabled_apply
// }  // namespace detail
//
// template <class Functor, class Arguments>
// void invoke_all_applicable(Functor&& functor, Arguments&& arguments) {
//   detail::enabled_apply::invoke_all_applicable<0>(
//       std::forward<Functor>(functor), std::forward<Arguments>(arguments));
// }

}  // namespace echo
