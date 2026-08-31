#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  eve::wide<double> re = [](auto i, auto) { return 1.0 + i; };
  eve::wide<double> im = [](auto i, auto) { return 0.5 * i; };

  auto z = kyosu::complex(re, im);

  std::cout << "z      = " << z             << "\n";
  std::cout << "abs(z) = " << kyosu::abs(z) << "\n";
  std::cout << "exp(z) = " << kyosu::exp(z) << "\n";
}
