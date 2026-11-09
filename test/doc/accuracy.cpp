#include <iostream>
#include <limits>
#include <kyosu/kyosu.hpp>

int main()
{
  auto inf = std::numeric_limits<double>::infinity();
  auto nan = std::numeric_limits<double>::quiet_NaN();
  auto z   = kyosu::complex(inf, nan);

  // By default, the modulus of a value with an infinite component is infinite, even with a NaN
  // component. raw skips that check and returns NaN.
  std::cout << "abs      = " << kyosu::abs(z)             << "\n";
  std::cout << "abs[raw] = " << kyosu::abs[kyosu::raw](z) << "\n";
}
