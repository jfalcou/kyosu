#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout.precision(16);
  using w_t = eve::wide<double, eve::fixed<2>>;
  auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
   for(int n=2; n <= 2; ++n)
   {
     auto h1n = kyosu::cyl_bessel_h2n(n, z);
     std::cout << "n " << n  << " z " << z << std::endl;
     std::cout << "yl_bessel_h2n(n, z) " << h1n << std::endl;
  }
  return 0;
}
