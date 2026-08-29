#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto z = kyosu::complex_t<double>(0.5, 0.25);

  std::cout << "exp(z)       = " << kyosu::exp(z)         << "\n";
  std::cout << "log(z)       = " << kyosu::log(z)         << "\n";
  std::cout << "sin(z)       = " << kyosu::sin(z)         << "\n";
  std::cout << "tanh(z)      = " << kyosu::tanh(z)        << "\n";
  std::cout << "erf(z)       = " << kyosu::erf(z)         << "\n";
  std::cout << "tgamma(z)    = " << kyosu::tgamma(z)      << "\n";
  std::cout << "bessel_j(0, z) = " << kyosu::bessel_j(0, z)  << "\n";
  std::cout << "legendre(3, z) = " << kyosu::legendre(3, z) << "\n";
}
