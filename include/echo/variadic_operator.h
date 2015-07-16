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

//------------------------------------------------------------------------------
// and_
//------------------------------------------------------------------------------
namespace DETAIL_NS {
inline constexpr bool and_impl() { return true; }

template <class OperandFirst, class... OperandsRest>
constexpr bool and_impl(OperandFirst operand_first,
                        OperandsRest... operands_rest) {
  return operand_first && and_impl(operands_rest...);
}
}

template <class... Operands>
constexpr bool and_(Operands... operands) {
  return DETAIL_NS::and_impl(operands...);
}

//------------------------------------------------------------------------------
// or_
//------------------------------------------------------------------------------
namespace DETAIL_NS {
inline constexpr bool or_impl() { return false; }

template <class OperorFirst, class... OperorsRest>
constexpr bool or_impl(OperorFirst operor_first, OperorsRest... operors_rest) {
  return operor_first || or_impl(operors_rest...);
}
}

template <class... Operors>
constexpr bool or_(Operors... operors) {
  return DETAIL_NS::or_impl(operors...);
}
}

#undef DETAIL_NS
