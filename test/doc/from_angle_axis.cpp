#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <array>
#include <iostream>

int main()
{
  using kyosu::from_angle_axis;
  using kyosu::complex_t;
  using kyosu::quaternion_t;


  auto theta = eve::pio_3(eve::as<double>());
  std::array<double, 3> ax{1., 2., 3.};

  std::cout << " <- theta = " << theta << std::endl;
  std::cout << " <- axis  = (" << ax[0] << ", " <<  ax[1] << ", " <<  ax[2] << ")" << std::endl;
  std::cout << " -> " << kyosu::from_angle_axis(theta,  ax) << "\n";

  return 0;
}
