#include <eve/wide.hpp>
#include <iomanip>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto I = kyosu::complex(0.0, 1.0);
  std::cout << "hypergeometric(2.0, kumi::tuple{}, kumi::tuple{1.5})         "
            << kyosu::hypergeometric(2.0, kumi::tuple{}, kumi::tuple{1.5}) << std::endl;
  std::cout << "hypergeometric(2.0, kumi::tuple{}, kumi::tuple{I})           "
            << kyosu::hypergeometric(2.0, kumi::tuple{}, kumi::tuple{I}) << std::endl;
  std::cout << "hypergeometric(2.0, kumi::tuple{1.5}, kumi::tuple{})         "
            << kyosu::hypergeometric(2.0, kumi::tuple{1.5}, kumi::tuple{}) << std::endl;
  std::cout << "hypergeometric(-4.0,kumi::tuple{1.0}, kumi::tuple{})         "
            << kyosu::hypergeometric(-4.0, kumi::tuple{1.0}, kumi::tuple{}) << std::endl;
  std::cout << "hypergeometric(2.0, kumi::tuple{1.5}, kumi::tuple{2.0})      "
            << kyosu::hypergeometric(2.0, kumi::tuple{1.5}, kumi::tuple{2.0}) << std::endl;
  std::cout << "hypergeometric(-4.0,kumi::tuple{1.0}, kumi::tuple{I})        "
            << kyosu::hypergeometric(-4.0, kumi::tuple{1.0}, kumi::tuple{I}) << std::endl;
  std::cout << "hypergeometric(2.0, kumi::tuple{1.4, -3.0}, kumi::tuple{})   "
            << kyosu::hypergeometric(2.0, kumi::tuple{1.4, -3.0}, kumi::tuple{}) << std::endl;
  std::cout << "hypergeometric(2.0, kumi::tuple{1.4, 1.0}, kumi::tuple{2.0}) "
            << kyosu::hypergeometric(2.0, kumi::tuple{1.4, 1.0}, kumi::tuple{2.0}) << std::endl;
  std::cout << "hypergeometric(2.0, kumi::tuple{1.4}, kumi::tuple{2.5,-1.6}) "
            << kyosu::hypergeometric(2.0, kumi::tuple{1.4}, kumi::tuple{2.5, -1.6}) << std::endl;

  std::cout << "hypergeometric[regularized](2.0, kumi::tuple{}, kumi::tuple{1.5})         "
            << kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{}, kumi::tuple{1.5}) << std::endl;
  std::cout << "hypergeometric[regularized](2.0, kumi::tuple{}, kumi::tuple{I})           "
            << kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{}, kumi::tuple{I}) << std::endl;
  std::cout << "hypergeometric[regularized](2.0, kumi::tuple{1.5}, kumi::tuple{})         "
            << kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{1.5}, kumi::tuple{}) << std::endl;
  std::cout << "hypergeometric[regularized](-4.0,kumi::tuple{1.0}, kumi::tuple{})         "
            << kyosu::hypergeometric[kyosu::regularized](-4.0, kumi::tuple{1.0}, kumi::tuple{}) << std::endl;
  std::cout << "hypergeometric[regularized](2.0, kumi::tuple{1.5}, kumi::tuple{2.0})      "
            << kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{1.5}, kumi::tuple{2.0}) << std::endl;
  std::cout << "hypergeometric[regularized](-4.0,kumi::tuple{1.0}, kumi::tuple{I})        "
            << kyosu::hypergeometric[kyosu::regularized](-4.0, kumi::tuple{1.0}, kumi::tuple{I}) << std::endl;
  std::cout << "hypergeometric[regularized](2.0, kumi::tuple{1.4, -3.0}, kumi::tuple{})   "
            << kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{1.4, -3.0}, kumi::tuple{}) << std::endl;
  std::cout << "hypergeometric[regularized](2.0, kumi::tuple{1.4, 1.0}, kumi::tuple{2.0}) "
            << kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{1.4, 1.0}, kumi::tuple{2.0}) << std::endl;
  std::cout << "hypergeometric[regularized](2.0, kumi::tuple{1.4}, kumi::tuple{2.5,-1.6}) "
            << kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{1.4}, kumi::tuple{2.5, -1.6}) << std::endl;
  std::cout << "hypergeometric[regularized](0.5, kumi::tuple{-5.0, 2.5}, kumi::tuple{-3.0}) "
            << kyosu::hypergeometric[kyosu::regularized](0.5, kumi::tuple{-5.0, 2.5}, kumi::tuple{-3.0}) << std::endl;

  return 0;
}
