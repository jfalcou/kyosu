#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto c = kyosu::complex_t<double>(1., 2.);
  auto q = kyosu::quaternion_t<double>(1., 2., 3., 4.);

  // A complex number is a quaternion whose last two components are zero.
  std::cout << "c + q = " << c + q << "\n";
  std::cout << "c * q = " << c * q << "\n";

  // A real works just as well.
  std::cout << "2. * q = " << 2. * q << "\n";
}
