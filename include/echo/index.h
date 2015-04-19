#pragma once

#include <echo/enable_if.h>
#include <boost/array.hpp>

namespace echo {

// deprecated
using IndexInteger = int;

using index_t = int;

///////////
// Index //
///////////

template <int N>
class Index {
 public:
  Index() {}

  template <class... Indexes>
  Index(Indexes... indexes)
      : _indexes({indexes...}) {
    static_assert(sizeof...(Indexes) == N, "");
  }

  index_t& operator[](int i) { return _indexes[i]; }
  index_t operator[](int i) const { return _indexes[i]; }
  const index_t* begin() const { return _indexes.begin(); }
  const index_t* end() const { return _indexes.end(); }
  index_t* begin() { return _indexes.begin(); }
  index_t* end() { return _indexes.end(); }

 private:
  boost::array<index_t, N> _indexes;
};

template <>
class Index<1> {
 public:
  Index() {}
  explicit Index(int i) : _index(i) {}

  operator index_t() { return _index; }

  index_t& operator[](int i) { return _index; }
  index_t operator[](int i) const { return _index; }
  const index_t* begin() const { return &_index; }
  const index_t* end() const { return &_index + 1; }
  index_t* begin() { return &_index; }
  index_t* end() { return &_index + 1; }

 private:
  index_t _index;
};

template <>
class Index<0> {
 public:
  Index() {}
  const index_t* begin() const { return nullptr; }
  const index_t* end() const { return nullptr; }
  index_t* begin() { return nullptr; }
  index_t* end() { return nullptr; }
};

/////////
// get //
/////////

template <int I, int N>
index_t get(const Index<N>& index) {
  static_assert(0 <= I && I < N, "");
  return index[I];
}

/////////////////
// StaticIndex //
/////////////////

template <index_t... Values>
struct StaticIndex : fatal::constant_sequence<index_t, Values...> {};

template <index_t I>
struct StaticIndex<I> : std::integral_constant<index_t, I>,
                        fatal::constant_sequence<index_t, I> {
  constexpr operator index_t() const { return I; }
  constexpr index_t operator()() const { return I; }
  constexpr StaticIndex<-I> operator-() const { return {}; }
};

/////////
// get //
/////////

template <int I, index_t... Values>
constexpr auto get(const StaticIndex<Values...>&)
    -> StaticIndex<StaticIndex<Values...>::list::template at<I>::value> {
  static_assert(0 <= I && I < sizeof...(Values), "");
  return {};
}

/////////////////
// ParseDigits //
/////////////////

namespace detail {

template <index_t Value, char...>
struct ParseDigitsImpl {
  static constexpr index_t value = Value;
};

template <index_t Value, char First, char... Rest>
struct ParseDigitsImpl<Value, First, Rest...> {
  static constexpr index_t value =
      ParseDigitsImpl<10 * Value + (First - '0'), Rest...>::value;
};

template <char First, char... Rest>
struct ParseDigits {
  static constexpr index_t value = ParseDigitsImpl<0, First, Rest...>::value;
};

}  // end namespace detail

/////////////////////
// index - literal //
/////////////////////

template <char... Chars>
constexpr auto operator"" _index() {
  return StaticIndex<detail::ParseDigits<Chars...>::value>{};
}

///////////////////////////
// arithmetic operations //
///////////////////////////

#define MAKE_COMPARISON_OPERATOR(OPERATOR)                   \
  template <index_t Lhs, index_t Rhs>                        \
  constexpr std::integral_constant<bool, (Lhs OPERATOR Rhs)> \
  operator OPERATOR(const StaticIndex<Lhs>& lhs,             \
                    const StaticIndex<Rhs>& rhs) {           \
    return {};                                               \
  }

MAKE_COMPARISON_OPERATOR(< )
MAKE_COMPARISON_OPERATOR(> )
MAKE_COMPARISON_OPERATOR(<= )
MAKE_COMPARISON_OPERATOR(>= )
MAKE_COMPARISON_OPERATOR(== )

#undef MAKE_COMPARISON_OPERATOR

#define MAKE_ARITHMETIC_OPERATOR(OPERATOR)                        \
  template <index_t Lhs, index_t Rhs>                             \
  constexpr StaticIndex<(Lhs OPERATOR Rhs)> operator OPERATOR(    \
      const StaticIndex<Lhs>& lhs, const StaticIndex<Rhs>& rhs) { \
    return {};                                                    \
  }

MAKE_ARITHMETIC_OPERATOR(+)
MAKE_ARITHMETIC_OPERATOR(-)
MAKE_ARITHMETIC_OPERATOR(*)
MAKE_ARITHMETIC_OPERATOR(/ )
MAKE_ARITHMETIC_OPERATOR(% )

#undef MAKE_ARITHMETIC_OPERATOR

}  // namespace echo
