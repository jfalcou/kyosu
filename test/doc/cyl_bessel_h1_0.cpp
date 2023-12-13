#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout.precision(16);
  using w_t = eve::wide<double, eve::fixed<2>>;
  auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
  std::cout << "z " << z << std::endl;
  std::cout << "cyl_bessel_h1_0(z) " << kyosu::cyl_bessel_h1_0(z) << std::endl;
  return 0;
}
