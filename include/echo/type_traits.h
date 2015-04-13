#pragma once

#include <type_traits>

namespace echo {
namespace type_traits {

///////////////////////////
// ConvertToConstPointer //
///////////////////////////

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

//////////////////////////
// function_return_type //
//////////////////////////

namespace detail {
namespace type_traits {
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
}
}

template <class FunctionPtr>
using function_return_type =
    typename detail::type_traits::FunctionReturnType<FunctionPtr>::type;

}  // namespace type_traits
}  // namespace echo
