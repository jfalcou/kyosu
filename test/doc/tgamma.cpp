#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{

 using wide_ft = eve::wide <float, eve::fixed<4>>;
  wide_ft ref1 = { 3.0f, 2.0f, 1.0f, 0.5f};
  wide_ft imf1 = { 2.0f , -1.0,  -5.0, 0.0};
  wide_ft ref2 = { 0.0, 1.0, 2.0, 3.0};
  auto zc = kyosu::complex_t<wide_ft>(ref1, imf1);

  std::cout
    << "---- simd" << std::endl
    << "<- zc                          = " << zc << std::endl
    << "-> tgamma(zc)                  = " << kyosu::tgamma(zc)<< std::endl
    << "-> tgamma(ref2)                = " << kyosu::tgamma(ref2) << std::endl
    << "-> tgamma(zc, 2.0)             = " << kyosu::tgamma(zc, 2.0)<< std::endl
    << "-> tgamma(ref2, 2.0)           = " << kyosu::tgamma(ref2, 2.0) << std::endl
    << "-> tgamma[upper](zc, 2.0)      = " << kyosu::tgamma[eve::upper](zc, 2.0)<< std::endl
    << "-> tgamma[upper](ref2, 2.0)    = " << kyosu::tgamma[eve::upper](ref2, 2.0) << std::endl;

  std::cout <<  kyosu::tgamma(ref2)-kyosu::tgamma(ref2, 2.0)- kyosu::tgamma[eve::upper](ref2, 2.0) << std::endl;
  std::cout <<  kyosu::tgamma(zc)-kyosu::tgamma(zc, 2.0)- kyosu::tgamma[eve::upper](zc, 2.0) << std::endl;
  return 0;
}
