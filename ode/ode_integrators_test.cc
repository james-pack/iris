#include <functional>

#include "gtest/gtest.h"
#include "ode/backward_euler.h"
#include "ode/forward_euler.h"

namespace pack::ode {

TEST(ForwardEulerTest, IntegratorCorrectOnFirstStep) {
  int deriv_call_count{0};
  std::function<double(double)> deriv = [&deriv_call_count](double) -> double {
    ++deriv_call_count;
    return 1.;
  };
  double time_step{1.};
  auto integrator = ForwardEuler(0., 0., time_step, deriv);
  EXPECT_EQ(1., integrator());
  EXPECT_EQ(1, deriv_call_count);
}

TEST(ForwardEulerTest, ReturnedIntegratorCanBeCalledMultipleTimes) {
  int deriv_call_count{0};
  std::function<double(double)> deriv = [&deriv_call_count](double) -> double {
    ++deriv_call_count;
    return 1.;
  };
  double time_step{1.};
  auto integrator = ForwardEuler(0., 0., time_step, deriv);
  EXPECT_EQ(time_step, integrator());
  EXPECT_EQ(2. * time_step, integrator());
  EXPECT_EQ(2, deriv_call_count);
}

TEST(BackwardEulerTest, IntegratorCorrectOnFirstStep) {
  int deriv_call_count{0};
  std::function<double(double)> deriv = [&deriv_call_count](double) -> double {
    ++deriv_call_count;
    return 1.;
  };
  double time_step{1.};
  auto integrator = BackwardEuler(0., 0., time_step, deriv);
  EXPECT_EQ(1., integrator());
  EXPECT_EQ(1, deriv_call_count);
}

TEST(BackwardEulerTest, ReturnedIntegratorCanBeCalledMultipleTimes) {
  int deriv_call_count{0};
  std::function<double(double)> deriv = [&deriv_call_count](double) -> double {
    ++deriv_call_count;
    return 1.;
  };
  double time_step{1.};
  auto integrator = BackwardEuler(0., 0., time_step, deriv);
  EXPECT_EQ(time_step, integrator());
  EXPECT_EQ(2. * time_step, integrator());
  EXPECT_EQ(2, deriv_call_count);
}

}  // namespace pack::ode
