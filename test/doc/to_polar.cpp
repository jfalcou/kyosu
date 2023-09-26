#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::to_polar;
  using kyosu::complex_t;
  using kyosu::quaternion_t;
  using e_t = float;
  using c_t = kyosu::complex_t<float>;
  using q_t = kyosu::quaternion_t<float>;
  using we_t = eve::wide<float, eve::fixed<2>>;
  using wc_t = eve::wide<kyosu::complex_t<float>, eve::fixed<2>>;
  using wq_t = eve::wide<kyosu::quaternion_t<float>, eve::fixed<2>>;
  using wq_t = eve::wide<kyosu::quaternion_t<float>, eve::fixed<2>>;

  {
    std::cout << "Real:        "<< "\n";
    e_t e0(1);
    e_t e1(-2);
    auto [r0, t0] = to_polar(e0);
    std::cout << e0 << " -> r0 = "  << r0 <<   ",  t0 = " << t0 << "\n";
    auto [r1, t1] = to_polar(e1);
    std::cout << e1 << " -> r0 = "  << r1 <<  ",  t1 = " << t0 << "\n";
    we_t we0(e0);
    we_t we1(e1);
    auto [wr0, wt0] = to_polar(we0);
    std::cout << we0 << " -> r0 = "  << wr0 <<  ",  wt0 = " << wt0 << "\n";
    auto [wr1, wt1] = to_polar(we1);
    std::cout << we1 << " -> wr0 = "  << wr1 <<  ",  wt1 = " << wt0 << "\n";
  }
  {
    std::cout << "Complex:     "<< "\n";
    c_t c0(3, -4);
    c_t c1(1, 2);
    auto [r0, t0] = to_polar(c0);
    std::cout << c0 << " -> r0 = "  << r0 <<  ",  t0 = " << t0 << "\n";
    auto [r1, t1] = to_polar(c1);
    std::cout << c1 << " -> r0 = "  << r1 <<  ",  t1 = " << t0 << "\n";
    wc_t wc0(c0, kyosu::sqr(c0));
    wc_t wc1(c1, c0);
    auto [wr0, wt0] = to_polar(wc0);
    std::cout << wc0 << " -> r0 = "  << wr0 <<  ",  wt0 = " << wt0 << "\n";
    auto [wr1, wt1] = to_polar(wc1);
    std::cout << wc1 << " -> wr0 = "  << wr1 <<  ",  wt1 = " << wt0 << "\n";
  }
  {
    std::cout << "Quaternion:     "<< "\n";
    q_t q0(3, -4, 2, -1);
    auto [r, t, i] = to_polar(q0);
    std::cout << "q0= " << q0<< std::endl;
    std::cout << "r = " << r << std::endl;
    std::cout << "t = " << t << std::endl;
    std::cout << "i = " << i << std::endl;
    std::cout <<  "r*exp(i*t) = " << r*kyosu::exp(i*t) << std::endl;
    wq_t wq0(q0, q0*(1.0-q0));
    auto [wr, wt, wi] = to_polar(wq0);
    std::cout << "wq0= " << wq0<< std::endl;
    std::cout << "wr = " << wr << std::endl;
    std::cout << "wt = " << wt << std::endl;
    std::cout << "wi = " << wi << std::endl;
    std::cout <<  "wr*exp(wi*wt) = " << wr*kyosu::exp(wi*wt) << std::endl;
  }
  return 0;
}
