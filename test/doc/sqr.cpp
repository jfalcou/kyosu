#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using kyosu::sqr;

  std::cout << "Real:        " << "\n";
  std::cout << 72.9f << " -> " << sqr(72.9f) << "\n";
  std::cout << 72.9f << " -> " << (72.9f) * (72.9f) << "\n";

  std::cout << "Complex:     " << "\n";
  std::cout << kyosu::complex_t<float>(3.5f, -2.9f) << " -> " << sqr(kyosu::complex_t<float>(3.5f, -2.9f)) << "\n";
  std::cout << kyosu::complex_t<float>(3.5f, -2.9f) << " -> "
            << (kyosu::complex_t<float>(3.5f, -2.9f)) * (kyosu::complex_t<float>(3.5f, -2.9f)) << "\n";

  std::cout << "Quaternion:  " << "\n";
  std::cout << kyosu::quaternion_t<double>(1.1, 2.2, -3.3, 4.4) << " -> "
            << sqr(kyosu::quaternion_t<double>(1.1, 2.2, -3.3, 4.4)) << "\n";
  std::cout << kyosu::quaternion_t<double>(1.1, 2.2, -3.3, 4.4) << " -> "
            << (kyosu::quaternion_t<double>(1.1, 2.2, -3.3, 4.4)) * (kyosu::quaternion_t<double>(1.1, 2.2, -3.3, 4.4))
            << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
  std::cout << wc_t(kyosu::complex_t<double>(1.3, -3.7)) << " -> " << sqr(wc_t(kyosu::complex_t<double>(1.3, -3.7)))
            << "\n";
  std::cout << wc_t(kyosu::complex_t<double>(1.3, -3.7)) << " -> "
            << (wc_t(kyosu::complex_t<double>(1.3, -3.7))) * (wc_t(kyosu::complex_t<double>(1.3, -3.7))) << "\n";

  return 0;
}
