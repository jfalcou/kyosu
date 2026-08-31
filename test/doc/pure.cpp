#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  auto c = kyosu::complex_t<double>(3., 4.);
  auto q = kyosu::quaternion_t<double>(1., 2., 3., 4.);

  // pure drops the real part and keeps every other component.
  std::cout << "c        = " << c              << "\n";
  std::cout << "pure(c)  = " << kyosu::pure(c) << "\n";
  std::cout << "q        = " << q              << "\n";
  std::cout << "pure(q)  = " << kyosu::pure(q) << "\n";

  // A real value has no pure part at all.
  std::cout << "pure(2.) = " << kyosu::pure(2.) << "\n";
}
