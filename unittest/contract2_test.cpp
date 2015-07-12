#define NDEBUG
#include <echo/contract.h>
#include <echo/test.h>

using namespace echo;

static double f1(double x) {
  CONTRACT_EXPECT {
    CONTRACT_ASSERT(x > 0);
  };
  return x*x;
}

static double f2(double x) {
  double result = 0;
  CONTRACT_ENSURE {
    CONTRACT_ASSERT(result >= 0);
  };
  result = 2*x;
  return result;
}

TEST_CASE("contract2") {
  f1(2.0);
  CHECK_NOTHROW(f1(-1));
  f2(1.0);
  CHECK_NOTHROW(f2(-2));
}

