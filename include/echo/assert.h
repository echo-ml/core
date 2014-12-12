#pragma once

#include <type_traits>
#include <cassert>

namespace echo { namespace detail {

template<class T>
constexpr bool is_statically_false() {
  return false;
}

template<>
constexpr bool is_statically_false<std::false_type>() {
  return true;
}


}} //end namespace

#define ECHO_ASSERT_EXPR_MSG(MSG, ...) assert(__VA_ARGS__ && MSG)

#define ECHO_ASSERT_MSG(MSG, ...) \
    static_assert(!echo::detail::is_statically_false<decltype(__VA_ARGS__)>(), MSG); \
    ECHO_ASSERT_EXPR_MSG(MSG, __VA_ARGS__);

#define ECHO_ASSERT(...) \
    ECHO_ASSERT_MSG("", __VA_ARGS__)
