#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto z = kyosu::complex_t<double>(-1., 0.);

  // The argument of -1 is a half-turn, in radians or in multiples of pi.
  std::cout << "arg        = " << kyosu::arg(z)                 << "\n";
  std::cout << "arg[radpi] = " << kyosu::arg[kyosu::radpi](z)   << "\n";
}
