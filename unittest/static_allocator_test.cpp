#include <echo/static_allocator.h>
#include <echo/concept.h>
#include <catch.hpp>

using namespace echo;

TEST_CASE("static_allocator") {
  using Allocator = StaticAllocator<double, 64>;
  Allocator::buffer_type<5> buffer;
  REQUIRE((reinterpret_cast<long>(buffer.data()) % 64l) == 0);
  REQUIRE(sizeof(buffer) >= 5*sizeof(double));
  REQUIRE(concept::is_static_allocator<Allocator>());
  REQUIRE(concept::is_allocator<Allocator>());

  // compilation error
  // using UnsupportedAllocator = StaticAllocator<double, 3>;
  // UnsupportedAllocator::buffer_type<1> unsupported_buffer;
}
