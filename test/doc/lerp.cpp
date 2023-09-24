#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::lerp;
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
  e_t e1(2);
  e_t t(0.3);
  std::cout << e0 << ", " << e1 << ", " << t << " -> "  << lerp(e0, e1, t) << "\n";
  std::cout << e0 << ", " << e0 << ", " << t << " -> "  << lerp(e0, e0, t) << "\n";
  we_t we0(e0);
  we_t we1(e1);
  std::cout << we0 << ", " << we1 << ", " << t<< " -> " << lerp(we0, we1, t) << "\n";

  std::cout << "Complex:     "<< "\n";
  c_t c0(1, 5);
  c_t c1(5, 9);
  std::cout << c0 << ", " << c1 << ", " << t << " -> "  << lerp(c0, c1, t) << "\n";
  std::cout << c0 << ", " << c0 << ", " << t << " -> "  << lerp(c0, c0, t) << "\n";
  wc_t wc0(c0, c1);
  wc_t wc1(c1, c1);
  std::cout << wc0 << ", " << wc1 << ", " << t << " -> " << lerp(wc0, wc1, t) << "\n";

  std::cout << "Quaternion:  "<< "\n";
  q_t q0(1, 5, 2, 3);
  q_t q1(5, 9, 6, 7);
  std::cout << q0 << ", " << q1 << ", " << t << " -> "  << lerp(q0, q1, t) << "\n";
  std::cout << q0 << ", " << q0 << ", " << t << " -> "  << lerp(q0, q0, t) << "\n";
  wq_t wq0(q0, q1);
  wq_t wq1(q1, q1);
  std::cout << wq0 << ", " << wq1 << ", " << t << " -> " << lerp(wq0, wq1, t) << "\n";

  std::cout << "Mixed:  "<< "\n";
  std::cout << c0 << ", " << q1 << ", " << t << " -> "  << kyosu::lerp(c0, q1, t) << std::endl;
  std::cout << e0 << ", " << q1 << ", " << t << " -> "  << kyosu::lerp(e0, q1, t) << std::endl;
  std::cout << c0 << ", " << wq1<< ", " << t << " -> "  << kyosu::lerp(c0, wq1, t) << std::endl;
  std::cout << we0<< ", " << q1 << ", " << t << " -> "  << kyosu::lerp(we0, q1, t) << std::endl;

  return 0;
}
