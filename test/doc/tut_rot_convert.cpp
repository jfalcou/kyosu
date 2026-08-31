#include <array>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto pi = eve::pi(eve::as<double>());
  std::array<double, 3> axis{0., 0., 1.};
  auto q = kyosu::from_angle_axis(pi/3, std::span(axis));

  std::cout << "q                  = " << q << "\n";

  // Back to an angle and an axis.
  auto [angle, ax] = kyosu::to_angle_axis(q);
  std::cout << "to_angle_axis      = " << angle << " rad about ("
            << ax[0] << ", " << ax[1] << ", " << ax[2] << ")\n";

  // To Euler angles, naming the three axes, and back again.
  auto [a, b, c] = kyosu::to_euler(q, kyosu::Z_, kyosu::X_, kyosu::Z_);
  std::cout << "to_euler           = " << a << ", " << b << ", " << c << "\n";
  std::cout << "round trip         = " << kyosu::from_euler(a, b, c, kyosu::Z_, kyosu::X_, kyosu::Z_) << "\n";

  // To a rotation matrix, and back.
  auto m = kyosu::to_rotation_matrix(q);
  std::cout << "to_rotation_matrix =\n";
  for (int i = 0; i < 3; ++i)
    std::cout << "    " << m[i][0] << ", " << m[i][1] << ", " << m[i][2] << "\n";
  std::cout << "from_rotation_matrix = " << kyosu::from_rotation_matrix(m) << "\n";
}
