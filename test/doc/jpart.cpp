#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::jpart;
  using kyosu::complex;
  using kyosu::quaternion;

  std::cout << "Real:        ";
  float f = 72.9f;
  std::cout << f << " -> " << jpart(f) << "\n";

  std::cout << "Complex:     ";
  auto z = complex<float>(3.5f,-2.9f);
  std::cout << z << " -> " << jpart(z) << "\n";

  std::cout << "Quaternion:  ";
  auto q = quaternion<double>(1.,2.,3.,4.);
  std::cout << q << " -> " << jpart(q)  <<  " => ";
  jpart(q) = 42.7;
  std::cout << q << "\n";

  std::cout << "SIMD:        ";
  eve::wide<quaternion<double>, eve::fixed<2>> wz(quaternion<double>(1.3,-3.7,4.2,-7.8));
  std::cout << wz << " -> " << jpart(wz) <<   " => ";
  jpart(wz) = eve::wide<double, eve::fixed<2>>{13.37,63.24};
  std::cout << wz << "\n";

  return 0;
}
