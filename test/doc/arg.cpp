#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{

  using wide_ft = eve::wide<float, eve::fixed<4>>;
  wide_ft ref1 = {3.0f, 2.0f, 1.0f, 0.5f};
  wide_ft imf1 = {2.0f, -1.0, -5.0, 0.0};
  wide_ft ref2 = {0.0, -1.0, 2.0, eve::nan(eve::as<double>())};
  auto zc = kyosu::complex_t<wide_ft>(ref1, imf1);

  std::cout << "---- simd" << std::endl
            << "<- zc                                 = " << zc << std::endl
            << "<- ref2                               = " << ref2 << std::endl
            << "-> arg(zc)                            = " << kyosu::arg(zc) << std::endl
            << "-> arg(ref2)                          = " << kyosu::arg(ref2) << std::endl
            << "-> arg(kyosu::cinf(eve::as<double>()) = " << kyosu::arg(kyosu::cinf(eve::as<double>())) << std::endl
            << "-> arg(kyosu::zero(kyosu::as(zc)))    = " << kyosu::arg(kyosu::zero(kyosu::as(zc))) << std::endl;
  return 0;
}
