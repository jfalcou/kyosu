#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::is_unitary;
  using kyosu::complex;
  using kyosu::quaternion;
  using e_t = float;
  using c_t = complex<float>;
  using q_t = quaternion<float>;
  using we_t = eve::wide<e_t, eve::fixed<2>>;
  using wc_t = eve::wide<c_t, eve::fixed<2>>;
  using wq_t = eve::wide<q_t, eve::fixed<2>>;

  std::cout << "Real:        \n";
  e_t e(72.9f);
  we_t we = we_t(e);
  e_t ue = kyosu::sign(e);
  we_t uwe = kyosu::sign(we);
  std::cout << e << " -> " << is_unitary(e) << "\n";
  std::cout << we << " -> " << is_unitary(we) << "\n";
  std::cout << ue << " -> " << is_unitary(ue) << "\n";
  std::cout << uwe << " -> " << is_unitary(uwe) << "\n";

  std::cout << "Complex:     \n";
  c_t c(3.5f,-2.9f);
  wc_t wc = wc_t(c);
  c_t uc = kyosu::sign(c);
  wc_t uwc = kyosu::sign(wc);
  std::cout << c << " -> " << is_unitary(c) << "\n";
  std::cout << wc << " -> " << is_unitary(wc) << "\n";
  std::cout << uc << " -> " << is_unitary(uc) << "\n";
  std::cout << uwc << " -> " << is_unitary(uwc) << "\n";

  std::cout << "Quaternion:  \n";
  q_t q(3.5f,-2.9f, 2.1f, 3.2f);
  wq_t wq = wq_t(q);
  q_t uq  = kyosu::sign(q);
  wq_t uwq = kyosu::sign(wq);
  std::cout << q << " -> " << is_unitary(q) << "\n";
  std::cout << wq << " -> " << is_unitary(wq) << "\n";
  std::cout << uq << " -> " << is_unitary(uq) << "\n";
  std::cout << uwq << " -> " << is_unitary(uwq) << "\n";

  return 0;
}
