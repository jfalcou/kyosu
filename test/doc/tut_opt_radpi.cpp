#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto pi = eve::pi(eve::as<double>());
  auto z  = kyosu::complex_t<double>(1., 0.);

  // A quarter turn: pi/2 in radians, or 0.5 half-turns.
  std::cout << "sin(pi/2 * z)        = " << kyosu::sin(pi/2 * z)              << "\n";
  std::cout << "sin[radpi](0.5 * z)  = " << kyosu::sin[kyosu::radpi](0.5 * z) << "\n";

  // The option form is exact where the other carries the error of pi.
  std::cout << "cos(pi * z)          = " << kyosu::cos(pi * z)                << "\n";
  std::cout << "cos[radpi](1. * z)   = " << kyosu::cos[kyosu::radpi](1. * z)  << "\n";
}
