#pragma once

#define DETAIL_NS detail_type_traits

#include <type_traits>

namespace echo {
namespace type_traits {

//------------------------------------------------------------------------------
// ConvertToConstPointer
//------------------------------------------------------------------------------
template <class Pointer>
struct ConvertToConstPointer {};

template <class T>
struct ConvertToConstPointer<T*> {
  using type = const T*;
};

template <class T>
struct ConvertToConstPointer<const T*> {
  using type = const T*;
};

//------------------------------------------------------------------------------
// function_return_type
//------------------------------------------------------------------------------
namespace DETAIL_NS {
template <class T>
struct FunctionReturnType {};

template <class Return, class... Args>
struct FunctionReturnType<Return(Args...)> {
  using type = Return;
};

template <class Return, class Record, class... Args>
struct FunctionReturnType<Return (Record::*)(Args...)> {
  using type = Return;
};

template <class Return, class Record, class... Args>
struct FunctionReturnType<Return (Record::*)(Args...) const> {
  using type = Return;
};

template <class Return, class Record, class... Args>
struct FunctionReturnType<Return (Record::*)(Args...) volatile> {
  using type = Return;
};

template <class Return, class Record, class... Args>
struct FunctionReturnType<Return (Record::*)(Args...) const volatile> {
  using type = Return;
};
}

template <class FunctionPtr>
using function_return_type =
    typename DETAIL_NS::FunctionReturnType<FunctionPtr>::type;

//------------------------------------------------------------------------------
// functor_return_type
//------------------------------------------------------------------------------
template <class Functor>
using functor_return_type =
    function_return_type<decltype(&Functor::operator())>;

//------------------------------------------------------------------------------
// function_arity
//------------------------------------------------------------------------------
namespace DETAIL_NS {
template <class T>
struct FunctionArity {};

template <class Return, class... Args>
struct FunctionArity<Return(Args...)> {
  static constexpr int value = sizeof...(Args);
};

template <class Return, class Record, class... Args>
struct FunctionArity<Return (Record::*)(Args...)> {
  static constexpr int value = sizeof...(Args);
};

template <class Return, class Record, class... Args>
struct FunctionArity<Return (Record::*)(Args...) const> {
  static constexpr int value = sizeof...(Args);
};

template <class Return, class Record, class... Args>
struct FunctionArity<Return (Record::*)(Args...) volatile> {
  static constexpr int value = sizeof...(Args);
};

template <class Return, class Record, class... Args>
struct FunctionArity<Return (Record::*)(Args...) const volatile> {
  static constexpr int value = sizeof...(Args);
};
}

template <class FunctionPtr>
constexpr int function_arity() {
  return DETAIL_NS::FunctionArity<FunctionPtr>::value;
}

//------------------------------------------------------------------------------
// functor_arity
//------------------------------------------------------------------------------
template <class Functor>
constexpr int functor_arity() {
  return function_arity<decltype(&Functor::operator())>();
}

//------------------------------------------------------------------------------
// is_const_functor
//------------------------------------------------------------------------------
namespace DETAIL_NS {
template <class>
struct ConstFunctor : std::false_type {};

template <class Return, class Record, class... Args>
struct ConstFunctor<Return (Record::*)(Args...) const> : std::true_type {};

template <class Return, class Record, class... Args>
struct ConstFunctor<Return (Record::*)(Args...) const volatile>
    : std::true_type {};
}

template <class Functor>
constexpr bool is_const_functor() {
  return DETAIL_NS::ConstFunctor<decltype(&Functor::operator())>::value;
}

}  // namespace type_traits
}  // namespace echo

#undef DETAIL_NS
