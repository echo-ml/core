#pragma once

#include <echo/enable_if.h>
#include <boost/array.hpp>

namespace echo {

using IndexInteger = int;

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

  IndexInteger& operator[](int i) { return _indexes[i]; }
  IndexInteger operator[](int i) const { return _indexes[i]; }
  const IndexInteger* begin() const { return _indexes.begin(); }
  const IndexInteger* end() const { return _indexes.end(); }
  IndexInteger* begin() { return _indexes.begin(); }
  IndexInteger* end() { return _indexes.end(); }

 private:
  boost::array<IndexInteger, N> _indexes;
};

template <>
class Index<1> {
 public:
  Index() {}
  explicit Index(int i) : _index(i) {}

  operator IndexInteger() { return _index; }

  IndexInteger& operator[](int i) { return _index; }
  IndexInteger operator[](int i) const { return _index; }
  const IndexInteger* begin() const { return &_index; }
  const IndexInteger* end() const { return &_index + 1; }
  IndexInteger* begin() { return &_index; }
  IndexInteger* end() { return &_index + 1; }

 private:
  IndexInteger _index;
};

template <>
class Index<0> {
 public:
  Index() {}
  const IndexInteger* begin() const { return nullptr; }
  const IndexInteger* end() const { return nullptr; }
  IndexInteger* begin() { return nullptr; }
  IndexInteger* end() { return nullptr; }
};

/////////
// get //
/////////

template <int I, int N>
IndexInteger get(const Index<N>& index) {
  static_assert(0 <= I && I < N, "");
  return index[I];
}

/////////////////
// StaticIndex //
/////////////////

template <IndexInteger... Values>
struct StaticIndex : fatal::constant_sequence<IndexInteger, Values...> {};

template <IndexInteger I>
struct StaticIndex<I> : std::integral_constant<IndexInteger, I>,
                        fatal::constant_sequence<IndexInteger, I> {
  constexpr operator IndexInteger() const { return I; }
  constexpr IndexInteger operator()() const { return I; }
  constexpr StaticIndex<-I> operator-() const { return {}; }
};

/////////
// get //
/////////

template <int I, IndexInteger... Values>
constexpr auto get(const StaticIndex<Values...>&)
    -> StaticIndex<StaticIndex<Values...>::list::template at<I>::value> {
  static_assert(0 <= I && I < sizeof...(Values), "");
  return {};
}

/////////////////
// ParseDigits //
/////////////////

namespace detail {

template <IndexInteger Value, char...>
struct ParseDigitsImpl {
  static constexpr IndexInteger value = Value;
};

template <IndexInteger Value, char First, char... Rest>
struct ParseDigitsImpl<Value, First, Rest...> {
  static constexpr IndexInteger value =
      ParseDigitsImpl<10 * Value + (First - '0'), Rest...>::value;
};

template <char First, char... Rest>
struct ParseDigits {
  static constexpr IndexInteger value =
      ParseDigitsImpl<0, First, Rest...>::value;
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
  template <IndexInteger Lhs, IndexInteger Rhs>              \
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
  template <IndexInteger Lhs, IndexInteger Rhs>                   \
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
