#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::complex;

  std::cout << "Real:        ";
  std::cout << "complex(72.9f) -> " << complex(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << "complex(3.5f, 2.9f) -> " << complex(3.5f,-2.9f) << "\n";

  std::cout << "SIMD complex:        ";
  using w_t = eve::wide<double, eve::fixed<2>>;
  w_t a(3.5f,-2.9f), b(1.0, -3.0);
  std::cout << "complex(a, b) -> " << complex(a, b) << "\n";

  return 0;
}
