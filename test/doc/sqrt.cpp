#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using kyosu::sqrt;

  std::cout << "Real:        ";
  std::cout << 72.9f << " -> " << sqrt(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << kyosu::complex_t<float>(3.5f, -2.9f) << " -> " << sqrt(kyosu::complex_t<float>(3.5f, -2.9f)) << "\n";

  std::cout << "Quaternion:  ";
  std::cout << kyosu::quaternion_t<double>(1., 2., 3., 4.) << " -> "
            << sqrt(kyosu::quaternion_t<double>(1., 2., 3., 4.)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
  std::cout << wc_t(kyosu::complex_t<double>(1.3, -3.7)) << " -> " << sqrt(wc_t(kyosu::complex_t<double>(1.3, -3.7)))
            << "\n";

  using e_t = float;
  using z_t = kyosu::complex_t<e_t>;
  using k_t = eve::wide<e_t, eve::fixed<2>>;
  z_t z{e_t(1.0), e_t(2.0)};
  k_t k{0, 1};
  e_t e(1.0);

  std::cout << "z " << z << std::endl;
  std::cout << "k " << k << std::endl;
  std::cout << "sqrt(z) "     << sqrt(z) << std::endl;
  std::cout << "sqrt(z, k) "  << sqrt(z, k) << std::endl;
  std::cout << "sqrt(e) "     << sqrt(e) << std::endl;
  std::cout << "sqrt[real_only](e) "     << sqrt[real_only](e) << std::endl;
  std::cout << "sqrt(-e)"     << sqrt(-e) << std::endl;
  std::cout << "sqrt[real_only](-e) "     << sqrt[real_only](-e) << std::endl;
  std::cout << "sqrt(e, k) "  << sqrt(e, k) << std::endl;
  std::cout << "sqrt[real_only](e, k) "  << sqrt[real_only](e, k) << std::endl;
  std::cout << "sqrt[real_only](-e, k) "  << sqrt[real_only](-e, k) << std::endl;
  std::cout << "sqrt[real_only](z, k) "  << sqrt[real_only](z, k) << std::endl;

  return 0;
}
