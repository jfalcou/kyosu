#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::is_not_denormal;
  using kyosu::as_complex_t;
  using kyosu::as_quaternion_t;
  using eve::as;
  using e_t = float;
  using c_t = kyosu::as_complex_t<float>;
  using q_t = kyosu::as_quaternion_t<float>;
  using we_t = eve::wide<e_t, eve::fixed<4>>;
  using wc_t = eve::wide<c_t, eve::fixed<4>>;
  using wq_t = eve::wide<q_t, eve::fixed<4>>;

  std::cout << "Real:        \n";
  e_t e(2.9f);
  e_t nan = eve::nan(as(e));
  e_t inf = eve::inf(as(e));
  e_t zer = eve::zero(as(e));
  e_t mind= eve::mindenormal(as(e));
  we_t we = we_t(e, zer, nan, mind);
  std::cout << e << " -> " << is_not_denormal(e) << "\n";
  std::cout << we << " -> " << is_not_denormal(we) << "\n";
  std::cout               << is_not_denormal(c_t(e))<< "\n";
  std::cout               << is_not_denormal(q_t(e))<< "\n";
  std::cout               << is_not_denormal(kyosu::to_complex(we))<< "\n";
  std::cout               << is_not_denormal(kyosu::to_quaternion(we))<< "\n";

  std::cout << "Complex:     \n";
  c_t c(3.5f,-2.9f);
  c_t d(0.0f, mind);
  wc_t wc = wc_t(c, zer, nan, d);
  std::cout << c << " -> " << is_not_denormal(c) << "\n";
  std::cout << wc << " -> " << is_not_denormal(wc) << "\n";
  std::cout                 << is_not_denormal(kyosu::to_complex(wc))<< "\n";;
  std::cout                 << is_not_denormal(kyosu::to_quaternion(wc))<< "\n";

  std::cout << "Quaternion:  \n";
  q_t q(3.5f,-2.9f, mind, 3.2f);
  q_t r(3.5f, nan, inf, zer);
  wq_t wq = wq_t(q, zer, nan, r);
  std::cout << q << " -> " << is_not_denormal(q) << "\n";
  std::cout << wq << " -> " << is_not_denormal(wq) << "\n";

  return 0;
}
