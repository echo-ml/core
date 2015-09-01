#pragma once

#include <echo/variadic_operator.h>
#include <type_traits>
#include <array>

namespace echo {

//------------------------------------------------------------------------------
// make_array
//------------------------------------------------------------------------------
template <class TFirst, class... TRest,
          std::enable_if_t<
              and_c<std::is_same<TFirst, TRest>::value...>(), int> = 0>
auto make_array(TFirst&& x_first, TRest&&... x_rest) {
  return std::array<std::decay_t<TFirst>, sizeof...(TRest) + 1>(
      {std::forward<TFirst>(x_first), std::forward<TRest>(x_rest)...});
}
}
