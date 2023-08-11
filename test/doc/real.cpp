#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::real;
  using kyosu::complex;
  using kyosu::quaternion;

  std::cout << "Real:        ";
  float f = 72.9f;
  std::cout << f << " -> " << real(f) << " => ";
  real(f) = -9.f;
  std::cout << f << "\n";

  std::cout << "Complex:     ";
  auto z = complex<float>(3.5f,-2.9f);
  std::cout << z << " -> " << real(z) <<  " => ";
  real(z) = 11.23f;
  std::cout << z << "\n";

  std::cout << "Quaternion:  ";
  auto q = quaternion<double>(1.,2.,3.,4.);
  std::cout << q << " -> " << real(q)  <<  " => ";
  real(q) = 42.7;
  std::cout << q << "\n";

  std::cout << "SIMD:        ";
  eve::wide<complex<double>, eve::fixed<2>> wz(complex<double>(1.3,-3.7));
  std::cout << wz << " -> " << real(wz) <<   " => ";
  real(wz) = eve::wide<double, eve::fixed<2>>{13.37,63.24};
  std::cout << wz << "\n";

  return 0;
}
