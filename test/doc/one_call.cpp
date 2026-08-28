#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::sqr;

  // One name, whatever the dimension of the argument.
  std::cout << "complex:    " << sqr(kyosu::complex_t<double>(1., 2.))            << "\n";
  std::cout << "quaternion: " << sqr(kyosu::quaternion_t<double>(1., 2., 3., 4.)) << "\n";
  std::cout << "octonion:   " << sqr(kyosu::octonion_t<double>(1., 2., 3., 4., 5., 6., 7., 8.)) << "\n";
}
