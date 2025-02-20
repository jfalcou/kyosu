#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  double pio_2 =  eve::pio_2(eve::as<double>());
  std::cout << "am(2.0, 0.5)            "<< kyosu::am(2.0, 0.5)                 << std::endl;
  std::cout << "am(2.0, 0.9)            "<< kyosu::am(2.0, 0.9)                 << std::endl;
  std::cout << "am[modular](2.0, pio_2)   "<< kyosu::am[eve::modular](2.0, pio_2) << std::endl;
  std::cout << "am[modular](2.0, 0.5)   "<< kyosu::am[eve::modular](2.0, 0.5) << std::endl;
  std::cout << "am[eccentric](2.0, 0.5) "<< kyosu::am[eve::eccentric](2.0, 0.5) << std::endl;
  std::cout << "am[eccentric](2.0, 0.9) "<< kyosu::am[eve::eccentric](2.0, 0.9) << std::endl;
  return 0;
}
