#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::lpart;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  std::cout << "Real:        ";
  float f = 72.9f;
  std::cout << f << " -> " << lpart(f) << "\n";

  std::cout << "Complex:     ";
  auto z = kyosu::complex_t<float>(3.5f,-2.9f);
  std::cout << z << " -> " << lpart(z) << "\n";

  std::cout << "Quaternion:  ";
  auto q = kyosu::quaternion_t<double>(1.,2.,3.,4.);
  std::cout << q << " -> " << lpart(q)  <<  " => ";

  std::cout << "octonion:  ";
  auto q = kyosu::cayley_dickson_t<8, double>(1.,2.,3.,4.,11.,12.,13.,14.);
  std::cout << q << " -> " << lpart(q)  <<  " => ";


  return 0;
}
