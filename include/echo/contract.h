#pragma once

#include <echo/preprocessor.h>
#include <exception>
#include <stdexcept>
#include <cassert>

#define DETAIL_NS detail_contract

namespace echo {

namespace DETAIL_NS {
//------------------------------------------------------------------------------
// ScopeExit
//------------------------------------------------------------------------------
template <bool RunOnFailure, class Functor>
struct ScopeExit {
 public:
  ScopeExit(const Functor& functor) : _functor(functor) {}
  ScopeExit(const ScopeExit&) = default;
  ScopeExit(ScopeExit&&) = default;
  ~ScopeExit() noexcept(false) {
    // TODO: replace with a version using exception counts
    if (std::uncaught_exception() == RunOnFailure) _functor();
  }

 private:
  Functor _functor;
};

//------------------------------------------------------------------------------
// ContractExpect
//------------------------------------------------------------------------------
struct ContractExpect {};

template <class Functor>
void operator+(ContractExpect, Functor&& functor) {
  functor();
}

//------------------------------------------------------------------------------
// ContractEnsure
//------------------------------------------------------------------------------
struct ContractEnsure {};

template <class Functor>
auto operator+(ContractEnsure, Functor&& functor) {
  return ScopeExit<false, Functor>(functor);
}

//------------------------------------------------------------------------------
// ContractIgnore
//------------------------------------------------------------------------------
struct ContractIgnore {};

template <class Functor>
void operator+(ContractIgnore, Functor&&) {}
}

//------------------------------------------------------------------------------
// ContractViolation
//------------------------------------------------------------------------------
struct ContractViolation : virtual std::runtime_error {
  ContractViolation(const char* message) : std::runtime_error(message) {}
};
}

#ifdef ECHO_CONTRACT_VIOLATION_THROW
#define CONTRACT_ASSERT(CONDITION)                                         \
  if (!(CONDITION)) {                                                      \
    throw echo::ContractViolation("Contract \"" ECHO_STRINGIFY(            \
        CONDITION) "\" failed in " __FILE__ ":" ECHO_STRINGIFY(__LINE__)); \
  }
#else
#ifndef NDEBUG
#define CONTRACT_ASSERT(CONDITION) assert(CONDITION);
#else
#define CONTRACT_ASSERT(CONDITION)
#endif
#endif

#ifndef NDEBUG
#define CONTRACT_EXPECT echo::detail_contract::ContractExpect() + [&]
#define CONTRACT_ENSURE                               \
  auto ECHO_ANONYMOUS_VARIABLE(CONTRACT_ENSURE_VAR) = \
      echo::detail_contract::ContractEnsure() + [&]
#else
#define CONTRACT_EXPECT echo::detail_contract::ContractIgnore() + [&]
#define CONTRACT_ENSURE echo::detail_contract::ContractIgnore() + [&]
#endif

#undef DETAIL_NS
