#pragma once

#include <iterator>

#include <tick/builder.h>

namespace echo { namespace concept {

using tick::valid;

/////////////////
// is_copyable //
/////////////////

TICK_TRAIT(
    is_copyable
  , std::is_copy_constructible<_>
  , std::is_copy_assignable<_>
) {
};

////////////////////////////
// is_equality_comparable //
////////////////////////////

TICK_TRAIT(is_equality_comparable) {
  template<class T>
  auto requires_(T&& x) -> valid<
      decltype(returns<bool>(x == x))
    , decltype(returns<bool>(x != x))
  >;
};

///////////////////////
// is_weakly_ordered //
///////////////////////

TICK_TRAIT(is_weakly_ordered) {
  template<class T>
  auto requires_(T&& x) -> valid<
      decltype(returns<bool>(x < x))
    , decltype(returns<bool>(x > x))
    , decltype(returns<bool>(x <= x))
    , decltype(returns<bool>(x >= x))
  >;
};

////////////////////////
// is_totally_ordered //
////////////////////////

TICK_TRAIT(
    is_totally_ordered
  , is_weakly_ordered<_>
  , is_equality_comparable<_>
) {
};

////////////////////
// is_allocatable //
////////////////////

TICK_TRAIT(is_allocatable) {
  template<class T>
  auto requires_(T x) -> valid<
      decltype(returns<T*>(new T))
    , decltype(delete new T)
    , decltype(returns<T*>(new T[1]))
    , decltype(delete [] new T[1])
  >;
};

/////////////////////
// is_semi_regular //
/////////////////////

TICK_TRAIT(
    is_semi_regular
  , std::is_default_constructible<_>
  , std::is_copy_constructible<_>
  , std::is_destructible<_>
  , std::is_copy_assignable<_>
  , is_allocatable<_>
) {
};

////////////////
// is_regular //
////////////////

TICK_TRAIT(
    is_regular
  , is_semi_regular<_>
  , is_equality_comparable<_>
) {
};

TICK_TRAIT(
    is_readable
  , is_semi_regular<_>
) {
  template<class T>
  auto requires_(T x) -> valid<
      decltype(returns<typename std::iterator_traits<T>::reference>(*x))
  >;
};
  
TICK_TRAIT(
    is_writable
  , is_semi_regular<_>
) {
  template<class T>
  auto requires_(T x) -> valid<
      decltype(*x = std::declval<typename std::iterator_traits<T>::value_type>())
  >;
};

TICK_TRAIT(
    is_weakly_incrementable
  , is_semi_regular<_>
) {
  template<class T>
  auto requires_(T x) -> valid<
      has_type<typename std::iterator_traits<T>::difference_type, std::is_integral<_>>
    , decltype(returns<T&>(++x))
    , decltype(x++)
  >;
};

TICK_TRAIT(
    is_incrementable
  , is_weakly_incrementable<_>
  , is_regular<_>
) {
};

TICK_TRAIT(
    is_weak_iterator
  , is_weakly_incrementable<_>
  , is_copyable<_>
) {
};

TICK_TRAIT(
    is_iterator
  , is_weak_iterator<_>
  , is_equality_comparable<_>
) {
};

TICK_TRAIT(
    is_weak_output_iterator
  , is_writable<_>
  , is_weak_iterator<_>
) {
};

TICK_TRAIT(
    is_output_iterator
  , is_weak_output_iterator<_>
  , is_iterator<_>
) {
};

TICK_TRAIT(
    is_weak_input_iterator
  , is_weak_iterator<_>
  , is_readable<_>
) {
  template<class T>
  auto requires_(T x) -> valid<
      decltype(returns<is_readable<_>>(x++))
  >;
};

TICK_TRAIT(
    is_input_iterator
  , is_weak_input_iterator<_>
  , is_iterator<_>
) {
  template<class T>
  auto requires_(T x) -> valid<
      is_true<
        std::is_convertible<
            typename std::iterator_traits<T>::iterator_category
          , std::input_iterator_tag
        >
      >
  >;
};

TICK_TRAIT(
    is_forward_iterator
  , is_input_iterator<_>
  , is_incrementable<_>
) {
  template<class T>
  auto requires_(T x) -> valid<
      is_true<
        std::is_convertible<
            typename std::iterator_traits<T>::iterator_category
          , std::forward_iterator_tag
        >
      >
  >;
};

TICK_TRAIT(
    is_bidirectional_iterator
  , is_forward_iterator<_>
) {
  template<class T>
  auto requires_(T x) -> valid<
      is_true<
        std::is_convertible<
            typename std::iterator_traits<T>::iterator_category
          , std::bidirectional_iterator_tag
        >
      >
    , decltype(returns<T&>(--x))
    , decltype(returns<T>(x--))
    , is_true<std::is_same<decltype(*x), decltype(*x--)>>
  >;
};

TICK_TRAIT(
    is_random_access_iterator
  , is_bidirectional_iterator<_>
  , is_totally_ordered<_>
) {
  template<class T>
  auto requires_(T x) -> valid<
      is_true<
        std::is_convertible<
            typename std::iterator_traits<T>::iterator_category
          , std::random_access_iterator_tag
        >
      >
    , decltype(returns<std::is_integral<_>>(x - x))
    , decltype(returns<std::is_signed<_>>(x - x))
    , decltype(returns<typename std::iterator_traits<T>::difference_type>(x - x))
    , decltype(returns<T>(x + (x-x)))
    , decltype(returns<T>((x-x) + x))
    , decltype(returns<T>(x - (x-x)))
    , decltype(returns<T&>(x += (x-x)))
    , decltype(returns<T&>(x -= (x-x)))
    , decltype(returns<typename std::iterator_traits<T>::reference>(x[x-x]))
  >;
};

}} //end namespace
