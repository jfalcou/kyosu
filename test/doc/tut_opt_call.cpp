#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // The option in square brackets, then the arguments.
  std::cout << "sqrt[real_only](-1.0) = " << kyosu::sqrt[kyosu::real_only](-1.0) << "\n";
}
