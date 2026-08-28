<img src="https://github.com/jfalcou/kyosu/raw/main/doc/logo.png" alt="KYOSU logo" data-canonical-src="https://github.com/jfalcou/kyosu/main/doc/logo.png" align="left"  width="15%" height="15%" />

# Kyosu
## Complex Without Complexes

Efficient and SIMD-aware computation for complex numbers, quaternions and octonions.

Kyosu proposes a unified treatment of Cayley-Dickson algebras over the real numbers, for
numerical computation.

Real numbers are the IEEE `float` and `double` types and, as Kyosu builds on the EVE library,
they can be SIMD registers just as well.

<br clear="left"/>

## Example

The same function over three algebras of growing dimension, mixed freely, then vectorized —
without the maths changing a line.

```cpp
#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::complex_t;
  using kyosu::octonion_t;
  using kyosu::quaternion_t;

  // The same function, over three algebras of growing dimension.
  auto c = complex_t<double>(1., 2.);
  auto q = quaternion_t<double>(1., 2., 3., 4.);
  auto o = octonion_t<double>(1., 2., 3., 4., 5., 6., 7., 8.);

  std::cout << "complex:    " << c << " -> exp " << kyosu::exp(c) << "\n";
  std::cout << "quaternion: " << q << " -> exp " << kyosu::exp(q) << "\n";
  std::cout << "octonion:   " << o << " -> exp " << kyosu::exp(o) << "\n";

  // Dimensions mix freely, the widest one wins.
  std::cout << "\nc + q     = " << c + q << "\n";
  std::cout << "q * o     = " << q * o << "\n";

  // And every one of them vectorizes, without changing a line of the maths.
  using wq_t = eve::wide<quaternion_t<double>, eve::fixed<2>>;
  wq_t w(q);
  std::cout << "\nSIMD quaternion: " << w << "\n";
  std::cout << "            exp: " << kyosu::exp(w) << "\n";

  return 0;
}
```

which prints:

```text
complex:    1 + 2i  -> exp -1.1312 + 2.47173i
quaternion: 1 + 2i + 3j + 4k  -> exp 1.69392 - 0.78956i - 1.18434j - 1.57912k
octonion:   1 + 2i + 3j + 4k + 5l + 6li + 7lj + 8lk  -> exp -0.300137 + 0.379239i + 0.568858j + 0.758478k + 0.948097l + 1.13772li + 1.32734lj + 1.51696lk

c + q     = 2 + 4i + 3j + 4k
q * o     = -28 + 4i + 6j + 8k - 60l + 20li + 14lj + 32lk

SIMD quaternion: (1 + 2i + 3j + 4k , 1 + 2i + 3j + 4k )
            exp: (1.69392 - 0.78956i - 1.18434j - 1.57912k , 1.69392 - 0.78956i - 1.18434j - 1.57912k )
```

The full documentation lives at [jfalcou.github.io/kyosu](https://jfalcou.github.io/kyosu).
