#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{

  size_t n = 12;
  using kyosu::sph_bessel_jn;
  std::cout.precision(16);
  std::cout << std::scientific << std::endl;
  std::cout << "1.0             " << " -> " << sph_bessel_jn(n,1.0) << "\n";
  std::cout << "1+0i            " << " -> " << sph_bessel_jn(n,kyosu::complex(1.0, 0.0)) << "\n";
  std::cout << "15.0            " << " -> " << sph_bessel_jn(n,15.0) << "\n";
  std::cout << "15+0i           " << " -> " << sph_bessel_jn(n,kyosu::complex(15.0, 0.0)) << "\n";
  std::cout << "40.0            " << " -> " << sph_bessel_jn(n,40.0) << "\n";
  std::cout << "40+0i           " << " -> " << sph_bessel_jn(n,kyosu::complex(40.0, 0.0)) << "\n";
  std::cout << "60.0            " << " -> " << sph_bessel_jn(n,60.0) << "\n";
  std::cout << "60+0i           " << " -> " << sph_bessel_jn(n,kyosu::complex(60.0, 0.0)) << "\n";

  eve::wide<double, eve::fixed<4>> z(1.0, 15.0, 40.0, 60.0);
  auto zz = kyosu::complex(z);
  std::cout << z  << "\n -> " << sph_bessel_jn(n,z) << "\n";
  std::cout << zz << "\n -> " << kyosu::real(sph_bessel_jn(n,zz)) << "\n";

  std::cout << "1.0                 " << " -> " << sph_bessel_jn(n,1.0) << "\n";
  std::cout << "1.0+36.0i           " << " -> " << sph_bessel_jn(n,kyosu::complex(1.0, 36.0)) << "\n";
  std::cout << "1.0+36.0i+2.0j+1.5k " << " -> " << sph_bessel_jn(n,kyosu::quaternion(1.0, 36.0, 2.0, 1.5)) << "\n";


  eve::wide<double, eve::fixed<4>> z1(1.0, 2.0, 40.0, 0.0),  z2(36.0, 0.5, 0.0, 40.0);
  auto z0 = kyosu::complex(z1, z2);
  std::cout << z0 << " \n-> " << sph_bessel_jn(n,z0) << "\n";


  for(int i=75; i < 100; ++i)
    std::cout << "i " << i << " -> " << kyosu::sph_bessel_jn(i,kyosu::complex(1.0, 1.0)) << "\n";


  return 0;
}
