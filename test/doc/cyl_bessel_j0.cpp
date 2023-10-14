#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::cyl_bessel_j0;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  std::cout << "Real:        ";
//   std::cout << 3.0 << " -> " << cyl_bessel_j0(3.0) << "\n";
//   std::cout << 36.0 << " -> " << cyl_bessel_j0(36.0) << "\n";
//    std::cout << "3.0i " << " -> " << cyl_bessel_j0(kyosu::complex(0.0, 3.0)) << "\n";
  std::cout << "1+36.0i " << " -> " << cyl_bessel_j0(kyosu::complex(1.0, 36.0)) << "\n";

//   std::cout << "Complex:     ";
//   std::cout << kyosu::complex_t<float>(3.0) << " -> " << cyl_bessel_j0(kyosu::complex_t<float>(3.0)) << "\n";
//   std::cout << kyosu::complex_t<float>(36.0) << " -> " << cyl_bessel_j0(kyosu::complex_t<float>(36.0)) << "\n";

//   std::cout << "Quaternion:  ";
//   std::cout << kyosu::quaternion_t<double>(3.0) << " -> " << cyl_bessel_j0(kyosu::quaternion_t<double>(3.0)) << "\n";

//   std::cout << "SIMD:        ";
//   using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
//   using w_t  = eve::wide<double, eve::fixed<2>>;
//   using c_t  = kyosu::complex_t<double>;
//   std::cout << w_t(63.0, 4.0) << " -> " << cyl_bessel_j0(wc_t(kyosu::complex_t<double>(63.0), kyosu::complex_t<double>(4.0))) << "\n";
//   std::cout << w_t(63.0, 4.0) << " -> " << cyl_bessel_j0(w_t(63.0, 4.0)) << "\n";
//   c_t a(17, 3);
//   c_t b(3, -1);
//   wc_t ab(a, b);
//    std::cout << ab << " -> " << cyl_bessel_j0(ab) << "\n";

  return 0;
}
