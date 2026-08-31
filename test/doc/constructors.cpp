#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // A rotation given as three Euler angles, in the order they are applied.
  using kyosu::X_;
  using kyosu::Y_;
  using kyosu::Z_;
  auto q = kyosu::from_euler(eve::pio_3(eve::as(0.0)), eve::pio_4(eve::as(0.0)),
                             eve::pio_6(eve::as(0.0)), Z_, Y_, X_);

  std::cout << "from_euler   = " << q << "\n";

  // Or as a modulus and an argument.
  std::cout << "from_polar   = " << kyosu::from_polar(2., eve::pio_4(eve::as(0.0))) << "\n";
}
