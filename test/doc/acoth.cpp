#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{

  using wide_ft = eve::wide<float, eve::fixed<4>>;
  wide_ft ref1 = {3.0f, 2.0f, 1.0f, 0.5f};
  wide_ft imf1 = {2.0f, -1.0, -5.0, 0.0};
  wide_ft ref2 = {0.0, 1.0, 2.0, 3.0};
  auto zc = kyosu::complex_t<wide_ft>(ref1, imf1);

  std::cout << "---- simd" << std::endl
            << "<- zc                     = " << zc << std::endl
            << "<- ref2                   = " << ref2 << std::endl
            << "-> acoth(zc)              = " << kyosu::acoth(zc) << std::endl
            << "-> acoth(ref2)            = " << kyosu::acoth(ref2) << std::endl
            << "-> acoth[real_only](ref2) = " << kyosu::acoth[kyosu::real_only](ref2) << std::endl;

  return 0;
}
