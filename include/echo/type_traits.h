#pragma once

#include <type_traits>

namespace echo { namespace type_traits {

///////////////////////////
// ConvertToConstPointer //
///////////////////////////

template<class Pointer>
struct ConvertToConstPointer {};

template<class T>
struct ConvertToConstPointer<
    T*
> {
  using type = const T*;
};

template<class T>
struct ConvertToConstPointer<
    const T*
> {
  using type = const T*;
};

}} //end namespace echo::type_traits
