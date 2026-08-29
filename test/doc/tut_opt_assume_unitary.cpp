#include <array>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto pi = eve::pi(eve::as<double>());
  std::array<double, 3> axis{0., 0., 1.};
  std::array<double, 3> v{1., 0., 0.};

  auto q = kyosu::from_angle_axis(pi/2, std::span(axis));   // already unitary
  std::cout << "abs(q) = " << kyosu::abs(q) << "\n";

  auto a = kyosu::rotate_vec(q, std::span<double,3>(v));
  auto b = kyosu::rotate_vec[kyosu::assume_unitary](q, std::span<double,3>(v));

  std::cout << "rotate_vec                  = (" << a[0] << ", " << a[1] << ", " << a[2] << ")\n";
  std::cout << "rotate_vec[assume_unitary]  = (" << b[0] << ", " << b[1] << ", " << b[2] << ")\n";
}
