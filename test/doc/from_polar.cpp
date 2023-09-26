#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <array>
#include <iostream>

int main()
{
  using kyosu::from_polar;
  using kyosu::complex_t;
  using kyosu::quaternion_t;


  auto theta = eve::pio_3(eve::as<double>());
  auto rho   = 3.0;
  auto iz0   = kyosu::sign(kyosu::quaternion(0., 1.));
  auto iz1   = kyosu::sign(kyosu::quaternion(0., 1., 2., 3.));

  std::cout << " <- theta = " << theta << std::endl;
  std::cout << " <- rho   = " << rho << std::endl;
  std::cout << " -> " << from_polar(theta, rho) << "\n";
  std::cout << " -> " << from_polar(theta, rho, iz0) << "\n";
  std::cout << " -> " << from_polar(theta, rho, iz1) << "\n";

  return 0;
}
