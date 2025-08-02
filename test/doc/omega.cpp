#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using c_t = kyosu::complex_t<double>;
  auto I = c_t(0, 1);
  auto in  = -1.30685281944005469058276787854182343192449986563974474587931999050660637 -3.14159265358979323846264338327950288419716939937510582097494459230781640*I;
  std::cout << kyosu::omega(in) << std::endl;
//  std::cout << kyosu::omega(kyosu::conj(in))<< std::endl;

//  using wide_ft = eve::wide <float, eve::fixed<4>>;
//   wide_ft ref1 = { 3.0f, 2.0f, 1.0f, 0.5f};
//   wide_ft imf1 = { 2.0f , -1.0,  -5.0, 0.0};
//   wide_ft ref2 = { 0.0, 1.0, 2.0, 3.0};
//   auto zc = kyosu::complex_t<wide_ft>(ref1, imf1);

//   std::cout
//     << "---- simd" << std::endl
//     << "<- zc              = " << zc << std::endl
//     << "<- ref2            = " << ref2 <<  std::endl
//     << "-> lambda(zc)      = " << kyosu::lambda(zc)<< std::endl
//     << "-> lambda(ref2)    = " << kyosu::lambda(ref2) << std::endl
//     << "-> λ(ref2)         = " << kyosu::λ(ref2) << std::endl;

  return 0;
}
