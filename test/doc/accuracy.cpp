#include <iostream>
#include <limits>
#include <kyosu/kyosu.hpp>

int main()
{
  auto inf = std::numeric_limits<double>::infinity();
  auto nan = std::numeric_limits<double>::quiet_NaN();
  auto z   = kyosu::complex(inf, nan);

  // The default is IEEE754-conforming: an infinite component wins over a NaN one.
  // raw skips that check and lets the NaN propagate.
  std::cout << "abs      = " << kyosu::abs(z)             << "\n";
  std::cout << "abs[raw] = " << kyosu::abs[kyosu::raw](z) << "\n";
}
