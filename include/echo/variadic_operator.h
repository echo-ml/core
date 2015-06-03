#pragma once

namespace echo {

///////////
// and_c //
///////////

namespace detail {
namespace variadic_operator {
template <bool... Values>
struct and_c_impl {
  static constexpr bool value = true;
};

template <bool ValueFirst, bool... ValuesRest>
struct and_c_impl<ValueFirst, ValuesRest...> {
  static constexpr bool value = ValueFirst && and_c_impl<ValuesRest...>::value;
};
}
}

template <bool... Values>
constexpr bool and_c() {
  return detail::variadic_operator::and_c_impl<Values...>::value;
}
}
