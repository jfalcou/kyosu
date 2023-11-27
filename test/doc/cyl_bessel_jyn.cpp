#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>

int main()
{
  using kyosu::cyl_bessel_jyn;
  using z_t = kyosu::complex_t<double>;
//  using w_t = eve::wide<double, eve::fixed<2>>;
//  using wz_t = kyosu::complex_t<w_t>;
  std::cout.precision(16);
  std::cout << std::scientific << std::endl;
  int n = 5;
  int sn = eve::sign(n);
  int nn = abs(n);
//   std::vector<wz_t> js(n+1), ys(n+1);
     std::vector< z_t> js(nn+1), ys(nn+1);
//   auto r = w_t{1.0e-50, -2.0};
//   auto i = w_t{1.0e-50, 3.0};
//  auto z = kyosu::complex(r, i);
//  auto z = kyosu::complex(1.0e-50, 1.0e-50);
//  auto z = kyosu::complex(-2.0, 3.0);
     auto z = eve::eps(eve::as<double>());
//  auto z = 2.0;
  auto [jn, yn] =  cyl_bessel_jyn(n, z, js, ys);
  std::cout << "jn = " << jn << std::endl;
  std::cout << "yn = " << yn << std::endl;
  std::cout << std::endl;
  for(int i=0; i <= nn ; ++i)
  {
    std::cout << "j[" << i << "] = " << js[i] << "vs " << kyosu::cyl_bessel_jn(sn*i, z) << std::endl;
  }
  std::cout << std::endl;
  for(int i=0; i <= nn ; ++i)
  {
    std::cout << "y[" << i << "] = " << ys[i] << "vs " << kyosu::cyl_bessel_yn(sn*i, z) << std::endl;
  }
  return 0;
}
