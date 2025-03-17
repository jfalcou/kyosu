#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{

 using wide_t = eve::wide <double, eve::fixed<4>>;
  wide_t ref1 = { 3.0, 2.0, 1.0, 0.5};
  wide_t imf1 = { 2.0 , -1.0,  -5.0, 0.0};
  wide_t ref2 = { 0.0, 1.0, 2.0, 3.0};
  auto zc = kyosu::complex_t<wide_t>(ref1, imf1);

  std::cout
    << "---- simd" << std::endl
    << "<- zc                          = " << zc << std::endl
    << "-> tgamma(zc)                  = " << kyosu::tgamma(zc)<< std::endl
    << "-> tgamma(ref2)                = " << kyosu::tgamma(ref2) << std::endl; 
}
