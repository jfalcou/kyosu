#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // The jl component of an octonion, printed with the label jl.
  auto o = kyosu::octonion_t<double>(1., 2., 3., 4., 11., 12., 13., 14.);
  std::cout << o << " -> " << kyosu::jlpart(o) << "\n";

  // Below the octonions, the jl part is zero.
  auto q = kyosu::quaternion_t<double>(1., 2., 3., 4.);
  std::cout << q << " -> " << kyosu::jlpart(q) << "\n";
  std::cout << 72.9f << " -> " << kyosu::jlpart(72.9f) << "\n";
}
