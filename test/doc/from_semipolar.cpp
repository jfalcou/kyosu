#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::from_semipolar;

  auto rho = 2.0;
  auto alpha = eve::pio_3(eve::as(rho));
  auto theta1 = eve::pio_4(eve::as(rho));
  auto theta2 = eve::pio_2(eve::as(rho));
  std::cout << " <- rho " << rho << std::endl;
  std::cout << " <- alpha " << alpha << std::endl;
  std::cout << " <- theta1 " << theta1 << std::endl;
  std::cout << " <- theta2 " << theta2 << std::endl;
  std::cout << " -> " << from_semipolar(rho, alpha, theta1, theta2) << "\n";

  return 0;
}
