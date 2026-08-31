#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // -1 is outside the real domain of sqrt, so the answer is complex.
  std::cout << "sqrt(-1.0)            = " << kyosu::sqrt(-1.0) << "\n";

  // Unless real_only is asked for, which defers to eve::acos and its NaN.
  std::cout << "sqrt[real_only](-1.0) = " << kyosu::sqrt[kyosu::real_only](-1.0) << "\n";
}
