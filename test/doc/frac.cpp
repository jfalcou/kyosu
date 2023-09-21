#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::frac;
  using kyosu::as_complex_t;
  using kyosu::as_quaternion_t;

  std::cout << "Real:        ";
  std::cout << 72.9f << " -> " << frac(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << kyosu::as_complex_t<float>(3.5f,-2.9f) << " -> " << frac(kyosu::as_complex_t<float>(3.5f,-2.9f)) << "\n";

  std::cout << "Quaternion:  ";
  std::cout << kyosu::as_quaternion_t<double>(1.,2.,3.,4.) << " -> " << frac(kyosu::as_quaternion_t<double>(1.,2.,3.,4.)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::as_complex_t<double>, eve::fixed<2>>;
  std::cout << wc_t(kyosu::as_complex_t<double>(1.3,-3.7)) << " -> " << frac(wc_t(kyosu::as_complex_t<double>(1.3,-3.7))) << "\n";

  return 0;
}
