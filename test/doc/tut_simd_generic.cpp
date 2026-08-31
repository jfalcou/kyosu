#include <iostream>
#include <kyosu/kyosu.hpp>

// One body, whatever the caller hands over.
auto energy(auto z) { return kyosu::sqr_abs(z) + kyosu::real(kyosu::exp(z)); }

int main()
{
  std::cout << "scalar : " << energy(kyosu::complex_t<double>(1., 2.)) << "\n";

  eve::wide<double> re = [](auto i, auto) { return 1.0 + i; };
  std::cout << "re                     " << re << "\n";
  std::cout << "kyosu::complex(re, re) " << kyosu::complex(re, re) << "\n";
  std::cout << "wide energy            " << energy(kyosu::complex(re, re)) << "\n";
}
