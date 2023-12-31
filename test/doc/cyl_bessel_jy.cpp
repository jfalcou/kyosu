#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout.precision(16);
  using w_t = eve::wide<double, eve::fixed<2>>;
  auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
  auto v = 3.3;
  std::cout << "z                    " << z << std::endl;
  std::vector<decltype(z)> j(4), y(4);
  kyosu::cyl_bessel_jy(v, z, j, y);
  for(int n=0; n <= 3; ++n)
  {
    std::cout << "j[" << n << "] = " << j[n] << std::endl;
    std::cout << "y[" << n << "] = " << y[n] << std::endl;
  }
  return 0;
}
