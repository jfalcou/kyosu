#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using eve::as;
  using kyosu::complex_t;
  using kyosu::is_fnan;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;
  using we_t = eve::wide<e_t, eve::fixed<4>>;
  using wc_t = eve::wide<c_t, eve::fixed<4>>;
  using wq_t = eve::wide<q_t, eve::fixed<4>>;

  std::cout << "Real:        \n";
  e_t e(2.9f);
  e_t fnan = kyosu::fnan(as(e));
  e_t nan = eve::nan(as(e));
  e_t inf = eve::inf(as(e));
  e_t zer = eve::zero(as(e));
  we_t we = we_t(fnan, inf, zer, nan);
  std::cout << e << " -> " << is_fnan(e) << "\n";
  std::cout << nan << " -> " << is_fnan(nan) << "\n";
  std::cout << we << " -> " << is_fnan(we) << "\n";
  std::cout << is_fnan(c_t(e)) << "\n";
  std::cout << is_fnan(q_t(e)) << "\n";
  std::cout << is_fnan(kyosu::complex(we)) << "\n";
  std::cout << is_fnan(kyosu::quaternion(we)) << "\n";

  std::cout << "Complex:     \n";
  c_t c(3.5f, -2.9f);
  c_t d(0.0f, inf);
  c_t cfnan(kyosu::fnan(as<c_t>()));
  wc_t wc = wc_t(c, zer, cfnan, d);
  std::cout << c << " -> " << is_fnan(c) << "\n";
  std::cout << wc << " -> " << is_fnan(wc) << "\n";
  std::cout << is_fnan(kyosu::complex(wc)) << "\n";
  ;
  std::cout << is_fnan(kyosu::quaternion(wc)) << "\n";

  std::cout << "Quaternion:  \n";
  q_t qfnan(kyosu::fnan(as<q_t>()));
  q_t q(3.5f, -2.9f, 2.1f, 3.2f);
  q_t r(3.5f, nan, inf, nan);
  wq_t wq = wq_t(q, nan, qfnan, r);
  std::cout << q << " -> " << is_fnan(q) << "\n";
  std::cout << wq << " -> " << is_fnan(wq) << "\n";

  return 0;
}
