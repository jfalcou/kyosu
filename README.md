<img src="https://raw.githubusercontent.com/jfalcou/kyosu/refs/heads/main/doc/logo.svg" alt="KYOSU logo: the Fano plane, three of its lines drawn dark to form a K" data-canonical-src="https://jfalcou.github.io/kyosu/doc/logo.svg" align="left" width="15%" height="15%" />

# Kyosu
## Complex Without Complexes

Efficient and SIMD-aware computation for complex numbers, quaternions and octonions.

Kyosu proposes a unified treatment of Cayley-Dickson algebras over the real numbers, for
numerical computation.

Real numbers are the IEEE `float` and `double` types and, as Kyosu builds on the EVE library,
they can be SIMD registers just as well.

<br clear="left"/>

## Example

One name, whatever the dimension of the argument:

```cpp
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::sqr;

  // One name, whatever the dimension of the argument.
  std::cout << "complex:    " << sqr(kyosu::complex_t<double>(1., 2.))            << "\n";
  std::cout << "quaternion: " << sqr(kyosu::quaternion_t<double>(1., 2., 3., 4.)) << "\n";
  std::cout << "octonion:   " << sqr(kyosu::octonion_t<double>(1., 2., 3., 4., 5., 6., 7., 8.)) << "\n";
}
```

```text
complex:    -3 + 4i
quaternion: -28 + 4i + 6j + 8k
octonion:   -202 + 4i + 6j + 8k + 10l + 12li + 14lj + 16lk
```

The algebra is the real one — past the complex numbers it stops being commutative:

```cpp
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using q_t = kyosu::quaternion_t<double>;
  auto c = kyosu::complex_t<double>(1., 2.);
  auto q = q_t(1., 2., 3., 4.);
  auto o = kyosu::octonion_t<double>(1., 2., 3., 4., 5., 6., 7., 8.);

  // Dimensions mix freely: the result takes the largest one.
  std::cout << "c + q = " << c + q << "\n";
  std::cout << "q * o = " << q * o << "\n";

  // The constants behave as the algebra says they should, and it is not commutative.
  auto i = kyosu::i(kyosu::as<q_t>());
  auto j = kyosu::j(kyosu::as<q_t>());
  std::cout << "i * j = " << i * j << "\n";
  std::cout << "j * i = " << j * i << "\n";

  // Which is why a left-division of its own is needed.
  std::cout << "q / c      = " << q / c            << "\n";
  std::cout << "ldiv(c, q) = " << kyosu::ldiv(c, q) << "\n";
}
```

```text
c + q = 2 + 4i + 3j + 4k
q * o = -28 + 4i + 6j + 8k - 60l + 20li + 14lj + 32lk
i * j = 0 + 0i + 0j + 1k
j * i = 0 + 0i + 0j - 1k
q / c      = 1 + 0i - 1j + 2k
ldiv(c, q) = 1 + 0i + 2.2j - 0.4k
```

The full documentation lives at [jfalcou.github.io/kyosu](https://jfalcou.github.io/kyosu).
