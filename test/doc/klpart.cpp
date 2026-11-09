#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  // The kl component of an octonion, printed with the label kl.
  auto o = kyosu::octonion_t<double>(1., 2., 3., 4., 11., 12., 13., 14.);
  std::cout << o << " -> " << kyosu::klpart(o) << "\n";

  // Below the octonions, the kl part is zero.
  auto q = kyosu::quaternion_t<double>(1., 2., 3., 4.);
  std::cout << q << " -> " << kyosu::klpart(q) << "\n";
  std::cout << 72.9f << " -> " << kyosu::klpart(72.9f) << "\n";
}
