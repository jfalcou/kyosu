#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::from_spherical;
  using kyosu::quaternion_t;

  auto r = 2.0;
  auto theta = eve::pio_3(eve::as(r));
  auto phi1 = eve::pio_4(eve::as(r));
  auto phi2 = eve::pio_2(eve::as(r));
  std::cout << " <- r     " << r << std::endl;
  std::cout << " <- theta " << theta << std::endl;
  std::cout << " <- phi1  " << phi1 << std::endl;
  std::cout << " <- phi2  " << phi2 << std::endl;
  std::cout << " -> " << from_spherical(r, theta, phi1, phi2) << "\n";

  return 0;
}
