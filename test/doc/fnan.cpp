#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::as;
  using kyosu::complex_t;
  using kyosu::quaternion_t;

  std::cout << "Real:        \n";
  auto fnan = kyosu::fnan(kyosu::as(72.9f));
  std::cout << "fnan  = " << fnan << "\n";
  std::cout << "rec(fnan) = " << kyosu::rec(fnan) << std::endl;
  std::cout << "1.0f/fnan = " << 1.0 / fnan << std::endl;
  std::cout << 1.0f / kyosu::complex_t<float>(0.0, 0.0) << std::endl;
  std::cout << "kyosu::abs(fnan) " << kyosu::abs(fnan) << std::endl;
  std::cout << "kyosu::arg(fnan) " << kyosu::arg(fnan) << std::endl;
  std::cout << "Complex:     \n";
  auto c = kyosu::complex_t<float>(3.5f, -2.9f);
  std::cout << "c       = " << c << std::endl;
  std::cout << "fnan(as(c)) " << " -> " << kyosu::fnan(as(c)) << "\n";
  std::cout << c / kyosu::complex_t<float>(0.0, 0.0) << std::endl;
  std::cout << c / 0.0f << std::endl;

  std::cout << "Quaternion:  \n";
  auto z = kyosu::quaternion_t<double>(1., 2., 3., 4.);
  std::cout << "fnan(as(z)) " << " -> " << kyosu::fnan(as(z)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
  auto wz = wc_t(complex_t<double>(1.3, -3.7));
  std::cout << "fnan(as(wz)) " << " -> " << kyosu::fnan(as(wz)) << "\n";

  return 0;
}
