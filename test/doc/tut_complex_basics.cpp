#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto z = kyosu::complex_t<double>(3., 4.);

  std::cout << "z         = " << z                 << "\n";
  std::cout << "real(z)   = " << kyosu::real(z)    << "\n";
  std::cout << "imag(z)   = " << kyosu::imag(z)    << "\n";
  std::cout << "conj(z)   = " << kyosu::conj(z)    << "\n";
  std::cout << "abs(z)    = " << kyosu::abs(z)     << "\n";
  std::cout << "arg(z)    = " << kyosu::arg(z)     << "\n";
  std::cout << "z * z     = " << z * z             << "\n";
}
