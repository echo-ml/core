#pragma once

#include <boost/type_index.hpp>
#include <type_traits>
#include <catch.hpp>
#include <cmath>

#define STATIC_EQUAL(TYPE, X, Y) \
  REQUIRE((std::integral_constant<TYPE, (X)>()) == (std::integral_constant<TYPE, (Y)>()));

#define REQUIRE_NEAR(X, Y) \
  REQUIRE((X > 0 ? std::abs((X-Y)/X) : std::abs(X-Y)) < 0.01);

namespace echo {

template<class T1, class T2>
void type_equal() {
  auto lhs = boost::typeindex::type_id<T1>().pretty_name();
  auto rhs = boost::typeindex::type_id<T2>().pretty_name();
  REQUIRE(lhs == rhs);
}

} //end namespace
