#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::sqr;
  using kyosu::as_complex_t;
  using kyosu::as_quaternion_t;

  std::cout << "Real:        "<< "\n";
  std::cout << 72.9f << " -> " << sqr(72.9f) << "\n";
  std::cout << 72.9f << " -> " << (72.9f)*(72.9f) << "\n";

  std::cout << "Complex:     "<< "\n";
  std::cout << kyosu::as_complex_t<float>(3.5f,-2.9f) << " -> " << sqr(kyosu::as_complex_t<float>(3.5f,-2.9f)) << "\n";
  std::cout << kyosu::as_complex_t<float>(3.5f,-2.9f) << " -> " << (kyosu::as_complex_t<float>(3.5f,-2.9f))*(kyosu::as_complex_t<float>(3.5f,-2.9f)) << "\n";


  std::cout << "Quaternion:  "<< "\n";
  std::cout << kyosu::as_quaternion_t<double>(1.1,2.2,-3.3,4.4) << " -> " << sqr(kyosu::as_quaternion_t<double>(1.1,2.2,-3.3,4.4)) << "\n";
  std::cout << kyosu::as_quaternion_t<double>(1.1,2.2,-3.3,4.4) << " -> " <<    (kyosu::as_quaternion_t<double>(1.1,2.2,-3.3,4.4))*(kyosu::as_quaternion_t<double>(1.1,2.2,-3.3,4.4))<< "\n";

   std::cout << "SIMD:        ";
   using wc_t = eve::wide<kyosu::as_complex_t<double>, eve::fixed<2>>;
   std::cout << wc_t(kyosu::as_complex_t<double>(1.3,-3.7)) << " -> " << sqr(wc_t(kyosu::as_complex_t<double>(1.3,-3.7))) << "\n";
   std::cout << wc_t(kyosu::as_complex_t<double>(1.3,-3.7)) << " -> " <<    (wc_t(kyosu::as_complex_t<double>(1.3,-3.7)))*(wc_t(kyosu::as_complex_t<double>(1.3,-3.7)))<< "\n";

  return 0;
}
