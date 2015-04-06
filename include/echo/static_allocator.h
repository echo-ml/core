#pragma once

#include <echo/simd_allocator.h>

namespace echo {

////////////////////////
// StaticMemoryBuffer //
////////////////////////

template <class Scalar, int NumElements, int Alignment>
class StaticMemoryBuffer {
  static_assert(NumElements != NumElements,
                "Buffer with given alignment is not supported");
};

template <class Scalar, int NumElements>
class StaticMemoryBuffer<Scalar, NumElements, 0> {
 public:
  Scalar* data() { return _data; }
  const Scalar* data() const { return _data; }
  const Scalar* const_data() const { return _data; }

 private:
  Scalar _data[NumElements];
};

#define MAKE_STATIC_MEMORY_BUFFER(ALIGNMENT)               \
  template <class Scalar, int NumElements>                 \
  class alignas(ALIGNMENT)                                 \
      StaticMemoryBuffer<Scalar, NumElements, ALIGNMENT> { \
   public:                                                 \
    Scalar* data() { return _data; }                       \
    const Scalar* data() const { return _data; }           \
    const Scalar* const_data() const { return _data; }     \
                                                           \
   private:                                                \
    Scalar _data[NumElements];                             \
  };

MAKE_STATIC_MEMORY_BUFFER(1)
MAKE_STATIC_MEMORY_BUFFER(32)
MAKE_STATIC_MEMORY_BUFFER(64)
MAKE_STATIC_MEMORY_BUFFER(128)

#undef MAKE_STATIC_MEMORY_BUFFER

/////////////////////
// StaticAllocator //
/////////////////////

template <class Scalar, int Alignment = 0>
struct StaticAllocator {
  template <int NumElements>
  using buffer_type = StaticMemoryBuffer<Scalar, NumElements, Alignment>;
};

template <class Scalar>
using SimdStaticAllocator = StaticAllocator<Scalar, ECHO_SIMD_ALIGNMENT>;

}  // end namespace echo
