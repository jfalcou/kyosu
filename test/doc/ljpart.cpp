#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::ljpart;
  using kyosu::quaternion_t;

  std::cout << "Real:        ";
  float f = 72.9f;
  std::cout << f << " -> " << ljpart(f) << "\n";

  std::cout << "Complex:     ";
  auto z = kyosu::complex_t<float>(3.5f, -2.9f);
  std::cout << z << " -> " << ljpart(z) << "\n";

  std::cout << "Quaternion:  ";
  auto q = kyosu::quaternion_t<double>(1., 2., 3., 4.);
  std::cout << q << " -> " << ljpart(q) << " => ";

  std::cout << "octonion:  ";
  auto o = kyosu::octonion_t<double>(1., 2., 3., 4., 11., 12., 13., 14.);
  std::cout << o << " -> " << ljpart(o) << " => ";

  return 0;
}
