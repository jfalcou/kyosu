#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto I = kyosu::complex(0.0, 1.0);
  std::cout << "kummer(2.0, 1., 1.5)                 " << kyosu::kummer(2.0, 1., 1.5) << std::endl;
  std::cout << "kummer(2.0, 1., I)                   " << kyosu::kummer(2.0, 1., I) << std::endl;
  std::cout << "kummer[regularized](2.0, 1., 1.5)    " << kyosu::kummer[kyosu::regularized](2.0, 1., 1.5) << std::endl;
  std::cout << "kummer[regularized](2.0, 1., I)      " << kyosu::kummer[kyosu::regularized](2.0, 1., I) << std::endl;
  std::cout << "kummer[regularized](0.5, -2.0,-1.0)  " << kyosu::kummer[kyosu::regularized](1.0, 2.0, -3.0)
            << std::endl;
  std::cout << "kummer[regularized](0.5, -2.0,-1.0)  " << kyosu::kummer[kyosu::regularized](1.0, 2.0, -3.001)
            << std::endl;
  return 0;
}
