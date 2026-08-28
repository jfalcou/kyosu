Mathematics of Cayley-Dickson Algebras  {#math_background}
======================================

# General Principles
KYOSU is fundamentally built upon the Cayley-Dickson construction scheme. This mathematical framework defines a new algebra as a Cartesian product of a base algebra with itself, featuring a unique multiplication definition and an involution known as conjugation.

## The Construction
The product of an element by its conjugate is exclusively real. The positive square root of this product acts as a norm on the vector space defined by the algebra. Currently, KYOSU limits this construction strictly to IEEE float and double representations of real numbers.

### Algebra Dimensions
  Starting from real numbers, the construction continuously doubles the dimension to generate:
  + [**Complex Numbers**](https://en.wikipedia.org/wiki/Complex_number).
  + [**Quaternions**](https://en.wikipedia.org/wiki/Quaternion).
  + [**Octonions**](https://en.wikipedia.org/wiki/Octonion).
  + [**General Algebras**](https://en.wikipedia.org/wiki/Cayley%E2%80%93Dickson_construction).

Let \f$\mathbb{K}\f$ be a Cayley-Dickson algebra of dimension \f$N\f$. Its elements are expressed mathematically as:

\f[ z = \sum_{i=0}^{N-1} z_i\;e_i \f]

where \f$e_0=1\f$, and the bases \f$(e_i)_{i>1}\f$ satisfy \f$e_i^2 = -1\f$. Up to octonions, the bases \f$(e_i)_{i<8}\f$ carry standard
non-indicial names: \f$i, j, k, l, li, lj, lk\f$. Because \f$e_0=1\f$, it is typically omitted from the notation.

## Mathematical Notations
Throughout the KYOSU API, the following notations apply:
  + \f$|z|\f$: The absolute value (or modulus) of \f$z\f$, defined as \f$\sqrt{\sum_{i=0}^{N-1} |z_i|^2}\f$.
  + \f$z_0\f$: The real part of \f$z\f$.
  + \f$\underline{z}\f$: The pure part of \f$z\f$, defined as \f$\sum_{i=1}^{N-1} z_i\;e_i\f$.
  + \f$I_z\f$: Denotes \f$\pm\underline{z}/|\underline{z}|\f$, where the \f$\pm\f$ matches the sign of \f$z_1\f$.
  + **Polar Form:** The polar form is \f$\rho e^{\theta\;I_z} = \rho(\cos\theta + I_z\sin\theta)\f$, where \f$\rho\f$ is the norm and \f$\theta\f$ is the argument. Because \f$I_z^2 = -1\f$, the similarity to standard complex numbers is mathematically preserved.

## Structural Properties
 As dimensionality increases, mathematical structural properties are progressively lost:
 * **Real Numbers:** A commutative ordered field.
 * **Complex Numbers:** A commutative field lacking a multiplication-compatible order.
 * **Quaternions:** A non-commutative field.
 * **Octonions:** A non-associative, but alternative, division algebra.
 * **Dimension > 8:** These algebras are not alternative but retain power-associativity, which is sufficient to define most elementary functions.

## Function Extension Scheme
 KYOSU extends real analytic functions to general Cayley-Dickson types using the polar form. For a function \f$f(z)\f$ defined on complex input, the extension mechanism for an arbitrary Cayley-Dickson entry \f$c\f$ evaluates as follows:
 1. Compute \f$v = f(\Re(c) + i|\underline{c}|)\f$, where \f$\Re(c)\f$ is the real part and \f$\underline{c}\f$ is the pure part.
 2. The final result is \f$\Re(v) + I_c\Im(v)\f$, where \f$\Im(v)\f$ is the imaginary part of the complex \f$v\f$.
