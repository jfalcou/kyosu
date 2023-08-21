#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::trunc;
  using kyosu::complex;
  using kyosu::quaternion;

  std::cout << "Real:        ";
  std::cout << 72.9f << " -> " << trunc(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << complex<float>(3.5f,-2.9f) << " -> " << trunc(complex<float>(3.5f,-2.9f)) << "\n";

  std::cout << "Quaternion:  ";
  std::cout << quaternion<double>(1.,2.,3.,4.) << " -> " << trunc(quaternion<double>(1.,2.,3.,4.)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<complex<double>, eve::fixed<2>>;
  std::cout << wc_t(complex<double>(1.3,-3.7)) << " -> " << trunc(wc_t(complex<double>(1.3,-3.7))) << "\n";

  return 0;
}
