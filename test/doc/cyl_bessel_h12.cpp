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
  std::vector<decltype(z)> h1(4), h2(4);
  kyosu::cyl_bessel_h12(v, z, std::span(h1), std::span(h2));
  for(int n=0; n <= 3; ++n)
  {
    std::cout << "h1[" << n << "] = " << h1[n] << std::endl;
    std::cout << "h2[" << n << "] = " << h2[n] << std::endl;
  }
  return 0;
}
