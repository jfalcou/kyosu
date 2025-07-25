#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::kronecker;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using we_t = eve::wide<float, eve::fixed<2>>;
  using wc_t = eve::wide<kyosu::complex_t<float>, eve::fixed<2>>;

  std::cout << "Real:        "<< "\n";
  e_t e0(3);
  e_t e1(2);
  std::cout << e0 << ", " << e1 << " -> "  << kyosu::kronecker(e0, e1) << "\n";
  std::cout << e0 << ", " << e0 << " -> "  << kronecker(e0, e0) << "\n";
  std::cout << e0 << ", " << e1 << ", " << e1 << " -> "  << kyosu::kronecker(e0, e1, e1) << "\n";
  std::cout << e0 << ", " << e0 << ", " << e0 << " -> "  << kronecker(e0, e0, e0) << "\n";
  we_t we0{e0, e1};
  we_t we1(e1);
  std::cout << we0 << ", " << we1 << ", " << we1 << " -> " << kronecker(we0, we1, we1) << "\n";
  std::cout << we0 << ", " << we1 << ", " << we1 << " -> " << kronecker(we0, we1, we1) << "\n";


  std::cout << "Complex:     "<< "\n";
  c_t c0(1, 5);
  c_t c1(5, 9);
  std::cout << c0 << ", " << c1 << " -> "  << kronecker(c0, c1) << "\n";
  std::cout << c0 << ", " << c0 << " -> "  << kronecker(c0, c0) << "\n";
  std::cout << c0 << ", " << c1 << ", " << c1 << " -> "  << kyosu::kronecker(c0, c1, c1) << "\n";
  std::cout << c0 << ", " << c0 << ", " << c0 << " -> "  << kronecker(c0, c0, c0) << "\n";
  wc_t wc0(c0, c1);
  wc_t wc1(c1, c1);
  std::cout << wc0 << ", " << wc1 << " -> " << kronecker(wc0, wc1) << "\n";

  return 0;
}
