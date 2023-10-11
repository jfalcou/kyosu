#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::cyl_bessel_jn;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  int n = 3;
  std::cout << "Real:     \n";
  std::cout << 3.0 << " -> " << cyl_bessel_jn(n, 3.0f) << "\n";
  std::cout << 63.0 << " -> " << cyl_bessel_jn(n, 63.0f) << "\n";

  std::cout << "Complex:  \n";
  std::cout << kyosu::complex_t<float>(3.0) << " -> " << cyl_bessel_jn(n, kyosu::complex_t<float>(3.0)) << "\n";
  std::cout << kyosu::complex_t<float>(63.0) << " -> " << cyl_bessel_jn(n, kyosu::complex_t<float>(63.0)) << "\n";

//  std::cout << "Quaternion:  ";
  std::cout << kyosu::quaternion_t<double>(3.0) << " -> " << cyl_bessel_jn(n, kyosu::quaternion_t<double>(3.0)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
  using w_t  = eve::wide<double, eve::fixed<2>>;
  using c_t  = kyosu::complex_t<double>;
  std::cout << w_t(63.0, 4.0) << " -> " << cyl_bessel_jn(n, wc_t(kyosu::complex_t<double>(63.0), kyosu::complex_t<double>(4.0))) << "\n";
  std::cout << w_t(63.0, 4.0) << " -> " << cyl_bessel_jn(n, w_t(63.0, 4.0)) << "\n";
  c_t a(17, 3);
  c_t b(3, -1);
  wc_t ab(a, b);
  std::cout << ab << " -> " << cyl_bessel_jn(n, ab) << "\n";
  std::cout << a << " -> " << cyl_bessel_jn(n, a) << "\n";

  return 0;
}
