#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::from_cylindrospherical;
  using kyosu::quaternion_t;

  auto radius = 2.0;
  auto t = eve::pio_3(eve::as(radius));
  auto longitude = eve::pio_4(eve::as(radius));
  auto latitude = eve::pio_2(eve::as(radius));
  std::cout << " <- radius     " << radius << std::endl;
  std::cout << " <- t          " << t << std::endl;
  std::cout << " <- longitude  " << longitude << std::endl;
  std::cout << " <- latitude   " << latitude << std::endl;
  std::cout << " -> " << from_cylindrospherical(radius, t, longitude, latitude) << "\n";

  return 0;
}
