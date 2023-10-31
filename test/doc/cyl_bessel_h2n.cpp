#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout.precision(16);
 // using w_t = eve::wide<double, eve::fixed<2>>;
  //auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
  auto z = kyosu::complex(30.0, 0.0);
//  auto z = kyosu::complex(1.0);
   for(int n=2; n <= 2; ++n)
   {
     auto h2n = kyosu::cyl_bessel_h2n(n, z);
     std::cout << "n " << n  << " z " << z << std::endl;
     std::cout <<  "0 " << h2n << std::endl;
     std::cout <<  "2 " << kyosu::cyl_bessel_h2n(n, 30.0) << std::endl;
  }
  return 0;
}
