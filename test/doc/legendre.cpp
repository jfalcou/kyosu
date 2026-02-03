// revision 1
#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  eve::wide xd{0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  eve::wide n{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
  double x(0.5);

  std::cout << "<- xd                                         = " << xd << '\n';
  std::cout << "<- n                                          = " << n << '\n';
  std::cout << "<- x                                          = " << x << '\n';
  auto ln = kyosu::legendre(n, x);
  auto lnp1 = kyosu::legendre(n + 1, x);
  auto lnp2 = kyosu::legendre(n + 2, x);
  std::cout << "-> legendre(n, x)                             = " << ln << '\n';
  std::cout << "-> legendre(n+1, x)                           = " << lnp1 << '\n';
  std::cout << "-> legendre(n+2, x)                           = " << lnp2 << '\n';
  std::cout << "-> legendre[eve::successor](n+1, x, lnp1, ln) = " << kyosu::legendre(n + 1, x, lnp1, ln) << '\n';
  std::cout << "-> legendre[eve::ignore_last(2)](n, xd)       = " << kyosu::legendre[eve::ignore_last(2)](n, xd)
            << '\n';
  std::cout << "-> legendre[n > 3](n, xd)                     = " << kyosu::legendre[n > 3](n, xd) << '\n';
  std::cout << "-> legendre(3.0, xd)                          = " << kyosu::legendre(3.0, xd) << '\n';
  std::cout << "-> legendre(n, 2.0)                           = " << kyosu::legendre(n, 2.0) << '\n';
  std::cout << "-> legendre(n, x)                             = " << kyosu::legendre(n, x) << '\n';
}
