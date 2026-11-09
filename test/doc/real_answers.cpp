#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // -1 is outside the real domain of sqrt, so the answer is complex.
  std::cout << "sqrt(-1.0)            = " << kyosu::sqrt(-1.0) << "\n";

  // real_only calls eve::sqrt instead, which returns NaN.
  std::cout << "sqrt[real_only](-1.0) = " << kyosu::sqrt[kyosu::real_only](-1.0) << "\n";
}
