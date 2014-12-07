#pragma once

#include <fatal/type/sequence.h>
#include <utility>

namespace echo { namespace const_algorithm {

/////////
// sum //
/////////

template<class T>
constexpr int sum(const fatal::constant_sequence<T>&) {
  return 0;
}

template<class T, T ValueFirst, T... ValuesRest>
constexpr int sum(const fatal::constant_sequence<T, ValueFirst, ValuesRest...>&) {
  return ValueFirst + sum(fatal::constant_sequence<T, ValuesRest...>());
}

/////////////
// product //
/////////////

template<class T>
constexpr int product(const fatal::constant_sequence<T>&) {
  return 1;
}

template<class T, T ValueFirst, T... ValuesRest>
constexpr int product(const fatal::constant_sequence<T, ValueFirst, ValuesRest...>&) {
  return ValueFirst*product(fatal::constant_sequence<T, ValuesRest...>());
}

///////////
// count //
///////////

template<class T, T... Values, T Key>
constexpr int count(const fatal::constant_sequence<T, Values...>&
                  , const std::integral_constant<T, Key>&)
{
  return sum(fatal::constant_sequence<bool, (Key == Values)...>());
}

//////////
// and_ //
//////////

template<bool... Values>
constexpr bool and_(const fatal::constant_sequence<bool, Values...>& values) {
  return product(values);
}

/////////
// or_ //
/////////

template<bool... Values>
constexpr bool or_(const fatal::constant_sequence<bool, Values...>&) {
  return sum(fatal::constant_sequence<bool, Values...>()) > 0;
}

//////////////////////////
// to_constant_sequence //
//////////////////////////

template<class T, T... Values>
constexpr fatal::constant_sequence<T, Values...>
to_constant_sequence(const fatal::type_list<std::integral_constant<T, Values>...>&) {
  return {};
}

///////////
// slice //
///////////

template<int I, int J, class T, T... Values>
constexpr decltype(
  to_constant_sequence<T>(
    std::declval<typename fatal::constant_sequence<T, Values...>::list::template slice<I, J>>()
  )
) slice(const fatal::constant_sequence<T, Values...>&) {
  return {};
}

//////////
// left //
//////////

template<int I, class T, T... Values>
constexpr decltype(
  to_constant_sequence<T>(
    std::declval<typename fatal::constant_sequence<T, Values...>::list::template left<I>>()
  )
) left(const fatal::constant_sequence<T, Values...>&) {
  return {};
}

///////////
// right //
///////////

template<int I, class T, T... Values>
constexpr decltype(
  to_constant_sequence<T>(
    std::declval<typename fatal::constant_sequence<T, Values...>::list::template right<I>>()
  )
) right(const fatal::constant_sequence<T, Values...>&) {
  return {};
}

////////////
// remove //
////////////

template<class T, T... Values, T Key>
constexpr decltype(
  to_constant_sequence<T>(
    std::declval<typename fatal::constant_sequence<T, Values...>
                                  ::list::template remove<std::integral_constant<T, Key>>>()
  )
) remove(const fatal::constant_sequence<T, Values...>&
       , const std::integral_constant<T, Key>&) {
  return {};
}

//////////
// tail //
//////////

template<int I, class T, T... Values>
constexpr decltype(
  to_constant_sequence<T>(
    std::declval<typename fatal::constant_sequence<T, Values...>::list::template tail<I>>()
  )
) tail(const fatal::constant_sequence<T, Values...>&) {
  return {};
}

//////////////
// contains //
//////////////

template<class T, T... Values, T Key>
constexpr bool contains(const fatal::constant_sequence<T, Values...>&
                      , const std::integral_constant<T, Key>&) 
{
  return fatal::constant_sequence<T, Values...>
                    ::list::template contains<std::integral_constant<T, Key>>::value;
}

//////////
// find //
//////////

static constexpr int kNotFound = -1;

template<class T, T... Values, T Key>
constexpr int find(const fatal::constant_sequence<T, Values...>& values
                 , const std::integral_constant<T, Key>& key) 
{
  return contains(values, key) 
       ? fatal::constant_sequence<T, Values...>
              ::list
             ::template index_of<std::integral_constant<T, Key>>::value
       : kNotFound;
}

///////////////
// find_last //
///////////////

template<class T, T Key>
constexpr int find_last(const fatal::constant_sequence<T>& values
                      , const std::integral_constant<T, Key>& key)
{
  return kNotFound;
}

template<class T, T ValueFirst, T... ValuesRest, T Key>
constexpr int find_last(const fatal::constant_sequence<T, ValueFirst, ValuesRest...>& values
                      , const std::integral_constant<T, Key>& key)
{
  return contains(tail<1>(values), key)
       ? 1 + find_last(tail<1>(values), key)
       : (ValueFirst == Key ? 0 : kNotFound);
}

}} //end namespace
