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

  std::cout << " <- theta = " << theta << std::endl;
  std::cout << " <- rho   = " << rho << std::endl;
  std::cout << " -> " << kyosu::from_polar(theta,  rho) << "\n";

  return 0;
}
