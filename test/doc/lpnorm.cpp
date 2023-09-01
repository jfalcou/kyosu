#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::lpnorm;
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
  std::cout << e0 << ", " << e1 << " -> " << lpnorm(e_t(1), e0, e1) << "\n";
  we_t we0(e0);
  we_t we1(e1);
  std::cout << we0 << ", " << we1 << " -> " << lpnorm(e_t(1), we0, we1) << "\n";

  std::cout << "Complex:     "<< "\n";
  c_t c0(e_t(1), 5);
  c_t c1(5, 9);
  std::cout << c0 << ", " << c1 << " -> " << lpnorm(e_t(1), c0, c1) << "\n";
  wc_t wc0(c0);
  wc_t wc1(c1);
  std::cout << wc0 << ", " << wc1 << " -> " << lpnorm(e_t(1), wc0, wc1) << "\n";

  std::cout << "Quaternion:  "<< "\n";
  q_t q0(e_t(1), 5, 2, 3);
  q_t q1(5, 9, 6, 7);
  std::cout << q0 << ", " << q1 << " -> " << lpnorm(e_t(1), q0, q1) << "\n";
  wq_t wq0(q0);
  wq_t wq1(q1);
  std::cout << wq0 << ", " << wq1 << " -> " << lpnorm(e_t(1), wq0, wq1) << "\n";

  return 0;
}
