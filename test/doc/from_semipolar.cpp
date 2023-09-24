#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::from_semipolar;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  auto r1 = 2.0;
  auto t1 = eve::pio_3(eve::as(r1));
  auto h1 = 3.0;
  auto h2 = eve::pio_2(eve::as(r1));
  std::cout << " <- r1 " << r1 << std::endl;
  std::cout << " <- t1 " << t1<< std::endl;
  std::cout << " <- h1 " << h1<< std::endl;
  std::cout << " <- h2 " << h2<< std::endl;
  std::cout << " -> " << from_semipolar(r1, t1, h1, h2) << "\n";

  return 0;
}
