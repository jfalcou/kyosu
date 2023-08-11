#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::imag;
  using kyosu::complex;
  using kyosu::quaternion;

  std::cout << "imag:        ";
  float f = 72.9f;
  std::cout << f << " -> " << imag(f) << "\n";

  std::cout << "Complex:     ";
  auto z = complex<float>(3.5f,-2.9f);
  std::cout << z << " -> " << imag(z) <<  " => ";
  imag(z) = 11.23f;
  std::cout << z << "\n";

  std::cout << "Quaternion:  ";
  auto q = quaternion<double>(1.,2.,3.,4.);
  std::cout << q << " -> " << imag(q)  <<  " => ";
  imag(q) = 42.7;
  std::cout << q << "\n";

  std::cout << "SIMD:        ";
  eve::wide<complex<double>, eve::fixed<2>> wz(complex<double>(1.3,-3.7));
  std::cout << wz << " -> " << imag(wz) <<   " => ";
  imag(wz) = eve::wide<double, eve::fixed<2>>{13.37,63.24};
  std::cout << wz << "\n";

  return 0;
}
