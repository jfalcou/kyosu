// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

using wide_t = eve::wide<double, eve::fixed<4>>;
using r_t = double;
wide_t ref1 = {3.0, 2.0, 1.0, 0.5};
wide_t imf1 = {2.0, -1.0, -5.0, 0.0};
wide_t ref2 = {0.0, 1.0, 2.0, 3.0};
wide_t imf2 = {1.0f, -4.0, -2.0, 0.0};
auto pf = kyosu::complex_t<wide_t>(ref1, imf1);
auto qf = kyosu::complex_t<wide_t>(ref2, imf2);

int main()
{
  std::cout << "<- pf = " << pf << "\n";
  std::cout << "<- qf = " << qf << "\n";

  std::cout << "-> ellint_rc(pf, qf)                = " << kyosu::ellint_rc(pf, qf) << "\n";
}
