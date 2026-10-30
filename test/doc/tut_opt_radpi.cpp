#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto pi = eve::pi(eve::as<double>());
  auto z  = kyosu::complex_t<double>(1., 0.);

  // A half turn, where the sine is zero.
  std::cout << "sin(pi * z)          = " << kyosu::sin(pi * z)                << "\n";
  std::cout << "sin[radpi](z)        = " << kyosu::sin[kyosu::radpi](z)       << "\n";

  // A million half turns: the rounding error of pi grows with the angle.
  std::cout << "sin(1e6 * pi * z)    = " << kyosu::sin(1e6 * pi * z)          << "\n";
  std::cout << "sin[radpi](1e6 * z)  = " << kyosu::sin[kyosu::radpi](1e6 * z) << "\n";
}
