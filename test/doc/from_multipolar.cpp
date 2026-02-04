#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::from_multipolar;
  using kyosu::quaternion_t;

  auto r1 = 2.0;
  auto t1 = eve::pio_3(eve::as(r1));
  auto r2 = 3.0;
  auto t2 = eve::pio_2(eve::as(r1));
  std::cout << " <- r1 " << r1 << std::endl;
  std::cout << " <- t1 " << t1 << std::endl;
  std::cout << " <- r2 " << r2 << std::endl;
  std::cout << " <- t2 " << t2 << std::endl;
  std::cout << " -> " << from_multipolar(r1, t1, r2, t2) << "\n";

  return 0;
}
