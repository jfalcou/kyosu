#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // lane i holds -1 + i, whatever the width
  eve::wide<double> x = [](auto i, auto) { return -1.0 + i; };

  std::cout << "width               = " << eve::wide<double>::size() << " values at a time\n";
  std::cout << "x                   = " << x     << "\n";
  std::cout << "x * x               = " << x * x << "\n";

  // A square root may leave the reals: the answer is complex unless real_only says otherwise.
  std::cout << "sqrt(x)             = " << kyosu::sqrt(x)                  << "\n";
  std::cout << "sqrt[real_only](x)  = " << kyosu::sqrt[kyosu::real_only](x) << "\n";
}
