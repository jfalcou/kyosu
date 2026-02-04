// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

using wide_t = eve::wide<double, eve::fixed<4>>;
using r_t = double;
wide_t re1 = {3.0, 2.0, 1.0, 0.5};
wide_t im1 = {2.0, -1.0, -5.0, 0.0};
wide_t re2 = {0.0, 1.0, 2.0, 3.0};
wide_t im2 = {1.0, -4.0, -2.0, 0.0};
wide_t re3 = {0.1, -1.0, 2.0, 4.0};
wide_t im3 = {2.0, -4.0, -3.0, 0.0};
auto p = kyosu::complex_t<wide_t>(re1, im1);
auto q = kyosu::complex_t<wide_t>(re2, im2);
auto r = kyosu::complex_t<wide_t>(re3, im3);

int main()
{
  std::cout << "<- p = " << p << "\n";
  std::cout << "<- q = " << q << "\n";
  std::cout << "<- r = " << r << "\n";

  std::cout << "-> ellint_rd(p, q, r)                = " << kyosu::ellint_rd(p, q, r) << "\n";
  std::cout << "-> ellint_rd[ignore_last(2)](p, q, r)= " << kyosu::ellint_rd[eve::ignore_last(2)](p, q, r) << "\n";
  std::cout << "-> ellint_rd[q != 4.0](p, q, r)    = " << kyosu::ellint_rd[q != 4.0](p, q, r) << "\n";
}
