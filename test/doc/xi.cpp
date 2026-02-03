#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using wide_ft = eve::wide<float, eve::fixed<4>>;
  wide_ft ref1 = {3.0f, 2.0f, 1.0f, 0.5f};
  wide_ft imf1 = {2.0f, -1.0, -5.0, 0.0};
  auto zc = kyosu::complex_t<wide_ft>(ref1, imf1);
  std::cout << "---- simd" << std::endl
            << "<- zc              = " << zc << std::endl
            << "<- ref1            = " << ref1 << std::endl
            << "-> xi(zc)          = " << kyosu::xi(zc) << std::endl
            << "-> xi[riemann](zc) = " << kyosu::xi[kyosu::riemann](zc) << std::endl
            << "-> xi[landau ](zc) = " << kyosu::xi[kyosu::landau](zc) << std::endl
            << "-> ξ(zc)           = " << kyosu::ξ(zc) << std::endl
            << "-> Ξ(zc)           = " << kyosu::Ξ(zc) << std::endl
            << "-> xi(ref1)        = " << kyosu::xi(ref1) << std::endl;
  return 0;
}
