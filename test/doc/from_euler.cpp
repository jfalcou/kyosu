#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::from_euler;
  using kyosu::X_;
  using kyosu::Z_;
  using kyosu::extrinsic;

  auto psi  = eve::pio_3(eve::as(0.0));
  auto theta= eve::pio_4(eve::as(0.0));
  auto phi  = eve::pio_6(eve::as(0.0));

  std::cout << " <- psi   " << psi << std::endl;
  std::cout << " <- theta " << theta << std::endl;
  std::cout << " <- phi   " << phi<< std::endl;
  std::cout << " -> from_euler(psi, theta, phi, X_, Z_, X_, extrinsic) "
            << kyosu::from_euler(psi, theta, phi, X_, Z_, X_, extrinsic) << "\n";

  return 0;
}
