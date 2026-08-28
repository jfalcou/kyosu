Mathematics of Cayley-Dickson Algebras  {#math_background}
======================================

# General Principles
KYOSU is fundamentally built upon the Cayley-Dickson construction scheme[cite: 1]. This mathematical framework defines a new algebra as a Cartesian product of a base algebra with itself, featuring a unique multiplication definition and an involution known as conjugation[cite: 1].

## The Construction
The product of an element by its conjugate is exclusively real[cite: 1]. The positive square root of this product acts as a norm on the vector space defined by the algebra[cite: 1]. Currently, KYOSU limits this construction strictly to IEEE float and double representations of real numbers[cite: 1].

### Algebra Dimensions
  Starting from real numbers, the construction continuously doubles the dimension to generate[cite: 1]:
  + [**Complex Numbers**](https://en.wikipedia.org/wiki/Complex_number).
  + [**Quaternions**](https://en.wikipedia.org/wiki/Quaternion).
  + [**Octonions**](https://en.wikipedia.org/wiki/Octonion).
  + [**General Algebras**](https://en.wikipedia.org/wiki/Cayley%E2%80%93Dickson_construction).

Let \f$\mathbb{K}\f$ be a Cayley-Dickson algebra of dimension \f$N\f$. Its elements are expressed mathematically as:

$$z = \sum_{i=0}^{N-1} z_i\;e_i$$

where \f$e_0=1\f$, and the bases \f$(e_i)_{i>1}\f$ satisfy \f$e_i^2 = -1\f$. Up to octonions, the bases \f$(e_i)_{i<8}\f$ carry standard
non-indicial names: \f$i, j, k, l, li, lj, lk\f$. Because \f$e_0=1\f$, it is typically omitted from the notation.

## Mathematical Notations
Throughout the KYOSU API, the following notations apply[cite: 1]:
  + \f$|z|\f$: The absolute value (or modulus) of \f$z\f$, defined as \f$\sqrt{\sum_{i=0}^{N-1} |z_i|^2}\f$[cite: 1].
  + \f$z_0\f$: The real part of \f$z\f$[cite: 1].
  + \f$\underline{z}\f$: The pure part of \f$z\f$, defined as \f$\sum_{i=1}^{N-1} z_i\;e_i\f$[cite: 1].
  + \f$I_z\f$: Denotes \f$\pm\underline{z}/|\underline{z}|\f$, where the \f$\pm\f$ matches the sign of \f$z_1\f$[cite: 1].
  + **Polar Form:** The polar form is \f$\rho e^{\theta\;I_z} = \rho(\cos\theta + I_z\sin\theta)\f$, where \f$\rho\f$ is the norm and \f$\theta\f$ is the argument[cite: 1]. Because \f$I_z^2 = -1\f$, the similarity to standard complex numbers is mathematically preserved[cite: 1].

## Structural Properties
 As dimensionality increases, mathematical structural properties are progressively lost[cite: 1]:
 * **Real Numbers:** A commutative ordered field[cite: 1].
 * **Complex Numbers:** A commutative field lacking a multiplication-compatible order[cite: 1].
 * **Quaternions:** A non-commutative field[cite: 1].
 * **Octonions:** A non-associative, but alternative, division algebra[cite: 1].
 * **Dimension > 8:** These algebras are not alternative but retain power-associativity, which is sufficient to define most elementary functions[cite: 1].

## Function Extension Scheme
 KYOSU extends real analytic functions to general Cayley-Dickson types using the polar form[cite: 1]. For a function \f$f(z)\f$ defined on complex input, the extension mechanism for an arbitrary Cayley-Dickson entry \f$c\f$ evaluates as follows[cite: 1]:
 1. Compute \f$v = f(\Re(c) + i|\underline{c}|)\f$, where \f$\Re(c)\f$ is the real part and \f$\underline{c}\f$ is the pure part[cite: 1].
 2. The final result is \f$\Re(v) + I_c\Im(v)\f$, where \f$\Im(v)\f$ is the imaginary part of the complex \f$v\f$[cite: 1].
