// revision 1
#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  eve::wide xd{0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  eve::wide n{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};

  double x(0.5);

  std::cout << "<- xd                                      = " << xd << '\n';
  std::cout << "<- n                                       = " << n  << '\n';
  std::cout << "<- x                                       = " << x  << '\n';

  std::cout << "-> tchebytchev(n, xd)                      = " << kyosu::tchebytchev(n, xd) << '\n';
  std::cout << "-> tchebytchev(3.0, xd)                    = " << kyosu::tchebytchev(3.0, xd) << '\n';
  std::cout << "-> tchebytchev(n, 2.0)                     = " << kyosu::tchebytchev(n, 2.0) << '\n';
  std::cout << "-> tchebytchev(n, x)                       = " << kyosu::tchebytchev(n, x)   << '\n';
  std::cout << "-> tchebytchev[kind_2](n, xd)              = " << kyosu::tchebytchev[eve::kind_2](n, xd) << "\n\n";
  std::cout << "-> tchebytchev[eve::ignore_last(2)](n, xd) = " << kyosu::tchebytchev[eve::ignore_last(2)](n, xd) << '\n';
//   std::cout << "-> tchebytchev[n > 3](n, xd)               = " << kyosu::tchebytchev[n >  3](n, xd) << '\n';
}
