#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // 2 is outside the real domain of acos, so the answer is complex.
  std::cout << "acos(2.0)            = " << kyosu::acos(2.0) << "\n";

  // Unless real_only is asked for, which defers to eve::acos and its NaN.
  std::cout << "acos[real_only](2.0) = " << kyosu::acos[kyosu::real_only](2.0) << "\n";
}
