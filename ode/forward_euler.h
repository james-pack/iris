#pragma once

#include <functional>

namespace pack::ode {

/**
 * Naive form of a forward_euler ODE integrator.
 *
 * TODO(james): Revisit API and implementation as requirements become more clear.
 */
template <typename Scalar, typename U>
auto forward_euler(Scalar start, const U& u0, Scalar time_step, std::function<U(Scalar)> deriv) {
  return [=](Scalar t) -> U {
    U result{u0};
    for (Scalar i = start; i < t; i += time_step) {
      result += time_step * deriv(i);
    }
    return result;
  };
}

}  // namespace pack::ode
