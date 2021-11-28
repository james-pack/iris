#pragma once

#include <functional>

namespace pack::ode {

/**
 * Naive form of a backward Euler ODE integrator.
 *
 * TODO(james): Revisit API and implementation as requirements become more clear.
 */
template <typename U, typename TimeT>
class BackwardEuler final {
 private:
  U prev_value_;
  TimeT t_;
  const TimeT time_step_;
  const std::function<U(TimeT)> deriv_;

 public:
  BackwardEuler(TimeT start, const U& u0, TimeT time_step, std::function<U(TimeT)> deriv)
      : prev_value_(u0), t_(start), time_step_(time_step), deriv_(deriv) {}

  const U& operator()() {
    prev_value_ += time_step_ * deriv_(t_);
    t_ += time_step_;
    return prev_value_;
  }
};

}  // namespace pack::ode
