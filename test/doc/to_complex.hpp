#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::abs;
  using kyosu::as_complex_t;
  using kyosu::as_quaternion_t;

  std::cout << "Real:        ";
  std::cout << 72.9f << " -> " << complex(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << (3.5f,-2.9f) << " -> " << complex(3.5f,-2.9f) << "\n";

  std::cout << "Quaternion:  ";
  std::cout << (1.,2.,3.,4.) << " -> " << quaternion(1.,2.,3.,4.) << "\n";

  std::cout << "SIMD:        ";
  using w_t = eve::wide<double, eve::fixed<2>>;
  w_t a(3.5f,-2.9f), b(1.0, -3.0);
  std::cout << complex(a, b) << " -> " << complex(a, b) << "\n";

  return 0;
}
