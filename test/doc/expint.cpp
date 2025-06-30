#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::exp;
  using kyosu::complex_t;
  using e_t = float;
  using we_t = eve::wide<e_t, eve::fixed<2>>;

  std::cout << "Real:        \n";
  e_t e(2.9);
  we_t we = we_t(e);
  std::cout << e << " -> " << kyosu::expint(e) << "\n";
  std::cout << we << " -> " << kyosu::expint(we) << "\n";


//   using c_t = kyosu::complex_t<float>;
//   using wc_t = eve::wide<c_t, eve::fixed<2>>;
//   std::cout << "Complex:     \n";
//   c_t c(3.5f,-2.9f);
//   wc_t wc = wc_t(c);
//   std::cout << c << " -> " << expint(c) << "\n";
//   std::cout << wc << " -> " << expint(wc) << "\n";
//   std::cout               << expint(q_t(c))<< "\n";
//   std::cout               << expint(wq_t(c))<< "\n";

   return 0;
}
