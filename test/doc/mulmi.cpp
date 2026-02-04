#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{

  using wide_ft = eve::wide<float, eve::fixed<4>>;
  wide_ft r = {3.0f, 2.0f, 1.0f, 0.5f};
  wide_ft i = {2.0f, -1.0, -5.0, 0.0};
  auto zc = kyosu::complex_t<wide_ft>(r, i);
  auto zq = kyosu::quaternion(1.0f, 2.0f, 3.0f, 4.0f);

  std::cout << "---- simd" << std::endl
            << "<- r                         = " << r << std::endl
            << "-> mulmi(r)                  = " << kyosu::mulmi(r) << std::endl
            << "<- zc                        = " << zc << std::endl
            << "-> mulmi(zc)                 = " << kyosu::mulmi(zc) << std::endl
            << "<- zq                        = " << zq << std::endl
            << "-> mulmi(zq)                 = " << kyosu::mulmi(zq) << std::endl
            << "-> mulmi[eve::left](zq)      = " << kyosu::mulmi[eve::left](zq) << std::endl
            << "-> mulmi[eve::right](zq)     = " << kyosu::mulmi[eve::right](zq) << std::endl;
  ;

  return 0;
}
