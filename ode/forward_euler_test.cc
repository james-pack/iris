#include "ode/forward_euler.h"

#include <functional>

#include "gtest/gtest.h"

namespace pack::ode {

TEST(ForwardEulerTest, CanCompile) {
  int deriv_call_count{0};
  std::function<double(double)> deriv = [&deriv_call_count](double) -> double {
    ++deriv_call_count;
    return 1.;
  };
  double time_step{1.};
  double u0{0.};
  auto integrator = forward_euler(0., u0, time_step, deriv);
  EXPECT_EQ(1., integrator(1.));
  EXPECT_EQ(1, deriv_call_count);
}

}  // namespace pack::ode
