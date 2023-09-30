#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::lkpart;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  std::cout << "Real:        ";
  float f = 72.9f;
  std::cout << f << " -> " << lkpart(f) << "\n";

  std::cout << "Complex:     ";
  auto z = kyosu::complex_t<float>(3.5f,-2.9f);
  std::cout << z << " -> " << lkpart(z) << "\n";

  std::cout << "Quaternion:  ";
  auto q = kyosu::quaternion_t<double>(1.,2.,3.,4.);
  std::cout << q << " -> " << lkpart(q)  <<  " => ";

  std::cout << "octonion:  ";
  auto o = kyosu::octonion_t<double>(1.,2.,3.,4.,11.,12.,13.,14.);
  std::cout << o << " -> " << lkpart(o)  <<  " => ";


  return 0;
}
