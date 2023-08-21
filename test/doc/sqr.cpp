#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::sqr;
  using kyosu::complex;
  using kyosu::quaternion;

  std::cout << "Real:        "<< "\n";
  std::cout << 72.9f << " -> " << sqr(72.9f) << "\n";
  std::cout << 72.9f << " -> " << (72.9f)*(72.9f) << "\n";

  std::cout << "Complex:     "<< "\n";
  std::cout << complex<float>(3.5f,-2.9f) << " -> " << sqr(complex<float>(3.5f,-2.9f)) << "\n";
  std::cout << complex<float>(3.5f,-2.9f) << " -> " << (complex<float>(3.5f,-2.9f))*(complex<float>(3.5f,-2.9f)) << "\n";


  std::cout << "Quaternion:  "<< "\n";
  std::cout << quaternion<double>(1.1,2.2,-3.3,4.4) << " -> " << sqr(quaternion<double>(1.1,2.2,-3.3,4.4)) << "\n";
  std::cout << quaternion<double>(1.1,2.2,-3.3,4.4) << " -> " <<    (quaternion<double>(1.1,2.2,-3.3,4.4))*(quaternion<double>(1.1,2.2,-3.3,4.4))<< "\n";

   std::cout << "SIMD:        ";
   using wc_t = eve::wide<complex<double>, eve::fixed<2>>;
   std::cout << wc_t(complex<double>(1.3,-3.7)) << " -> " << sqr(wc_t(complex<double>(1.3,-3.7))) << "\n";
   std::cout << wc_t(complex<double>(1.3,-3.7)) << " -> " <<    (wc_t(complex<double>(1.3,-3.7)))*(wc_t(complex<double>(1.3,-3.7)))<< "\n";

  return 0;
}
