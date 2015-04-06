#pragma once

#include <type_traits>
#include <echo/const_algorithm.h>

namespace echo {

///////////////
// enable_if //
///////////////

template <class... Conditions>
using enable_if =
    typename std::enable_if<const_algorithm::and_(fatal::constant_sequence<
                                bool, Conditions::value...>()),
                            int>::type;

////////////////
// disable_if //
////////////////

template <class... Conditions>
using disable_if =
    typename std::enable_if<!const_algorithm::or_(fatal::constant_sequence<
                                bool, Conditions::value...>()),
                            int>::type;

/////////////////
// enable_if_c //
/////////////////

template <bool... Conditions>
using enable_if_c = typename std::enable_if<
    const_algorithm::and_(fatal::constant_sequence<bool, Conditions...>()),
    int>::type;

//////////////////
// disable_if_c //
//////////////////

template <bool... Conditions>
using disable_if_c = typename std::enable_if<
    !const_algorithm::or_(fatal::constant_sequence<bool, Conditions...>()),
    int>::type;

}  // namespace echo
