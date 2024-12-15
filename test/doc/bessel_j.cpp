#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  std::cout<< std::setprecision(16) << std::endl;
  using w_t = eve::wide<double, eve::fixed<2>>;
  auto z = kyosu::complex(w_t(20.0, 1.5), w_t(0.0, 1.5));
  auto v = -(2+1/3.0);
  int nb = int(eve::abs(v)+1);
  std::cout << "z                    " << z << std::endl;
  std::vector<decltype(z)> js(nb);
  kyosu::bessel_j(v, z, std::span(js));
  auto inc = eve::sign(v);
  auto v0 =  eve::frac(v);
  for(int n=0; n < nb; ++n)
  {
    std::cout << "js[" << n << "]              = " << js[n] << std::endl;
    std::cout << "bessel_j[cylindrical](v0, z) = " << kyosu::bessel_j(v0, z) << std::endl;
    v0 += inc;
  }
  return 0;
}
