#include <echo/concept.h>
#include <catch.hpp>
#include <memory>
#include <list>

using namespace echo;

TEST_CASE("concept tests") {

  SECTION("is_copyable") {
    REQUIRE(concept::is_copyable<double>());
    REQUIRE(!concept::is_copyable<std::unique_ptr<double>>());
  }

  SECTION("is_random_access_iterator") {
    REQUIRE(concept::is_random_access_iterator<float*>());
    REQUIRE(!concept::is_random_access_iterator<std::list<float>::iterator>());
  }


  // REQUIRE(3 == 4);
}
