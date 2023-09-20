#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{

 using wide_ft = eve::wide <float, eve::fixed<4>>;
  wide_ft ref1 = { 3.0f, 2.0f, 1.0f, 0.5f};
  wide_ft imf1 = { 2.0f , -1.0,  -5.0, 0.0};
  wide_ft ref2 = { 0.0, 1.0, 2.0, 3.0};
  auto zc = kyosu::as_complex_t<wide_ft>(ref1, imf1);

  std::cout
    << "---- simd" << std::endl
    << "<- zc            = " << zc << std::endl
    << "-> asec(zc)      = " << kyosu::asec(zc)<< std::endl
    << "-> asec(ref2)    = " << kyosu::asec(ref2) << std::endl;

  return 0;
}
