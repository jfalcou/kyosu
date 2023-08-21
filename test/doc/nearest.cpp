#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::nearest;
  using kyosu::complex;
  using kyosu::quaternion;

  std::cout << "Real:        ";
  std::cout << 72.9f << " -> " << nearest(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << complex<float>(3.5f,-2.9f) << " -> " << nearest(complex<float>(3.5f,-2.9f)) << "\n";

  std::cout << "Quaternion:  ";
  std::cout << quaternion<double>(1.,2.,3.,4.) << " -> " << nearest(quaternion<double>(1.,2.,3.,4.)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<complex<double>, eve::fixed<2>>;
  std::cout << wc_t(complex<double>(1.3,-3.7)) << " -> " << nearest(wc_t(complex<double>(1.3,-3.7))) << "\n";

  return 0;
}
