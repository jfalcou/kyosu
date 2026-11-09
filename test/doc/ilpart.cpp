#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // The il component of an octonion, printed with the label il.
  auto o = kyosu::octonion_t<double>(1., 2., 3., 4., 11., 12., 13., 14.);
  std::cout << o << " -> " << kyosu::ilpart(o) << "\n";

  // Below the octonions, the il part is zero.
  auto q = kyosu::quaternion_t<double>(1., 2., 3., 4.);
  std::cout << q << " -> " << kyosu::ilpart(q) << "\n";
  std::cout << 72.9f << " -> " << kyosu::ilpart(72.9f) << "\n";
}
