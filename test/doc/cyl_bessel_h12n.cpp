#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout.precision(16);
  using w_t = eve::wide<double, eve::fixed<2>>;
  auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
  auto n = 3;
  std::cout << "z                    " << z << std::endl;
  std::vector<decltype(z)> h1n(4), h2n(4);
  kyosu::cyl_bessel_h12n(n, z, std::span(h1n), std::span(h2n));
  for(int n=0; n <= 3; ++n)
  {
    std::cout << "h1n[" << n << "] = " << h1n[n] << std::endl;
    std::cout << "h2n[" << n << "] = " << h2n[n] << std::endl;
  }
  return 0;
}
