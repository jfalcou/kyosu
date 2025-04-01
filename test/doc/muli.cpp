#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{

 using wide_ft = eve::wide <float, eve::fixed<4>>;
  wide_ft r = { 3.0f, 2.0f, 1.0f, 0.5f};
  wide_ft i = { 2.0f , -1.0,  -5.0, 0.0};
  auto zc = kyosu::complex_t<wide_ft>(r, i);
  auto zq = kyosu::quaternion(1.0f, 2.0f, 3.0f, 4.0f);

  std::cout
    << "---- simd" << std::endl
    << "<- r                         = " << r << std::endl
    << "-> muli(r)                   = " << kyosu::muli(r)<< std::endl
    << "<- zc                        = " << zc << std::endl
    << "-> muli(zc)                  = " << kyosu::muli(zc)<< std::endl
    << "<- zq                        = " << zq << std::endl
    << "-> muli(zq)                  = " << kyosu::muli(zq) << std::endl
    << "-> muli[eve::left](zq)       = " << kyosu::muli[eve::left](zq) << std::endl
    << "-> muli[eve::right](zq)      = " << kyosu::muli[eve::right](zq) << std::endl;

  return 0;
}
