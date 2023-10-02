#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::fnms;
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;
  using we_t = eve::wide<float, eve::fixed<2>>;
  using wq_t = eve::wide<kyosu::quaternion_t<float>, eve::fixed<2>>;

  std::cout << "Real:        "<< "\n";
  e_t e0(1);
  e_t e1(2);
  e_t e2(3);
  std::cout << e0 << ", " << e1 << ", " << e2 << " -> "  << fnms(e0, e1, e2) << "\n";
  std::cout << e0 << ", " << e0 << ", " << e2 << " -> "  << fnms(e0, e0, e2) << "\n";
  we_t we0(e0);
  we_t we1(e1);
  we_t we2(e2, e0);
  std::cout << we0 << ", " << we1 << ", " << we2<< " -> " << fnms(we0, we1, we2) << "\n";

  std::cout << "Complex:     "<< "\n";
  c_t c0(1, 5);
  c_t c1(5, 9);
  c_t c2(2, -5);
  std::cout << c0 << ", " << c1 << ", " << c2 << " -> "  << fnms(c0, c1, e2) << "\n";
  std::cout << c0 << ", " << c0 << ", " << c2 << " -> "  << fnms(c0, c0, e2) << "\n";

  std::cout << "Quaternion:  "<< "\n";
  q_t q0(1, 5, 2, 3);
  q_t q1(5, 9, 6, 7);
  q_t q2(7, -3, 0, 1);
  wq_t wq1(q1, q2);
  std::cout << q0 << ", " << q1 << ", " << q2 << " -> "  << fnms(q0, q1, q2) << "\n";
  std::cout << q0 << ", " << q0 << ", " << q2 << " -> "  << fnms(q0, q0, q2) << "\n";

  std::cout << "Mixed:  "<< "\n";
  std::cout << c0 << ", " << q1 << ", " << e2 << " -> "  << kyosu::fnms(c0, q1, e2) << std::endl;
  std::cout << e0 << ", " << q1 << ", " << q2 << " -> "  << kyosu::fnms(e0, q1, q2) << std::endl;
  std::cout << c0 << ", " << wq1<< ", " << e2 << " -> "  << kyosu::fnms(c0, we1, q2) << std::endl;
  std::cout << we0<< ", " << q1 << ", " << e2 << " -> "  << kyosu::fnms(we0, q1, e2) << std::endl;

  return 0;
}
