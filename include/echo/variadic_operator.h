#pragma once

#define DETAIL_NS detail_variadic_operator

namespace echo {

//------------------------------------------------------------------------------
// and_c
//------------------------------------------------------------------------------
namespace DETAIL_NS {
template <bool... Values>
struct and_c_impl {
  static constexpr bool value = true;
};

template <bool ValueFirst, bool... ValuesRest>
struct and_c_impl<ValueFirst, ValuesRest...> {
  static constexpr bool value = ValueFirst && and_c_impl<ValuesRest...>::value;
};
}

template <bool... Values>
constexpr bool and_c() {
  return DETAIL_NS::and_c_impl<Values...>::value;
}
}

//------------------------------------------------------------------------------
// or_c
//------------------------------------------------------------------------------
namespace DETAIL_NS {
template <bool... Values>
struct or_c_impl {
  static constexpr bool value = false;
};

template <bool ValueFirst, bool... ValuesRest>
struct or_c_impl<ValueFirst, ValuesRest...> {
  static constexpr bool value = ValueFirst || or_c_impl<ValuesRest...>::value;
};
}

template <bool... Values>
constexpr bool or_c() {
  return DETAIL_NS::or_c_impl<Values...>::value;
}

#undef DETAIL_NS
