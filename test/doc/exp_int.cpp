#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::exp;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;
  using we_t = eve::wide<e_t, eve::fixed<2>>;
  using wc_t = eve::wide<c_t, eve::fixed<2>>;
  using wq_t = eve::wide<q_t, eve::fixed<2>>;

  using kyosu::exp_int;
  std::cout << "Real:        \n";
  e_t e(2.9f);
  we_t we = we_t(e);
  std::cout << e << " -> " << exp_int(e) << "\n";
  std::cout << we << " -> " << exp_int(we) << "\n";
  std::cout << exp_int(c_t(e)) << "\n";
  std::cout << exp_int(q_t(e)) << "\n";
  std::cout << exp_int(wc_t(e)) << "\n";
  std::cout << exp_int(wq_t(e)) << "\n";

  std::cout << "Complex:     \n";
  c_t c(3.5f, -2.9f);
  wc_t wc = wc_t(c);
  std::cout << c << " -> " << exp_int(c) << "\n";
  std::cout << wc << " -> " << exp_int(wc) << "\n";
  std::cout << exp_int(q_t(c)) << "\n";
  std::cout << exp_int(wq_t(c)) << "\n";

  std::cout << "Quaternion:  \n";
  q_t q(3.5f, -2.9f, 2.1f, 3.2f);
  wq_t wq = wq_t(q);
  std::cout << q << " -> " << exp_int(q) << "\n";
  std::cout << wq << " -> " << exp_int(wq) << "\n";

  return 0;
}
