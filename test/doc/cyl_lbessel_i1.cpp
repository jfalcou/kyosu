#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout.precision(16);
  using w_t = eve::wide<double, eve::fixed<2>>;
  auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
//   auto z = kyosu::complex(30.0, 0.0);
//   auto zi= kyosu::complex(00.0, 30.0);
  //  auto z = kyosu::complex(1.0);
  auto in = kyosu::cyl_lbessel_i1(z);
  std::cout <<  "0 " << in << std::endl;
  auto login = kyosu::log(kyosu::cyl_bessel_i1(z));
  std::cout <<  "1 " << login << std::endl;
  return 0;
}
