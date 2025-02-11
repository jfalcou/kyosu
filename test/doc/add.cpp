#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::add;
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;
  using we_t = eve::wide<float, eve::fixed<2>>;
  using wc_t = eve::wide<kyosu::complex_t<float>, eve::fixed<2>>;
  using wq_t = eve::wide<kyosu::quaternion_t<float>, eve::fixed<2>>;

  std::cout << "Real:        "<< "\n";
  e_t e0(3);
  e_t e1(2);
  std::cout << e0 << ", " << e1 << " -> "  << kyosu::add(e0, e1) << "\n";
  std::cout << e0 << ", " << e0 << " -> "  << add(e0, e0) << "\n";
  we_t we0(e0);
  we_t we1(e1);
  std::cout << we0 << ", " << we1 << " -> " << add(we0, we1) << "\n";

  std::cout << "Complex:     "<< "\n";
  c_t c0(1, 5);
  c_t c1(5, 9);
  std::cout << c0 << ", " << c1 << " -> "  << add(c0, c1) << "\n";
  std::cout << c0 << ", " << c0 << " -> "  << add(c0, c0) << "\n";
  wc_t wc0(c0, c1);
  wc_t wc1(c1, c1);
  std::cout << wc0 << ", " << wc1 << " -> " << add(wc0, wc1) << "\n";

  std::cout << "Quaternion:  "<< "\n";
  q_t q0(1, 5, 2, 3);
  q_t q1(5, 9, 6, 7);
  std::cout << q0 << ", " << q1 << " -> "  << add(q0, q1) << "\n";
  std::cout << q0 << ", " << q0 << " -> "  << add(q0, q0) << "\n";
  std::cout << q0 << ", " << q0 << ", " << q1 << " -> "  << add(q0, q0, q1) << "\n";
  wq_t wq0(q0, q1);
  wq_t wq1(q1, q1);
  std::cout << wq0 << ", " << wq1 << " -> " << add(wq0, wq1) << "\n";

  std::cout << "Mixed:  "<< "\n";
  std::cout << kyosu::add(c0, e0) << std::endl;
  std::cout << kyosu::add(c0, c0, c1) << std::endl;
  std::cout << kyosu::add(c0, e0, c1) << std::endl;
  std::cout << kyosu::add(c0, q1, e0) << std::endl;
  std::cout << kyosu::add(e0, q1, c1) << std::endl;
  std::cout << kyosu::add(c0, wq1) << std::endl;
  std::cout << kyosu::add(we0, q1) << std::endl;

  std::cout << c0 <<  " == " <<  e0 << " == " << kyosu::add[e0 > 32](c0, e0) << std::endl;
  std::cout << c0 <<  " == " <<  e0 << " == " << kyosu::add[e0 <  32](c0, e0) << std::endl;
  kumi::tuple s{c0, c0, c1};
  std::cout <<  "kyosu::add( kumi::tuple s{c0, c0, c1}) == " << kyosu::add(s) << std::endl;
  return 0;
}
