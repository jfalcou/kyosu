#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::is_denormal;
  using kyosu::complex;
  using kyosu::quaternion;
  using e_t = float;
  using c_t = complex<float>;
  using q_t = quaternion<float>;
  using we_t = eve::wide<e_t, eve::fixed<2>>;
  using wc_t = eve::wide<c_t, eve::fixed<2>>;
  using wq_t = eve::wide<q_t, eve::fixed<2>>;

  std::cout << "Real:        \n";
  e_t e(2.9f);
  we_t we = we_t(e);
  std::cout << e << " -> " << is_denormal(e) << "\n";
  std::cout << we << " -> " << is_denormal(we) << "\n";
  std::cout               << is_denormal(c_t(e))<< "\n";
  std::cout               << is_denormal(q_t(e))<< "\n";
  std::cout               << is_denormal(wc_t(e))<< "\n";
  std::cout               << is_denormal(wq_t(e))<< "\n";

  std::cout << "Complex:     \n";
  c_t c(3.5f,-2.9f);
  wc_t wc = wc_t(c);
  std::cout << c << " -> " << is_denormal(c) << "\n";
  std::cout << wc << " -> " << is_denormal(wc) << "\n";
  std::cout               << is_denormal(q_t(c))<< "\n";
  std::cout               << is_denormal(wq_t(c))<< "\n";

  std::cout << "Quaternion:  \n";
  q_t q(3.5f,-2.9f, 2.1f, 3.2f);
  wq_t wq = wq_t(q);
  std::cout << q << " -> " << is_denormal(q) << "\n";
  std::cout << wq << " -> " << is_denormal(wq) << "\n";

  return 0;
}
