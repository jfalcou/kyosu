#include <array>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto pi = eve::pi(eve::as<double>());

  std::array<double, 3> axis{0., 0., 1.};   // the z axis
  std::array<double, 3> v   {1., 0., 0.};   // the x axis

  auto q  = kyosu::from_angle_axis(pi/2, std::span(axis));
  auto rv = kyosu::rotate_vec(q, std::span<double, 3>(v));

  std::cout << "q             = " << q << "\n";
  std::cout << "v             = (" << v[0]  << ", " << v[1]  << ", " << v[2]  << ")\n";
  std::cout << "rotate_vec    = (" << rv[0] << ", " << rv[1] << ", " << rv[2] << ")\n";
}
