#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::rsqrt;
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using kyosu::real_only;

  std::cout << "Real:        ";
  std::cout << 72.9f << " -> " << rsqrt(72.9f) << "\n";

  std::cout << "Complex:     ";
  std::cout << kyosu::complex_t<float>(3.5f,-2.9f) << " -> " << rsqrt(kyosu::complex_t<float>(3.5f,-2.9f)) << "\n";

  std::cout << "Quaternion:  ";
  std::cout << kyosu::quaternion_t<double>(1.,2.,3.,4.) << " -> " << rsqrt(kyosu::quaternion_t<double>(1.,2.,3.,4.)) << "\n";

  std::cout << "SIMD:        ";
  using wc_t = eve::wide<kyosu::complex_t<double>, eve::fixed<2>>;
  std::cout << wc_t(kyosu::complex_t<double>(1.3,-3.7)) << " -> " << rsqrt(wc_t(kyosu::complex_t<double>(1.3,-3.7))) << "\n";

  using e_t = float;
  using z_t = kyosu::complex_t<e_t>;
  using k_t = eve::wide<e_t, eve::fixed<2>>;
  z_t z{e_t(1.0), e_t(2.0)};
  k_t k{0, 1};
  e_t e(1.0);

  std::cout << "z                       " << z << std::endl;
  std::cout << "k                       " << k << std::endl;
  std::cout << "rsqrt(z)                " << rsqrt(z) << std::endl;
  std::cout << "rsqrt(z, k)             " << rsqrt(z, k) << std::endl;
  std::cout << "rsqrt(e)                " << rsqrt(e) << std::endl;
  std::cout << "rsqrt[real_only](e)     " << rsqrt[real_only](e) << std::endl;
  std::cout << "rsqrt(-e)               " << rsqrt(-e) << std::endl;
  std::cout << "rsqrt[real_only](-e)    " << rsqrt[real_only](-e) << std::endl;
  std::cout << "rsqrt(e, k)             " << rsqrt(e, k) << std::endl;
  std::cout << "rsqrt[real_only](e, k)  " << rsqrt[real_only](e, k) << std::endl;
  std::cout << "rsqrt[real_only](-e, k) " << rsqrt[real_only](-e, k) << std::endl;
  std::cout << "rsqrt[real_only](z, k)  " << rsqrt[real_only](z, k) << std::endl;

  return 0;
}
