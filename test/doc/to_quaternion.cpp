#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex;
  using kyosu::quaternion;

  std::cout << "Real:        ";
  std::cout << "quaternion(72.9f) -> " << quaternion(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << "quaternion(3.5f, 2.9f) -> " << quaternion(3.5f, -2.9f) << "\n";

  std::cout << "Quaternion:  ";
  std::cout << "quaternion(1.0,  2.0, 3.0, 4.0) -> " << quaternion(1., 2., 3., 4.) << "\n";
  auto c0 = complex(1.0, 2.3);
  auto c1 = complex(-4.0, -1.5);
  std::cout << "c0 = " << c0 << "\n";
  std::cout << "c1 = " << c1 << "\n";
  std::cout << "quaternion(c0, c1) -> " << quaternion(c0, c1) << "\n";

  std::cout << "SIMD quaternion:        \n";
  using w_t = eve::wide<double, eve::fixed<2>>;
  w_t a(3.5f, -2.9f), b(1.0, -3.0);
  std::cout << "a = " << a << "\n";
  std::cout << "b = " << b << "\n";
  std::cout << "quaternion(a, b) -> " << quaternion(a, b) << "\n";

  return 0;
}
