#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::from_euler;
  using kyosu::X_;
  using kyosu::Y_;
  using kyosu::Z_;

  auto psi = eve::pio_3(eve::as(0.0));
  auto theta = eve::pio_4(eve::as(0.0));
  auto phi = eve::pio_6(eve::as(0.0));

  std::cout << " <- psi   " << psi << std::endl;
  std::cout << " <- theta " << theta << std::endl;
  std::cout << " <- phi   " << phi << std::endl;
  std::cout << " -> from_euler(psi, theta, phi, X_, Z_, Y_) " << kyosu::from_euler(psi, theta, phi, X_, Z_, Y_) << "\n";
  std::cout << " -> from_euler[intrinsic](psi, theta, phi, Y_, Z_, Y_) "
            << kyosu::from_euler[kyosu::intrinsic](psi, theta, phi, Y_, Z_, Y_) << "\n";

  return 0;
}
