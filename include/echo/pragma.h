#pragma once

#ifdef __INTEL_COMPILER
#define ECHO_PRAGMA_NONTEMPORAL _Pragma("vector nontemporal")
#define ECHO_PRAGMA_SIMD _Pragma("simd")
#define ECHO_PRAGMA_ALIGNED _Pragma("vector aligned")
#define ECHO_PRAGMA_SUGGEST_INLINE _Pragma("inline recursive")
#define ECHO_PRAGMA_FORCE_INLINE _Pragma("forceinline recursive")
#else
#define ECHO_PRAGMA_NONTEMPORAL 
#define ECHO_PRAGMA_SIMD _Pragma("omp simd")
#define ECHO_PRAGMA_ALIGNED
#define ECHO_PRAGMA_SUGGEST_INLINE
#define ECHO_PRAGMA_FORCE_INLINE
#endif
