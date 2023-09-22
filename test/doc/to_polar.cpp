#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::to_polar;
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using we_t = eve::wide<float, eve::fixed<2>>;
  using wc_t = eve::wide<kyosu::complex_t<float>, eve::fixed<2>>;

  std::cout << "Real:        "<< "\n";
  e_t e0(1);
  e_t e1(-2);
  std::cout << e0 << " -> "  << to_polar(e0) << "\n";
  std::cout << e1 << " -> "  << to_polar(e1) << "\n";
  we_t we0(e0);
  we_t we1(e1);
  std::cout << we0 << " -> " << to_polar(we0) << "\n";
  std::cout << we1 << " -> " << to_polar(we1) << "\n";

  std::cout << "Complex:     "<< "\n";
  c_t c0(3, -4);
  std::cout << c0 << " -> "  << to_polar(c0) << "\n";
  wc_t wc0(c0);
  std::cout << wc0 << " -> " << to_polar(wc0) << "\n";

  return 0;
}
