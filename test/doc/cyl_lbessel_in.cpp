#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout.precision(16);
 // using w_t = eve::wide<double, eve::fixed<2>>;
  //auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
  auto z = kyosu::complex(30.0, 0.0);
  auto zi= kyosu::complex(00.0, 30.0);
//  auto z = kyosu::complex(1.0);
   for(int n=2; n <= 2; ++n)
   {
     auto in = kyosu::cyl_lbessel_in(n, z);
     std::cout << "n " << n  << " z " << z << std::endl;
     std::cout <<  "0 " << in << std::endl;
     std::cout <<  "1 " << kyosu::cyl_bessel_in(n, z) << std::endl;
     std::cout <<  "2 " << kyosu::cyl_bessel_jn(n, zi) << std::endl;
     std::cout <<  "3 " << kyosu::cyl_bessel_in(n, 20.0) << std::endl;
     auto login = kyosu::log(kyosu::cyl_bessel_in(n, z));
     std::cout <<  "4 " << login << std::endl;
     std::cout <<  "5 " << kyosu::exp(in) << std::endl;
     std::cout <<  "6 " << kyosu::exp(login) << std::endl;
  }
  return 0;
}
