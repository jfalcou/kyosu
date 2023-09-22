#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::log10;
  using kyosu::complex_t;
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
  std::cout << e << " -> " << log10(e) << "\n";
  std::cout << we << " -> " << log10(we) << "\n";
  std::cout               << log10(c_t(e))<< "\n";
  std::cout               << log10(q_t(e))<< "\n";
  std::cout               << log10(wc_t(e))<< "\n";
  std::cout               << log10(wq_t(e))<< "\n";

  std::cout << "Complex:     \n";
  c_t c(3.5f,-2.9f);
  wc_t wc = wc_t(c);
  std::cout << c << " -> " << log10(c) << "\n";
  std::cout << wc << " -> " << log10(wc) << "\n";
  std::cout               << log10(q_t(c))<< "\n";
  std::cout               << log10(wq_t(c))<< "\n";

  std::cout << "Quaternion:  \n";
  q_t q(3.5f,-2.9f, 2.1f, 3.2f);
  wq_t wq = wq_t(q);
  std::cout << q << " -> " << log10(q) << "\n";
  std::cout << wq << " -> " << log10(wq) << "\n";

  return 0;
}
