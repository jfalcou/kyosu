Mathematics of Cayley-Dickson Algebras  {#math_background}
======================================

# Construction

@ref biblio "Hamilton (1837)" defined the complex numbers without \f$\sqrt{-1}\f$, as the
ordered pairs of reals with the product \f$(a, b)(c, d) = (ac - bd, ad + bc)\f$. The same formula
applied to pairs of complex numbers gives a commutative algebra, and not the quaternions. Hamilton found the
quaternions in 1843, and Graves (1843) and Cayley (1845) the octonions. The doubling that
produces the quaternions from the complex numbers, and the octonions from the quaternions,
involves a conjugation, and is due to @ref biblio "Dickson (1919)".

Let \f$A\f$ be a real algebra with a unit and an involution \f$x \mapsto \overline{x}\f$, a linear
map with \f$\overline{\overline{x}} = x\f$ and \f$\overline{xy} = \overline{y}\,\overline{x}\f$. The
*Cayley-Dickson double* of \f$A\f$ is the algebra \f$A \times A\f$ with the product and the
involution

\f[ (a, b)\,(c, d) = \left(ac - \overline{d}b,\: da + b\overline{c}\right),
    \qquad \overline{(a,b)} = \left(\overline{a}, -b\right). \f]

From \f$A = \mathbb{R}\f$, with the identity as involution, the doubling gives in turn
\f$\mathbb{C}\f$, \f$\mathbb{H}\f$, \f$\mathbb{O}\f$, and an infinite sequence of algebras of
dimension \f$2^n\f$. The literature uses several forms of the doubling formula, and **KYOSU**
implements the one above.

The construction is the same at every step, with two consequences for the library:

- one function computes the product in every dimension,
- one scheme extends a real analytic function to every algebra of the sequence.

kyosu::sqrt is therefore one function, whether its argument is a `double`, a complex number, a
quaternion, or an element of dimension 32.

# Notation

## Elements

Let \f$\mathbb{K}\f$ be the Cayley-Dickson algebra of dimension \f$N\f$. Its standard basis
\f$e_0, \ldots, e_{N-1}\f$ follows the doubling: for \f$k < N/2\f$, \f$e_k\f$ is the pair
\f$(e_k, 0)\f$ and \f$e_{N/2+k}\f$ the pair \f$(0, e_k)\f$, built on the basis of the algebra of
dimension \f$N/2\f$. Then \f$e_0 = 1\f$ and \f$e_i^2 = -1\f$ for \f$i > 0\f$. An element of
\f$\mathbb{K}\f$ is written

\f[ z = z_0 + \sum_{i=1}^{N-1} z_i\,e_i. \f]

The components \f$z_i\f$ are IEEE `float` or `double` values, or, through EVE, SIMD registers of
them.

## Labels of the basis

A value prints each component followed by the label of its basis element:

| Dimension | Labels of \f$e_1, \ldots, e_{N-1}\f$ |
|:---------:|--------------------------------------|
| 2 | \f$i\f$ |
| 4 | \f$i, j, k\f$ |
| 8 | \f$i, j, k, l, il, jl, kl\f$ |
| 16 and more | the index: \f$z_0\f$ for the real part, then \f$z_1, \ldots, z_{N-1}\f$ |

In dimension 8, \f$l = e_4\f$, and each of the last three labels is the product it names:
\f$e_5 = il\f$, \f$e_6 = jl\f$, and \f$e_7 = kl\f$.

## Quantities

| Quantity | Definition | Function |
|----------|------------|----------|
| real part | \f$z_0\f$ | kyosu::real |
| pure part | \f$\underline{z} = \sum_{i=1}^{N-1} z_i\,e_i\f$ | kyosu::pure |
| modulus, or norm | \f$\vert z\vert = \sqrt{\sum_{i=0}^{N-1} z_i^2}\f$ | kyosu::abs |
| conjugate | \f$\overline{z} = z_0 - \underline{z}\f$ | kyosu::conj |
| inverse | \f$z^{-1} = \overline{z}/\vert z\vert^2\f$, for \f$z \neq 0\f$ | kyosu::rec |
| direction | \f$I_z = \mathrm{sign}(z_1)\,\underline{z}/\vert\underline{z}\vert\f$ | third element of kyosu::to_polar |
| argument | \f$\theta = \mathrm{sign}(z_1)\arccos(z_0/\vert z\vert)\f$, in \f$[-\pi, \pi]\f$ | kyosu::arg |

The direction and the argument are defined here for \f$z_1 \neq 0\f$. For a real \f$z\f$,
kyosu::arg returns \f$0\f$ or \f$\pi\f$, and kyosu::to_polar returns \f$0\f$ as the direction.

With \f$e^{\theta I_z}\f$ defined as \f$\cos\theta + I_z\sin\theta\f$, an element with
\f$z_1 \neq 0\f$ has the polar form

\f[ z = |z|\,e^{\theta I_z} = |z|\,(\cos\theta + I_z\sin\theta), \f]

since \f$I_z^2 = -1\f$. kyosu::to_polar returns \f$|z|\f$, \f$\theta\f$, and \f$I_z\f$ as a
`kumi::tuple`, and kyosu::from_polar builds \f$z\f$ back from them.

# Properties lost by the doubling

A division algebra is an algebra where \f$xb = a\f$ and \f$bx = a\f$ have exactly one solution
for every \f$a\f$ and every nonzero \f$b\f$. The doublings up to dimension 16 lose structural
properties in a fixed order. By
@ref biblio "Frobenius (1878)", the only finite-dimensional associative division algebras over
\f$\mathbb{R}\f$ are \f$\mathbb{R}\f$, \f$\mathbb{C}\f$, and \f$\mathbb{H}\f$, up to isomorphism.
By @ref biblio "Hurwitz (1898)", the only normed division algebras with a unit over
\f$\mathbb{R}\f$ are these three and \f$\mathbb{O}\f$, up to isomorphism, a normed algebra
having a positive definite quadratic form \f$N\f$ with \f$N(xy) = N(x)N(y)\f$. By @ref biblio "Bott and Milnor (1958)" and
@ref biblio "Kervaire (1958)", a finite-dimensional division algebra over \f$\mathbb{R}\f$,
associative or not, has dimension 1, 2, 4, or 8.

| Dimension | Algebra | Properties lost | Structure retained |
|:---------:|---------|-----------------|--------------------|
| 1  | \f$\mathbb{R}\f$ |  | commutative ordered field |
| 2  | \f$\mathbb{C}\f$ | order | commutative field |
| 4  | \f$\mathbb{H}\f$ | commutativity | division ring |
| 8  | \f$\mathbb{O}\f$ | associativity | alternative division algebra |
| 16 | \f$\mathbb{S}\f$, the sedenions | alternativity, division, multiplicative norm | flexible power-associative algebra |
| \f$2^n,\ n>4\f$ |  |  | flexible power-associative algebra |

## Dimension 2: order

No total order on \f$\mathbb{C}\f$ is compatible with its field operations: with such an order,
\f$i > 0\f$ would give \f$i^2 = -1 > 0\f$, and \f$i < 0\f$ would give \f$(-i)^2 = -1 > 0\f$.
**KYOSU** therefore defines the equality and the componentwise predicates on its values, and no
relational operator.

A real analytic function evaluated at a real argument may also leave the reals:
\f$\sqrt{-1}\f$ is the element \f$i\f$. A real argument outside the real domain of a function
gives a complex result by default, and the option kyosu::real_only selects the real function,
which returns NaN.

## Dimension 4: commutativity

In \f$\mathbb{H}\f$, \f$ij = k\f$ and \f$ji = -k\f$. The equations \f$xb = a\f$ and \f$bx = a\f$
then have distinct solutions in general, \f$ab^{-1}\f$ and \f$b^{-1}a\f$, and each defines a
division.

## Dimension 8: associativity

In \f$\mathbb{O}\f$, the products \f$(ab)c\f$ and \f$a(bc)\f$ differ in general. On the standard
basis,

\f[ (e_1e_2)e_4 = e_7, \qquad e_1(e_2e_4) = -e_7. \f]

The associator \f$[a,b,c] = (ab)c - a(bc)\f$, computed by kyosu::associator, measures the
difference. It is \f$2e_7\f$ on the triple above, and zero on any three quaternions.

The octonions are *alternative*: the associator is an alternating function of its three
arguments. By Artin's theorem, the subalgebra generated by any two elements is then associative.

## Dimension 16: alternativity, division, and the norm

The sedenions have zero divisors, nonzero elements \f$x\f$ with \f$xy = 0\f$ for some nonzero
\f$y\f$. On the standard basis,

\f[ (e_3 + e_{10})(e_6 - e_{15}) = 0, \f]

with both factors of norm \f$\sqrt2\f$. The norm is no longer multiplicative, and the sedenions
are no longer alternative. A nonzero element \f$x\f$ keeps the two-sided inverse
\f$\overline{x}/|x|^2\f$, which is its only inverse when \f$x\f$ is not a zero divisor. The
quotients \f$ab^{-1}\f$ and \f$b^{-1}a\f$ are then defined and finite for any nonzero \f$b\f$,
and in general they no longer solve \f$xb = a\f$ and \f$bx = a\f$:

- when \f$b\f$ is not a zero divisor, each equation has exactly one solution, which in general
  differs from \f$ab^{-1}\f$ and \f$b^{-1}a\f$,
- when \f$b\f$ is a zero divisor, each equation has either no solution or infinitely many.

Every algebra of the sequence is *power-associative*: the subalgebra generated by one element is
associative, so \f$z^mz^n = z^{m+n}\f$ holds in every dimension. Every algebra of the sequence is
also *flexible*, \f$(ab)a = a(ba)\f$.

# Expression in the API

| Mathematical fact | API |
|-------------------|-----|
| No order compatible with the operations beyond \f$\mathbb{R}\f$ | No relational operator. kyosu::is_equal and the componentwise predicates. |
| Real domains not preserved | A complex result by default. `f[kyosu::real_only]` calls the EVE function, which returns NaN. |
| Two divisions | `a / b` is \f$ab^{-1}\f$ and `kyosu::ldiv(b, a)` is \f$b^{-1}a\f$. Up to the octonions, they solve \f$xb = a\f$ and \f$bx = a\f$. |
| Nonzero associator | An expression is evaluated with its parentheses as written. kyosu::associator returns \f$[a,b,c]\f$. |
| Each algebra embedded in the next | An operation on mixed dimensions returns the larger one, the missing components being zero. |

The sum of a complex number and a quaternion, for instance, is a quaternion, and no conversion
appears in the source.

# Extension of real analytic functions

A real analytic function is a function from an open subset of \f$\mathbb{R}\f$ to
\f$\mathbb{R}\f$ that is the sum of a convergent power series in a neighborhood of each point. It
extends to a holomorphic function \f$f\f$ on a neighborhood of its domain in \f$\mathbb{C}\f$,
symmetric about the real axis, with \f$f(\overline{w}) = \overline{f(w)}\f$. A function with a
branch cut, such as kyosu::log or kyosu::sqrt, takes the principal branch, holomorphic on
\f$\mathbb{C} \setminus (-\infty, 0]\f$.

Every element \f$c \in \mathbb{K}\f$ satisfies

\f[ c^2 - 2c_0\,c + |c|^2 = 0, \f]

so the real span of \f$1\f$ and \f$c\f$ is a subalgebra. When \f$\underline{c} \neq 0\f$, let
\f$u_c = \underline{c}/|\underline{c}|\f$. Since \f$u_c^2 = -1\f$, the map
\f$x + iy \mapsto x + y\,u_c\f$ is an isomorphism from \f$\mathbb{C}\f$ onto that subalgebra,
and it sends \f$c_0 + i|\underline{c}|\f$ to \f$c\f$. The extension of \f$f\f$ at \f$c\f$ is the
image of \f$f(c_0 + i|\underline{c}|)\f$ by this isomorphism:

 1. evaluate \f$v = f\!\left(c_0 + i\,|\underline{c}|\right)\f$ in \f$\mathbb{C}\f$,
 2. return \f$\Re(v) + u_c\,\Im(v)\f$.

The direction \f$-u_c\f$ sends \f$c_0 - i|\underline{c}|\f$ to \f$c\f$, and since
\f$f(\overline{w}) = \overline{f(w)}\f$, it gives the same result. For kyosu::log, the scheme
gives \f$\log c = \ln|c| + u_c\arccos(c_0/|c|)\f$, an angle in \f$[0, \pi]\f$ along \f$u_c\f$,
where kyosu::arg carries the sign of \f$c_1\f$. When
\f$\underline{c} = 0\f$, \f$c\f$ is real, and the scheme applies where \f$f(c_0)\f$ is real.

The functions that are not real analytic, such as kyosu::abs, kyosu::arg, and kyosu::conj, are
outside this scheme and have a definition of their own.
