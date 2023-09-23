#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::rotate_vec;

  auto theta = eve::pio_3(eve::as<double>());
  std::array<double, 3> ax{1., 2., 3.};
  std::array<double, 3> v{ 1.5, 2.0, -3.0}
  auto q = from_angle_axis(theta, ax);
  std::cout << " v                " << v[0] << ", " < v[1] << ",  " << < v[2] << ")\n";
  �td::cout << " q                " << q << std::endl;
  std::cout << " rotate_vec(q, v) " << " -> (" << rv[0] << ", " < rv[1] << ",  " << < rv[2] << ")\n";

  return 0;
}
