#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::from_cylindrical;
  using kyosu::complex;
  using kyosu::quaternion;

  auto r = 2.0;
  auto a = eve::pio_3(eve::as(r));
  auto h1 = 3.0;
  auto h2 = 4.0;
  std::cout << " <- modulus " << r << std::endl;
  std::cout << " <- angle   " << a << std::endl;
  std::cout << " <- h1      " << h1<< std::endl;
  std::cout << " <- h2      " << h2<< std::endl;
  std::cout << " -> " << from_cylindrical(r, a, h1, h2) << "\n";

  return 0;
}
