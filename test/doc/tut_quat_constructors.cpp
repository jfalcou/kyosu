#include <array>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto pi = eve::pi(eve::as<double>());

  // A rotation of pi/3 around the axis (1,2,3).
  std::array<double, 3> axis{1., 2., 3.};
  std::cout << "from_angle_axis  = " << kyosu::from_angle_axis(pi/3, std::span(axis)) << "\n";

  // The same idea through Euler angles, naming the three axes used.
  std::cout << "from_euler       = "
            << kyosu::from_euler(pi/2, pi/3, pi/4, kyosu::Z_, kyosu::X_, kyosu::Z_) << "\n";

  // Modulus and argument, as for a complex number.
  std::cout << "from_polar       = " << kyosu::from_polar(2., pi/6) << "\n";

  // Four-dimensional spherical and cylindrical parametrisations.
  std::cout << "from_spherical   = " << kyosu::from_spherical(1., pi/4, pi/3, pi/6) << "\n";
  std::cout << "from_cylindrical = " << kyosu::from_cylindrical(1., pi/4, 2., 3.)   << "\n";
}
