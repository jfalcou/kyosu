#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  std::cout << "acosh(0.5)             = " << kyosu::acosh(0.5)                      << "\n";
  std::cout << "acosh[real_only](0.5)  = " << kyosu::acosh[kyosu::real_only](0.5)    << "\n";
  std::cout << "asin(2.0)              = " << kyosu::asin(2.0)                       << "\n";
  std::cout << "asin[real_only](2.0)   = " << kyosu::asin[kyosu::real_only](2.0)     << "\n";
}
