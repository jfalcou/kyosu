#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using q_t = kyosu::quaternion_t<double>;
  auto a = q_t(1., 2., 3., 4.);
  auto b = q_t(0., 1., 0., 1.);

  auto right = a / b;              // solves x * b == a
  auto left  = kyosu::ldiv(b, a);  // solves b * x == a

  std::cout << "a / b       = " << right << "\n";
  std::cout << "ldiv(b, a)  = " << left  << "\n";

  // Each really does solve its own equation.
  std::cout << "right * b   = " << right * b << "\n";
  std::cout << "b * left    = " << b * left  << "\n";
}
