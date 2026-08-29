#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto z = kyosu::complex_t<double>(3., 4.);

  std::cout << "z      = " << z             << "\n";
  std::cout << "|z|    = " << kyosu::abs(z) << "\n";
  std::cout << "exp(z) = " << kyosu::exp(z) << "\n";

  // A negative real has no real square root, so a complex one comes back.
  std::cout << "sqrt(-1.0) = " << kyosu::sqrt(-1.0) << "\n";

  // The very same name, on a four-dimensional value.
  std::cout << "sqrt(q)    = " << kyosu::sqrt(kyosu::quaternion_t<double>(1., 2., 3., 4.)) << "\n";
}
