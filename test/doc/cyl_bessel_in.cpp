#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::cyl_bessel_in;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  int n = 3;
  std::cout << "Real:     \n";
  std::cout << 3.0 << " -> " << cyl_bessel_in(n, 3.0f) << "\n";
  std::cout << 63.0 << " -> " << cyl_bessel_in(n, 63.0f) << "\n";

  std::cout << "Complex:  \n";
  std::cout << kyosu::complex(3.0) << " -> " << cyl_bessel_in(n, kyosu::complex(3.0)) << "\n";
  std::cout << kyosu::complex(63.0) << " -> " << cyl_bessel_in(n, kyosu::complex(63.0)) << "\n";

//  std::cout << "Quaternion:  ";
  std::cout << kyosu::quaternion_t<double>(3.0) << " -> " << cyl_bessel_in(n, kyosu::quaternion_t<double>(3.0)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
  using w_t  = eve::wide<double, eve::fixed<2>>;
  using c_t  = kyosu::complex_t<double>;
  std::cout << w_t(63.0, 3.0) << " -> " << cyl_bessel_in(n, wc_t(kyosu::complex_t<double>(63.0), kyosu::complex_t<double>(3.0))) << "\n";
  std::cout << w_t(63.0, 3.0) << " -> " << cyl_bessel_in(n, w_t(63.0, 3.0)) << "\n";
  c_t a(17, 3);
  c_t b(3, -1);
  wc_t ab(a, b);
  std::cout << ab << " -> " << cyl_bessel_in(n, ab) << "\n";
  std::cout << a << " -> " << cyl_bessel_in(n, a) << "\n";
  std::cout << b << " -> " << cyl_bessel_in(n, b) << "\n";

  return 0;
}
