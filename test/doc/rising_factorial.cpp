#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using kyosu::rising_factorial;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using we_t = eve::wide<float, eve::fixed<2>>;
  using wc_t = eve::wide<kyosu::complex_t<float>, eve::fixed<2>>;

  std::cout << "Real:        " << "\n";
  e_t e0(1);
  e_t e1(2);
  std::cout << e0 << ", " << e1 << " -> " << rising_factorial(e0, e1) << "\n";
  std::cout << e0 << ", " << e0 << " -> " << rising_factorial(e0, e0) << "\n";
  we_t we0(e0);
  we_t we1(e1);
  std::cout << we0 << ", " << we1 << " -> " << rising_factorial(we0, we1) << "\n";

  std::cout << "Complex:     " << "\n";
  c_t c0(1, 5);
  c_t c1(5, 9);
  std::cout << c0 << ", " << c1 << " -> " << rising_factorial(c0, c1) << "\n";
  std::cout << c0 << ", " << c0 << " -> " << rising_factorial(c0, c0) << "\n";
  wc_t wc0(c0, c1);
  wc_t wc1(c1, c1);
  std::cout << wc0 << ", " << wc1 << " -> " << rising_factorial(wc0, wc1) << "\n";

  return 0;
}
