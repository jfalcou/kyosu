#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using kyosu::rot_angle;

  //   std::cout << "Real:        ";
  //   std::cout << 72.9f << " -> " << rot_angle(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << kyosu::complex_t<float>(3.5f, -2.9f) << " -> " << rot_angle(kyosu::complex_t<float>(3.5f, -2.9f))
            << "\n";

  std::cout << "Quaternion:  ";
  std::cout << kyosu::quaternion_t<double>(1., 2., 3., 4.) << " -> "
            << rot_angle(kyosu::quaternion_t<double>(1., 2., 3., 4.)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
  std::cout << wc_t(kyosu::complex_t<double>(1.3, -3.7)) << " -> "
            << rot_angle(wc_t(kyosu::complex_t<double>(1.3, -3.7))) << "\n";

  return 0;
}
