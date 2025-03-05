// revision 1
#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  eve::wide xd{0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  eve::wide n{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
  eve::wide l{-4.3, -1.0, -0.52, 3.2, 4.3, -5.0, 6.1, 0.0};

  double x(0.5);

  std::cout << "<- xd                                      = " << xd << '\n';
  std::cout << "<- n                                       = " << n  << '\n';
  std::cout << "<- x                                       = " << x  << '\n';

  std::cout << "-> gegenbauer(n, l, xd)                      = " << kyosu::gegenbauer(n, l, xd) << '\n';
  std::cout << "-> gegenbauer[eve::ignore_last(2)](n, l, xd) = " << kyosu::gegenbauer[eve::ignore_last(2)](n, l, xd) << '\n';
  std::cout << "-> gegenbauer[n > 3](n, l, xd)               = " << kyosu::gegenbauer[n >  3](n, l, xd) << '\n';
  std::cout << "-> gegenbauer(3.0, 2.0, xd)                  = " << kyosu::gegenbauer(3.0, 2.0, xd) << '\n';
  std::cout << "-> gegenbauer(n, l, 2.0)                     = " << kyosu::gegenbauer(n, l, 2.0) << '\n';
  std::cout << "-> gegenbauer(n, l, x)                       = " << kyosu::gegenbauer(n, l, x)   << '\n';
}
