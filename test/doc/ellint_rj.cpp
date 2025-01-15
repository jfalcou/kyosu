// revision 1
#include <eve/module/elliptic.hpp>
#include <iostream>

using wide_t = eve::wide <double, eve::fixed<4>>;
using r_t = double;
wide_t re1 = { 3.0, 2.0, 1.0, 0.5};
wide_t im1 = { 2.0, -1.0,  -5.0, 0.0};
wide_t re2 = { 0.0, 1.0, 2.0, 3.0};
wide_t im2 = { 1.0 , -4.0,  -2.0, 0.0};
wide_t re3 = { 0.1, -1.0, 2.0, 4.0};
wide_t im3 = { 2.0 , -4.0,  -3.0, 0.0};
wide_t re4 = { 0.1, -1.5, 2.3, 0.5};
wide_t im4 = { 0.0 , -1.0,  -2.0, 0.0};
auto p = kyosu::complex_t<wide_t>(re1, im1);
auto q = kyosu::complex_t<wide_t>(re2, im2);
auto r = kyosu::complex_t<wide_t>(re3, im3);
auto s = kyosu::complex_t<wide_t>(re4, im4);

int main()
{
  std::cout << "<- p = " << p << "\n";
  std::cout << "<- q = " << q << "\n";
  std::cout << "<- r = " << r << "\n";
  std::cout << "<- s = " << s << "\n";


  std::cout << "-> ellint_rj(p, q, r, s)                = " << kyosu::ellint_rj(p, q, r, s) << "\n";
  std::cout << "-> ellint_rj[ignore_last(2)](p, q, r, s)= " << kyosu::ellint_rj[eve::ignore_last(2)](p, q, r, s) << "\n";
  std::cout << "-> ellint_rj[q != 4.0](p, q, r, s)    = " << kyosu::ellint_rj[q != 4.0](p, q, r, s) << "\n";
}
