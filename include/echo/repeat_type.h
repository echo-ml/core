#pragma once

#define DETAIL_NS detail_repeat_type

namespace echo {

//------------------------------------------------------------------------------
// repeat_type
//------------------------------------------------------------------------------
namespace DETAIL_NS {
template <class, class T>
struct repeat_type_impl {
  using type = T;
};
}

template <class A, class T>
using repeat_type = typename DETAIL_NS::repeat_type_impl<A, T>::type;

//------------------------------------------------------------------------------
// repeat_type_c
//------------------------------------------------------------------------------
namespace DETAIL_NS {
template <unsigned long long, class T>
struct repeat_type_c_impl {
  using type = T;
};
}

template <unsigned long long A, class T>
using repeat_type_c = typename DETAIL_NS::repeat_type_c_impl<A, T>::type;
}

#undef DETAIL_NS
