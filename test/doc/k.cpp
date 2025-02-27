#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::k;
  using kyosu::as;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  std::cout << "Real:        \n";
  std::cout << "k(kyosu::as(72.9f))" << " -> " << k(as(72.9f)) << "\n";

//   std::cout << "Complex:     \n";
//   auto c = kyosu::complex_t<float>(3.5f,-2.9f);
//   std::cout << "c       = " << c << std::endl;
//   std::cout << "k(as(c) " << " -> " << k(as(c)) << "\n";

  std::cout << "Quaternion:  \n";
  auto z = kyosu::quaternion_t<double>(1.,2.,3.,4.);
  std::cout <<  "k(as(z) " << " -> " <<  k(as(z)) << "\n";

//   std::cout << "SIMD:        ";
//   using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
//   auto wz =  wc_t(complex_t<double>(1.3,-3.7));
//   std::cout << "k(as(wz)) " << " -> " << k(as(wz)) << "\n";

  return 0;
}
