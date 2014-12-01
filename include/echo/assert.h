#pragma once

#include <type_traits>
#include <cassert>

namespace echo { namespace detail {

constexpr bool is_statically_false(const std::false_type&) {
  return true;
}

template<class T>
constexpr bool is_statically_false(const T&) {
  return false;
}

}} //end namespace

#define ECHO_ASSERT_EXPR_MSG(MSG, ...) assert(__VA_ARGS__ && MSG)

#define ECHO_ASSERT_MSG(MSG, ...) \
    static_assert(!detail::is_statically_false(__VA_ARGS__), MSG); \
    ECHO_ASSERT_EXPR_MSG(MSG, __VA_ARGS__);

#define ECHO_ASSERT(...) \
    ECHO_ASSERT_MSG("", __VA_ARGS__)
