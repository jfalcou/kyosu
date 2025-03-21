#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  double pio_2 =  eve::pio_2(eve::as<double>());
  auto i = kyosu::i(eve::as<double>());
  std::cout << "am(2.0, 0.5)            "<< kyosu::am(2.0, 0.5)                 << std::endl;
  std::cout << "am(2.0, 0.9)            "<< kyosu::am(2.0, 0.9)                 << std::endl;
  std::cout << "am[modular](2.0, pio_2)   "<< kyosu::am[eve::modular](2.0, pio_2) << std::endl;
  std::cout << "am[modular](2.0, 0.5)   "<< kyosu::am[eve::modular](2.0, 0.5) << std::endl;
  std::cout << "am[eccentric](2.0, 0.5) "<< kyosu::am[eve::eccentric](2.0, 0.5) << std::endl;
  std::cout << "am[eccentric](2.0, 0.9) "<< kyosu::am[eve::eccentric](2.0, 0.9) << std::endl;
  eve::wide phi{2.0+0*i, 2.0+0*i, 1.+2*i, i};
  eve::wide m  {0.5, 0.9, 0.1, 0.2};
  std::cout << "phi                     " << phi << std::endl;
  std::cout << "m                       " << m   << std::endl;
  std::cout << "am[eccentric](phi, m)   " << kyosu::am[eve::eccentric](phi, m) << std::endl;

  return 0;
}
