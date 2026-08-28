#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  eve::wide<double, eve::fixed<2>> re(1., 3.), im(2., 4.);

  auto c = kyosu::complex(1., 2.);
  auto w = kyosu::complex(re, im);

  // The same call, on one value or on a register of them.
  std::cout << "scalar: " << c << " -> " << kyosu::sqr(c) << "\n";
  std::cout << "SIMD:   " << w << " -> " << kyosu::sqr(w) << "\n";
}
