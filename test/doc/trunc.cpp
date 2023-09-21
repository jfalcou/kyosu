#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::trunc;
  using kyosu::as_complex_t;
  using kyosu::as_quaternion_t;

  std::cout << "Real:        ";
  std::cout << 72.9f << " -> " << trunc(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << kyosu::as_complex_t<float>(3.5f,-2.9f) << " -> " << trunc(kyosu::as_complex_t<float>(3.5f,-2.9f)) << "\n";

  std::cout << "Quaternion:  ";
  std::cout << kyosu::as_quaternion_t<double>(1.,2.,3.,4.) << " -> " << trunc(kyosu::as_quaternion_t<double>(1.,2.,3.,4.)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::as_complex_t<double>, eve::fixed<2>>;
  std::cout << wc_t(kyosu::as_complex_t<double>(1.3,-3.7)) << " -> " << trunc(wc_t(kyosu::as_complex_t<double>(1.3,-3.7))) << "\n";

  return 0;
}
