#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::as;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  std::cout << "Real:        \n";
  auto cinf = kyosu::cinf(kyosu::as(72.9f));
  std::cout << "cinf  = "  << cinf << "\n";
  std::cout << "rec(cinf) = " << kyosu::rec(cinf) << std::endl;
  std::cout << "1.0f/cinf = " << 1.0/cinf << std::endl;
  std::cout << 1.0f/kyosu::complex_t<float>(0.0, 0.0) << std::endl;
  std::cout << "kyosu::abs(cinf) " << kyosu::abs(cinf) << std::endl;
  std::cout << "kyosu::arg(cinf) " << kyosu::arg(cinf) << std::endl;
  std::cout << "Complex:     \n";
  auto c = kyosu::complex_t<float>(3.5f,-2.9f);
  std::cout << "c       = " << c << std::endl;
  std::cout << "cinf(as(c)) " << " -> " << kyosu::cinf(as(c)) << "\n";
  std::cout << c/kyosu::complex_t<float>(0.0, 0.0) << std::endl;
  std::cout << c/0.0f << std::endl;

  std::cout << "Quaternion:  \n";
  auto z = kyosu::quaternion_t<double>(1.,2.,3.,4.);
  std::cout <<  "cinf(as(z)) " << " -> " <<  kyosu::cinf(as(z)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
  auto wz =  wc_t(complex_t<double>(1.3,-3.7));
  std::cout << "cinf(as(wz)) " << " -> " << kyosu::cinf(as(wz)) << "\n";

  return 0;
}
