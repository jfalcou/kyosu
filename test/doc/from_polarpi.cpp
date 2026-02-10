#include <array>
#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::from_polarpi;
  using kyosu::quaternion_t;

  auto theta = eve::third(eve::as<double>());
  auto rho = 3.0;
  auto iz0 = kyosu::sign(kyosu::quaternion(0., 1.));
  auto iz1 = kyosu::sign(kyosu::quaternion(0., 1., 2., 3.));

  std::cout << " <- theta = " << theta << std::endl;
  std::cout << " <- rho   = " << rho << std::endl;
  std::cout << " -> " << from_polarpi(rho, theta) << "\n";
  std::cout << " -> " << from_polarpi(rho, theta, iz0) << "\n";
  std::cout << " -> " << from_polarpi(rho, theta, iz1) << "\n";

  return 0;
}
