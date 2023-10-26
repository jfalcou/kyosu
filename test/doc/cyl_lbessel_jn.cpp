#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
//#include <boost/math/tools/fraction.hpp>


int main()
{
  std::cout.precision(16);
  using w_t = eve::wide<double, eve::fixed<2>>;
  auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
//  auto z = kyosu::complex(1.0);
   for(int n=0; n <= 10; ++n)
   {
     auto jn = kyosu::cyl_lbessel_jn(n, z);
     std::cout << "n " << n  << " z " << z << std::endl;
     std::cout << jn << std::endl;
     std::cout << kyosu::log(kyosu::cyl_bessel_jn(n, z)) << std::endl;
//  std::cout << kyosu::_::lbesseljn(n, z) << std::endl;
  }
  return 0;
}
