#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // eve is at hand as soon as kyosu is
  eve::wide<double> x = [](auto i, auto) { return -1.0 + i; };

  std::cout << "cardinal            = " << eve::wide<double>::size() << " values at a time\n";
  std::cout << "x                   = " << x     << "\n";
  std::cout << "x * x               = " << x * x << "\n";

  // The rule from the previous page still holds: a square root may leave the reals,
  // so the answer is complex unless real_only says otherwise.
  std::cout << "sqrt(x)             = " << kyosu::sqrt(x)                  << "\n";
  std::cout << "sqrt[real_only](x)  = " << kyosu::sqrt[kyosu::real_only](x) << "\n";
}
