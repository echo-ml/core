#pragma once

#include <echo/enable_if.h>
#include <boost/array.hpp>

namespace echo {

using IndexInteger = int;

template<int N>
class Index 
  : public boost::array<IndexInteger, N>
{
  using Base = boost::array<IndexInteger, N>;
 public:
  Index() {}

  template<class... Indexes>
  Index(Indexes... indexes) 
    : Base({indexes...}) 
  {
    static_assert(sizeof...(Indexes) == N, "");
  }
};

template<>
class Index<1>
  : public boost::array<IndexInteger, 1>
{
 public:
  Index() {}
  explicit Index(int i) : boost::array<IndexInteger, 1>({i}) {}

  operator IndexInteger() { return this->operator[](0); }
};

template<int I, int N>
IndexInteger get(const Index<N>& index) {
  static_assert(0 <= I && I < N, "");
  return index[I];
}

template<IndexInteger... Values>
struct StaticIndex 
  : fatal::constant_sequence<IndexInteger, Values...>
{
};

template<IndexInteger I>
struct StaticIndex<I>
  : std::integral_constant<IndexInteger, I>
  , fatal::constant_sequence<IndexInteger, I>
{
  constexpr operator IndexInteger() const {
    return I;
  }
  constexpr IndexInteger operator()() const {
    return I;
  }
};

template<int I, IndexInteger... Values>
constexpr auto get(const StaticIndex<Values...>&) ->
    StaticIndex<StaticIndex<Values...>::list::template at<I>::value>
{
  static_assert(0 <= I && I < sizeof...(Values), "");
  return {};
}

#define MAKE_COMPARISON_OPERATOR(OPERATOR) \
  template<IndexInteger Lhs, IndexInteger Rhs> \
  constexpr std::integral_constant<bool, (Lhs OPERATOR Rhs)> \
  operator OPERATOR (const StaticIndex<Lhs>& lhs, const StaticIndex<Rhs>& rhs) { \
    return {}; \
  }

MAKE_COMPARISON_OPERATOR(<)
MAKE_COMPARISON_OPERATOR(>)
MAKE_COMPARISON_OPERATOR(<=)
MAKE_COMPARISON_OPERATOR(>=)
MAKE_COMPARISON_OPERATOR(==)

#undef MAKE_COMPARISON_OPERATOR

#define MAKE_ARITHMETIC_OPERATOR(OPERATOR) \
  template<IndexInteger Lhs, IndexInteger Rhs> \
  constexpr StaticIndex<(Lhs OPERATOR Rhs)> \
  operator OPERATOR (const StaticIndex<Lhs>& lhs, const StaticIndex<Rhs>& rhs) { \
    return {}; \
  }

MAKE_ARITHMETIC_OPERATOR(+)
MAKE_ARITHMETIC_OPERATOR(-)
MAKE_ARITHMETIC_OPERATOR(*)
MAKE_ARITHMETIC_OPERATOR(/)
MAKE_ARITHMETIC_OPERATOR(%)

#undef MAKE_ARITHMETIC_OPERATOR

} //end namespace
