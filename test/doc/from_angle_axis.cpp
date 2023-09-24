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
  auto q = kyosu::from_angle_axis(theta,  ax);
  std::cout << " -> " << kyosu::from_angle_axis(theta,  ax) << "\n";
  auto [aa, axx] = kyosu::to_angle_axis(q);
  std::cout << " ->theta = " << aa << std::endl;
  std::cout << " -> axis  = (" << axx[0] << ", " <<  axx[1] << ", " <<  axx[2] << ")" << std::endl;

  return 0;
}
