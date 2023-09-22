#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::to_semipolar;
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;
  using we_t = eve::wide<float, eve::fixed<2>>;
  using wc_t = eve::wide<kyosu::complex_t<float>, eve::fixed<2>>;
  using wq_t = eve::wide<kyosu::quaternion_t<float>, eve::fixed<2>>;

  std::cout << "Real:        "<< "\n";
  e_t e0(1);
  std::cout << e0 << " -> "  << to_semipolar(e0) << "\n";
  we_t we0(e0);
  std::cout << we0 << " -> " << to_semipolar(we0) << "\n";

  std::cout << "Complex:     "<< "\n";
  c_t c0(1, 5);
  std::cout << c0 << " -> "  << to_semipolar(c0) << "\n";
  wc_t wc0(c0);
  std::cout << wc0 << " -> " << to_semipolar(wc0) << "\n";

  std::cout << "Quaternion:  "<< "\n";
  q_t q0(1, 5, 2, 3);
  std::cout << q0 << " -> "  << to_semipolar(q0) << "\n";
  wq_t wq0(q0);
  std::cout << wq0 << " -> " << to_semipolar(wq0) << "\n";

  return 0;
}
