#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  std::cout<< std::setprecision(16) << std::endl;
  using w_t = eve::wide<double, eve::fixed<4>>;
  auto z = kyosu::complex(w_t(2.0, 1.0, 1.0, 0.0 ), w_t(1.0, 1.0, 0.0, 1.0));
  auto m = w_t(0.5);
//   auto z = kyosu::complex(0.0, 1.0);
//   auto m =0.5;
  auto [f, e] =  kyosu::elliptic_fe(z, eve::sqrt(m));
  std::cout << " z               " << z  << std::endl;
  std::cout << " m               " << m  << std::endl;
  std::cout << "f                " << f << std::endl;
  std::cout << "e                " << e << std::endl;
  return 0;
}
