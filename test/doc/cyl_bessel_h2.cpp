#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout.precision(16);
  using w_t = eve::wide<double, eve::fixed<2>>;
  auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
  auto v = 0.0;
  std::cout << "z                    " << z << std::endl;
  for(int n=0; n <= 3; ++n)
  {
    auto h2 = kyosu::cyl_bessel_h2(v, z);
    std::cout << "v                  " << v  << std::endl;
    std::cout << "yl_bessel_h2(v, z) " << h2 << std::endl;
    v = v+0.25;
  }
  return 0;
}
