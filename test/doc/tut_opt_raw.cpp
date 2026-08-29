#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using c_t = kyosu::complex_t<double>;

  // On ordinary input the two agree exactly.
  auto z = c_t(3., 4.);
  std::cout << "log(z)            = " << kyosu::log(z)             << "\n";
  std::cout << "log[raw](z)       = " << kyosu::log[kyosu::raw](z) << "\n";

  // At the origin the guarded version still names an imaginary part; the raw one does not.
  auto o = c_t(0., 0.);
  std::cout << "log(0)            = " << kyosu::log(o)             << "\n";
  std::cout << "log[raw](0)       = " << kyosu::log[kyosu::raw](o) << "\n";
}
