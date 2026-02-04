#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::cot;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;
  using we_t = eve::wide<e_t, eve::fixed<2>>;
  using wc_t = eve::wide<c_t, eve::fixed<2>>;
  using wq_t = eve::wide<q_t, eve::fixed<2>>;

  std::cout << "Real:        \n";
  e_t e(2.9f);
  we_t we = we_t(e);
  std::cout << e << " -> " << cot(e) << "\n";
  std::cout << we << " -> " << cot(we) << "\n";
  std::cout << cot(c_t(e)) << "\n";
  std::cout << cot(q_t(e)) << "\n";
  std::cout << cot(wc_t(e)) << "\n";
  std::cout << cot(wq_t(e)) << "\n";

  std::cout << "Complex:     \n";
  c_t c(3.5f, -2.9f);
  wc_t wc = wc_t(c);
  std::cout << c << " -> " << cot(c) << "\n";
  std::cout << wc << " -> " << cot(wc) << "\n";
  std::cout << cot(q_t(c)) << "\n";
  std::cout << cot(wq_t(c)) << "\n";

  std::cout << "Quaternion:  \n";
  q_t q(3.5f, -2.9f, 2.1f, 3.2f);
  wq_t wq = wq_t(q);
  std::cout << q << " -> " << cot(q) << "\n";
  std::cout << wq << " -> " << cot(wq) << "\n";

  return 0;
}
