#include <array>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto pi = eve::pi(eve::as<double>());
  std::array<double, 3> z{0., 0., 1.}, y{0., 1., 0.};

  auto p = kyosu::from_angle_axis(pi/2, std::span(z));   // quarter turn about z
  auto q = kyosu::from_angle_axis(pi/2, std::span(y));   // quarter turn about y

  std::array<double, 3> v{1., 0., 0.};

  // p first, then q, is the single rotation q*p.
  auto a = kyosu::rotate_vec(q * p, std::span<double, 3>(v));
  auto b = kyosu::rotate_vec(p * q, std::span<double, 3>(v));

  std::cout << "q*p applied to x = (" << a[0] << ", " << a[1] << ", " << a[2] << ")\n";
  std::cout << "p*q applied to x = (" << b[0] << ", " << b[1] << ", " << b[2] << ")\n";
}
