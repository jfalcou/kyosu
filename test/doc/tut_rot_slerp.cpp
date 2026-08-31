#include <array>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto pi = eve::pi(eve::as<double>());
  std::array<double, 3> z{0., 0., 1.};

  auto q0 = kyosu::from_angle_axis(0.,   std::span(z));   // no rotation
  auto q1 = kyosu::from_angle_axis(pi/2, std::span(z));   // a quarter turn

  std::array<double, 3> v{1., 0., 0.};

  for (double t = 0.; t <= 1.0001; t += 0.25)
  {
    auto rv = kyosu::rotate_vec(kyosu::slerp(q0, q1, t), std::span<double, 3>(v));
    std::cout << "t = " << t << "  ->  (" << rv[0] << ", " << rv[1] << ", " << rv[2] << ")\n";
  }
}
