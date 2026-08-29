#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // By default a real argument outside the real domain widens to a complex answer.
  std::cout << "sqrt(-1.0)              = " << kyosu::sqrt(-1.0)  << "\n";
  std::cout << "log(-1.0)               = " << kyosu::log(-1.0)   << "\n";
  std::cout << "acos(2.0)               = " << kyosu::acos(2.0)   << "\n";

  // real_only asks for the real function instead, NaN included.
  std::cout << "sqrt[real_only](-1.0)   = " << kyosu::sqrt[kyosu::real_only](-1.0) << "\n";
  std::cout << "log[real_only](-1.0)    = " << kyosu::log[kyosu::real_only](-1.0)  << "\n";
}
