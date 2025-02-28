// revision 1
#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  eve::wide xd{0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  eve::wide n{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
//  kyosu::wide n1{0, -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0};
  double x(0.5);

  std::cout << "<- xd                                   = " << xd << '\n';
  std::cout << "<- n                                    = " << n  << '\n';
  std::cout << "<- x                                    = " << x  << '\n';

  std::cout << "-> legendre(n, xd)                      = " << kyosu::legendre(n, xd) << '\n';
  std::cout << "-> legendre[eve::ignore_last(2)](n, xd) = " << kyosu::legendre[eve::ignore_last(2)](n, xd) << '\n';
  std::cout << "-> legendre[n > 3](n, xd)               = " << kyosu::legendre[n >  3](n, xd) << '\n';
  std::cout << "-> legendre(3.0, xd)                    = " << kyosu::legendre(3.0, xd) << '\n';
  std::cout << "-> legendre(n, 2.0)                     = " << kyosu::legendre(n, 2.0) << '\n';
  std::cout << "-> legendre(n, x)                       = " << kyosu::legendre(n, x)   << '\n';
  std::cout << "-> legendre[q_kind](n, xd)              = " << kyosu::legendre[eve::q_kind](n, xd) << "\n\n";
  std::cout << "-> legendre[q_kind](0.0, xd)            = " << kyosu::legendre[eve::q_kind](0.0, xd) << "\n\n";


 for(int i=0; i < 8 ; ++i)
 {
   std::cout << i << " -> legendre[q_kind](0.0, xd.get(i))              = " << kyosu::legendre[eve::q_kind](0.0, xd.get(i)) << "\n\n";
 }


}
