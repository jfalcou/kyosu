#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::average;
  using kyosu::complex;
  using kyosu::quaternion;
  using e_t = float;
  using c_t = complex<float>;
  using q_t = quaternion<float>;
  using we_t = eve::wide<float, eve::fixed<2>>;
  using wc_t = eve::wide<complex<float>, eve::fixed<2>>;
  using wq_t = eve::wide<quaternion<float>, eve::fixed<2>>;

  std::cout << "Real:        "<< "\n";
  e_t e0(1);
  e_t e1(2);
  std::cout << e0 << ", " << e1 << " -> "  << average(e0, e1) << "\n";
  std::cout << e0 << ", " << e0 << " -> "  << average(e0, e0) << "\n";
  we_t we0(e0);
  we_t we1(e1);
  std::cout << we0 << ", " << we1 << " -> " << average(we0, we1) << "\n";

  std::cout << "Complex:     "<< "\n";
  c_t c0(1, 5);
  c_t c1(5, 9);
  std::cout << c0 << ", " << c1 << " -> "  << average(c0, c1) << "\n";
  std::cout << c0 << ", " << c0 << " -> "  << average(c0, c0) << "\n";
  wc_t wc0(c0, c1);
  wc_t wc1(c1, c1);
  std::cout << wc0 << ", " << wc1 << " -> " << average(wc0, wc1) << "\n";

  std::cout << "Quaternion:  "<< "\n";
  q_t q0(1, 5, 2, 3);
  q_t q1(5, 9, 6, 7);
  std::cout << q0 << ", " << q1 << " -> "  << average(q0, q1) << "\n";
  std::cout << q0 << ", " << q0 << " -> "  << average(q0, q0) << "\n";
  wq_t wq0(q0, q1);
  wq_t wq1(q1, q1);
  std::cout << wq0 << ", " << wq1 << " -> " << average(wq0, wq1) << "\n";

  std::cout << "Mixed:  "<< "\n";
  std::cout << kyosu::average(c0, q1) << std::endl;
  std::cout << kyosu::average(e0, q1) << std::endl;
  std::cout << kyosu::average(c0, wq1) << std::endl;
  std::cout << kyosu::average(we0, q1) << std::endl;

  return 0;
}
