#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using eve::as;
  using kyosu::complex_t;
  using kyosu::is_not_cinf;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;
  using wc_t = eve::wide<c_t, eve::fixed<4>>;
  using wq_t = eve::wide<q_t, eve::fixed<4>>;

  e_t nan = eve::nan(as<e_t>());
  e_t inf = eve::inf(as<e_t>());
  e_t zer = eve::zero(as<e_t>());

  std::cout << "Complex:     \n";
  c_t c(3.5f, -2.9f);
  c_t d(inf, nan);
  c_t ccinf(kyosu::cinf(as<c_t>()));
  wc_t wc = wc_t(c, zer, ccinf, d);
  std::cout << c << " -> " << is_not_cinf(c) << "\n";
  std::cout << wc << " -> " << is_not_cinf(wc) << "\n";
  std::cout << is_not_cinf(kyosu::complex(wc)) << "\n";
  ;
  std::cout << is_not_cinf(kyosu::quaternion(wc)) << "\n";

  std::cout << "Quaternion:  \n";
  q_t qcinf(kyosu::cinf(as<q_t>()));
  q_t q(3.5f, -2.9f, 2.1f, 3.2f);
  q_t r(3.5f, nan, 6.0f, inf);
  wq_t wq = wq_t(q, nan, qcinf, r);
  std::cout << q << " -> " << is_not_cinf(q) << "\n";
  std::cout << wq << " -> " << is_not_cinf(wq) << "\n";
  std::cout << "kyosu::abs(wq) " << kyosu::abs(wq) << std::endl;
  std::cout << "kyosu::arg(wq) " << kyosu::arg(wq) << std::endl;

  return 0;
}
