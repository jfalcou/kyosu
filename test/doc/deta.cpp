#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::deta;
using wide_ft = eve::wide <float, eve::fixed<4>>;

  wide_ft ref1 = { 3.0f, 2.0f, 1.0f, 0.6f};
  wide_ft imf1 = { 2.0f , -1.0,  -5.0, 0.0};
  auto zc = kyosu::complex_t<wide_ft>(ref1, imf1);
  auto z = kyosu::complex_t<double>(1.0, 0.0);
  auto zf= kyosu::complex_t<float >(1.0, 0.0);
  std::cout
    << "---- simd" << std::endl
    << "<- z           = " << z << std::endl
    << "-> deta(1, z)  = " << deta(1u, z) << std::endl
    << "-> deta(2, z)  = " << deta(2u, z) << std::endl
    << "-> deta(3, z)  = " << deta(3u, z) << std::endl
    << "-> deta(2, 0.2)= " << deta(2u, 0.2)<< std::endl
    << "-> deta(1, 0.2)= " << deta(1u, 0.2)<< std::endl
    << "-> deta(1, z)  = " << deta(1u, zf) << std::endl
    << "-> deta(2, z)  = " << deta(2u, zf) << std::endl
    << "-> deta(3, z)  = " << deta(3u, zf) << std::endl
    << "-> deta(2, 0.2)= " << deta(2u, 0.2f)<< std::endl
    << "-> deta(1, 0.2)= " << deta(1u, 0.2f)<< std::endl
    << "<- zc          = " << zc << std::endl
    << "-> deta(1, zc) = " << deta(1u, zc)<< std::endl;
  return 0;
}
