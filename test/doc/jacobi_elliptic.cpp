#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  std::cout<< std::setprecision(16) << std::endl;
  using w_t = eve::wide<double, eve::fixed<2>>;
  auto z = kyosu::complex(w_t(2.0, 1.0), w_t(0.0, 1.0));
  auto m = w_t(0.5, 0.7);
  auto [sn, cn, dn] =  kyosu::jacobi_elliptic(z, m);
  std::cout << " z               " << z  << std::endl;
  std::cout << " m               " << m  << std::endl;
  std::cout << "sn(z, m)         " << sn << std::endl;
  std::cout << "cn(z, m)         " << cn << std::endl;
  std::cout << "dn(z, m)         " << dn << std::endl;
  return 0;
}
