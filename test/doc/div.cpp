#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::div;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;
  using we_t = eve::wide<float, eve::fixed<2>>;
  using wc_t = eve::wide<kyosu::complex_t<float>, eve::fixed<2>>;
  using wq_t = eve::wide<kyosu::quaternion_t<float>, eve::fixed<2>>;

  std::cout << "Real:        " << "\n";
  e_t e0(3);
  e_t e1(2);
  std::cout << e0 << ", " << e1 << " -> " << kyosu::div(e0, e1) << "\n";
  std::cout << e0 << ", " << e0 << " -> " << div(e0, e0) << "\n";
  we_t we0(e0);
  we_t we1(e1);
  std::cout << we0 << ", " << we1 << " -> " << div(we0, we1) << "\n";

  std::cout << "Complex:     " << "\n";
  c_t c0(1, 5);
  c_t c1(5, 9);
  std::cout << c0 << ", " << c1 << " -> " << div(c0, c1) << "\n";
  std::cout << c0 << ", " << c0 << " -> " << div(c0, c0) << "\n";
  wc_t wc0(c0, c1);
  wc_t wc1(c1, c1);
  std::cout << wc0 << ", " << wc1 << " -> " << div(wc0, wc1) << "\n";

  std::cout << "Quaternion:  " << "\n";
  q_t q0(1, 5, 2, 3);
  q_t q1(5, 9, 6, 7);
  std::cout << q0 << ", " << q1 << " -> " << div(q0, q1) << "\n";
  std::cout << q0 << ", " << q0 << " -> " << div(q0, q0) << "\n";
  std::cout << q0 << ", " << q0 << ", " << q1 << " -> " << div(q0, q0, q1) << "\n";
  wq_t wq0(q0, q1);
  wq_t wq1(q1, q1);
  std::cout << wq0 << ", " << wq1 << " -> " << div(wq0, wq1) << "\n";

  std::cout << "Mixed:  " << "\n";
  std::cout << kyosu::div(c0, e0) << std::endl;
  std::cout << kyosu::div(c0, c0, c1) << std::endl;
  std::cout << kyosu::div(c0, e0, c1) << std::endl;
  std::cout << kyosu::div(c0, q1, e0) << std::endl;
  std::cout << kyosu::div(e0, q1, c1) << std::endl;
  std::cout << kyosu::div(c0, wq1) << std::endl;
  std::cout << kyosu::div(we0, q1) << std::endl;

  std::cout << c0 << " == " << e0 << " == " << kyosu::div[e0 > 32](c0, e0) << std::endl;
  std::cout << c0 << " == " << e0 << " == " << kyosu::div[e0 < 32](c0, e0) << std::endl;
  kumi::tuple s{c0, c0, c1};
  std::cout << "kyosu::div( kumi::tuple s{c0, c0, c1}) == " << kyosu::div(s) << std::endl;
  return 0;
}
