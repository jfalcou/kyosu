#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
// auto I = kyosu::complex(0.0, 1.0);
//   std::cout << "hypergeometric(2.0, kumi::tuple{}, kumi::tuple{1.5})         "<< kyosu::hypergeometric(2.0, kumi::tuple{}, kumi::tuple{1.5})        << std::endl;
//   std::cout << "hypergeometric(2.0, kumi::tuple{}, kumi::tuple{I})           "<< kyosu::hypergeometric(2.0, kumi::tuple{}, kumi::tuple{I})          << std::endl;
//   std::cout << "hypergeometric(2.0, kumi::tuple{1.5}, kumi::tuple{})         "<< kyosu::hypergeometric(2.0, kumi::tuple{1.5}, kumi::tuple{})        << std::endl;
//   std::cout << "hypergeometric(-4.0,kumi::tuple{1.0}, kumi::tuple{})         "<< kyosu::hypergeometric(-4.0,kumi::tuple{1.0}, kumi::tuple{})        << std::endl;
//   std::cout << "hypergeometric(2.0, kumi::tuple{1.5}, kumi::tuple{2.0})      "<< kyosu::hypergeometric(2.0, kumi::tuple{1.5}, kumi::tuple{2.0})     << std::endl;
//   std::cout << "hypergeometric(-4.0,kumi::tuple{1.0}, kumi::tuple{I})        "<< kyosu::hypergeometric(-4.0,kumi::tuple{1.0}, kumi::tuple{I})       << std::endl;
//   std::cout << "hypergeometric(2.0, kumi::tuple{1.4, -3.0}, kumi::tuple{})   "<< kyosu::hypergeometric(2.0, kumi::tuple{1.4, -3.0}, kumi::tuple{})  << std::endl;
//   std::cout << "hypergeometric(2.0, kumi::tuple{1.4, 1.0}, kumi::tuple{2.0}) "<< kyosu::hypergeometric(2.0, kumi::tuple{1.4, 1.0}, kumi::tuple{2.0})<< std::endl;
//   std::cout << "hypergeometric(2.0, kumi::tuple{1.4}, kumi::tuple{2.5,-1.6}) "<< kyosu::hypergeometric(2.0,kumi::tuple{1.4}, kumi::tuple{2.5,-1.6}) << std::endl;

//   std::cout << "hypergeometric[regularized](2.0, kumi::tuple{}, kumi::tuple{1.5})         "<< kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{}, kumi::tuple{1.5})        << std::endl;
//   std::cout << "hypergeometric[regularized](2.0, kumi::tuple{}, kumi::tuple{I})           "<< kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{}, kumi::tuple{I})          << std::endl;
//   std::cout << "hypergeometric[regularized](2.0, kumi::tuple{1.5}, kumi::tuple{})         "<< kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{1.5}, kumi::tuple{})        << std::endl;
//   std::cout << "hypergeometric[regularized](-4.0,kumi::tuple{1.0}, kumi::tuple{})         "<< kyosu::hypergeometric[kyosu::regularized](-4.0,kumi::tuple{1.0}, kumi::tuple{})        << std::endl;
//   std::cout << "hypergeometric[regularized](2.0, kumi::tuple{1.5}, kumi::tuple{2.0})      "<< kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{1.5}, kumi::tuple{2.0})     << std::endl;
//   std::cout << "hypergeometric[regularized](-4.0,kumi::tuple{1.0}, kumi::tuple{I})        "<< kyosu::hypergeometric[kyosu::regularized](-4.0,kumi::tuple{1.0}, kumi::tuple{I})       << std::endl;
//   std::cout << "hypergeometric[regularized](2.0, kumi::tuple{1.4, -3.0}, kumi::tuple{})   "<< kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{1.4, -3.0}, kumi::tuple{})  << std::endl;
//   std::cout << "hypergeometric[regularized](2.0, kumi::tuple{1.4, 1.0}, kumi::tuple{2.0}) "<< kyosu::hypergeometric[kyosu::regularized](2.0, kumi::tuple{1.4, 1.0}, kumi::tuple{2.0})<< std::endl;
//   std::cout << "hypergeometric[regularized](2.0, kumi::tuple{1.4}, kumi::tuple{2.5,-1.6}) "<< kyosu::hypergeometric[kyosu::regularized](2.0,kumi::tuple{1.4}, kumi::tuple{2.5,-1.6}) << std::endl;
//   std::cout << "hypergeometric[regularized](0.5, kumi::tuple{-5.0, 2.5}, kumi::tuple{-3.0}) "<< kyosu::hypergeometric[kyosu::regularized](0.5,kumi::tuple{-5.0, 2.5}, kumi::tuple{-3.0}) << std::endl;
  auto zz = -eve::pi2o_16(eve::as<double>())*kyosu::sqr(kyosu::sqr(10.0));
  std::cout << std::setprecision(15) << zz << std::endl;
  std::cout << "hypergeometric(zz, kumi::tuple{0.25}, kumi::tuple{1.25, 0.5})    "<< kyosu::hypergeometric(zz, kumi::tuple{0.25}, kumi::tuple{1.25, 0.5})<< std::endl;

  return 0;
}
