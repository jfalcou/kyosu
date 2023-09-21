#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::log;
  using kyosu::as_complex_t;
  using kyosu::as_quaternion_t;
  using e_t = float;
  using c_t = kyosu::as_complex_t<float>;
  using q_t = kyosu::as_quaternion_t<float>;
  using we_t = eve::wide<e_t, eve::fixed<2>>;
  using wc_t = eve::wide<c_t, eve::fixed<2>>;
  using wq_t = eve::wide<q_t, eve::fixed<2>>;

  std::cout << "Real:        \n";
  e_t e(2.9f);
  we_t we = we_t(e);
  std::cout << e << " -> " << log(e) << "\n";
  std::cout << we << " -> " << log(we) << "\n";
  std::cout               << log(c_t(e))<< "\n";
  std::cout               << log(q_t(e))<< "\n";
  std::cout               << log(wc_t(e))<< "\n";
  std::cout               << log(wq_t(e))<< "\n";

  std::cout << "Complex:     \n";
  c_t c(3.5f,-2.9f);
  wc_t wc = wc_t(c);
  std::cout << c << " -> " << log(c) << "\n";
  std::cout << wc << " -> " << log(wc) << "\n";
  std::cout               << log(q_t(c))<< "\n";
  std::cout               << log(wq_t(c))<< "\n";

  std::cout << "Quaternion:  \n";
  q_t q(3.5f,-2.9f, 2.1f, 3.2f);
  wq_t wq = wq_t(q);
  std::cout << q << " -> " << log(q) << "\n";
  std::cout << wq << " -> " << log(wq) << "\n";

  return 0;
}
