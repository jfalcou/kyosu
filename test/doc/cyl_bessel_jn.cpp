#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::cyl_bessel_jn;

  std::cout << "1.0                 " << " -> " << cyl_bessel_jn(3, 1.0) << "\n";
  std::cout << "1.0+36.0i           " << " -> " << cyl_bessel_jn(3, kyosu::complex(1.0, 36.0)) << "\n";
  std::cout << "1.0+36.0i+2.0j+1.5k " << " -> " << cyl_bessel_jn(3, kyosu::quaternion(1.0, 36.0, 2.0, 1.5)) << "\n";

  eve::wide<double, eve::fixed<2>> z1(1.0, 2.0),  z2(36.0, 0.5);
  auto z = kyosu::complex(z1, z2);
  std::cout << z << " -> " << cyl_bessel_jn(3, z) << "\n";

  return 0;
}
