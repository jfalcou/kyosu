#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout.precision(16);
  using w_t = eve::wide<double, eve::fixed<2>>;
  auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
  std::cout << "z                    " << z << std::endl;
  std::vector<decltype(z)> is(4), ks(4);
  kyosu::cyl_bessel_ikn(3, z, is, ks);
  for(int n=0; n <= 3; ++n)
  {
    std::cout << "is[" << n << "] = " << is[n] << std::endl;
    std::cout << "ks[" << n << "] = " << ks[n] << std::endl;
  }
  return 0;
}
