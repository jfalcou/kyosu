#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::inject;
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using kyosu::inject;
  using kyosu::complex;

  std::cout << "Real:\n";
  std::cout << 72.9f << " -> " << inject(72.9f) << "\n";
  std::cout << 72.9f << " -> " << complex(72.9f) << "\n";
  std::cout << "nan" << " -> " << inject(eve::nan(eve::as<float>())) << "\n";
  std::cout << "nan" << " -> " << complex(eve::nan(eve::as<float>())) << "\n";

  std::cout << "Complex:\n";
  std::cout << kyosu::complex_t<float>(3.5f, -2.9f) << " -> " << inject(kyosu::complex_t<float>(3.5f, -2.9f)) << "\n";

  std::cout << "Quaternion:\n ";
  std::cout << kyosu::quaternion_t<double>(1., 2., 3., 4.) << " -> " << inject(kyosu::quaternion_t<double>(1., 2., 3., 4.))
            << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
  std::cout << wc_t(kyosu::complex_t<double>(1.3, -3.7)) << " -> " << inject(wc_t(kyosu::complex_t<double>(1.3, -3.7)))
            << "\n";

  return 0;
}
