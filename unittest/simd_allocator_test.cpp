#include <echo/simd_allocator.h>
#include <catch.hpp>

using namespace echo;

TEST_CASE("simd_allocator") {
  using Allocator = SimdAllocator<double>;  
  Allocator allocator;
  int n = 3;
  auto p = allocator.allocate(n);
  REQUIRE((reinterpret_cast<long>(p) % ECHO_SIMD_ALIGNMENT) == 0);
  allocator.deallocate(p, n);
}
