#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::is_unitary;
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
  std::cout << e << " -> " << is_unitary(e) << "\n";
  std::cout << we << " -> " << is_unitary(we) << "\n";
  std::cout               << is_unitary(c_t(e))<< "\n";
  std::cout               << is_unitary(q_t(e))<< "\n";
  std::cout               << is_unitary(wc_t(e))<< "\n";
  std::cout               << is_unitary(wq_t(e))<< "\n";

  std::cout << "Complex:     \n";
  c_t c(3.5f,-2.9f);
  wc_t wc = wc_t(c);
  std::cout << c << " -> " << is_unitary(c) << "\n";
  std::cout << wc << " -> " << is_unitary(wc) << "\n";
  std::cout               << is_unitary(q_t(c))<< "\n";
  std::cout               << is_unitary(wq_t(c))<< "\n";

  std::cout << "Quaternion:  \n";
  q_t q(3.5f,-2.9f, 2.1f, 3.2f);
  wq_t wq = wq_t(q);
  std::cout << q << " -> " << is_unitary(q) << "\n";
  std::cout << wq << " -> " << is_unitary(wq) << "\n";

  return 0;
}
