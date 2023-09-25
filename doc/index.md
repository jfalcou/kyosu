Kyosu
=====

**KYOSU** is an unified implementation of the complex, quaternions, octonions and more generally all
\f$\mathbb{R}\f$-Cayley-Dickson algebras in an SIMD aware context provided by **EVE**

The Cayley-Dickson construction scheme defines a new algebra as a Cartesian product of an algebra with itself,
 with multiplication defined in a specific way (different from the componentwise multiplication)
 and an involution known as conjugation.

We currently only implement the Cayley-Dickson algebras based on the IEEE float and double
 representations of real numbers.

Kyosu proper usable objects are all in the namespace `kyosu`.

Cayley-Dickson algebras
=======================

These are algebras over the real numbers with an involution named conjugation.
The product of an element by its conjugate is 'real' and its positive square root is a norm on the
vector space defined by the algebra.

Starting from the real numbers (supported by type T float or double) we define:

  - complex numbers (dimension 2)
  - quaternion      (dimension 4)
  - octonion        (dimension 8)

  - and more generally for any integral power of 2: N, the cayley_dickson algebra of dimension N

Let \f$\mathbb{K}\f$ be a Cayley-Dickson algebra of dimension N its elements can be mathematically written

\f$\displaystyle z=\sum_0^{N-1} z_i\;e_i\f$

where \f$e_0=1\f$ and \f$(e_i)_{i>1}\f$ satisfy \f$e_i^2 = -1\f$ and a proper multiplication table relating them.

@note Up to octonions these \f$e_i\f$ have (non indicial) standard names, namely : 1, i, j, k, l, li, lj, lk.

In the documentation we will sometimes use the following notations:

 * \f$|z|\f$ is the absolute value (or modulus) of \f$z\f$, i.e. \f$\sqrt{\sum_0^{N-1} |z_i|^2}\f$.
 * \f$z0 \f$ is the real part of \f$z\f$.
 * \f$\underline{z}\f$ is the pure part of \f$z\f$ i.e. \f$\sum_1^{N-1} z_i\;e_i\f$.
 * If \f$I_z\f$ denotes \f$\underline{z}/|z|\f$ the polar form of \f$z\f$ is \f$\rho e^{\theta\;I_z} = \rho(\cos\theta + I_z\sin\theta)\f$
   \f$ \rho\f$ being the norm of \f$z\f$ and \f$\theta\f$ its argument. (Note the similariraty with complex numbers:
   it is easy to see that \f$I_z^2=-1\f$

These datas with different dimensions can be freely mixed with the obvious semantic that if N <M an element of
cayley_dickson<N> will be considered as having its components from N to M-1, null as an element of cayley_dickson<M>


Higher are the dimensions weirder are these algebras

   - real numbers is a commutative ordered field
   - complex      is a commutative field with no multiplication-compatible order
   - quaternion   is a non-commutative field
   - octonion     is a non associative (but alternative) division algebra

Greater dimensions are not even alternative but keep power-associativity which allows
to define most elementary functions.


What does this implementation provide
======================================

All operators and functions implemented can receive a mix of scalar or simd of cayley-dickson and reals of various
dimensionnality and are defined in the namespace kyosu.

Of course the algebra operation +, -, * and / are provided, but as \ is not an usable **C++**
character as an operator, the left division a\b is provided as the call ldiv(a,b).

Constructors
------------

complex and  quaternion can be constructed using callables facilities `complex` and `quaternion`.

complex can also be constructed from their polar representation
quaternion from various parametrizations of \f$\mathbb{R}^4\f$ or from \f$\mathbb{R}^3\f$ rotations:

  * angle and axis
  * cylindrical
  * cylindricospherical
  * euler
  * multipolar
  * rotation_matrix
  * semipolar
  * spherical

TODO cayley_dickson<N>

Functions
---------

Most **KYOSU** callables are usable with all cayley_dickson types. The exception being mainly special
 complex functions and rotation related quaternion usage.

@warning: **EVE** callables that correspond to mathematical functions that
          are only defined on a proper part of the real axis as, for example, `acos` DOES NOT ever provide the same result
          if called in **EVE** or **KYOSU** context.

          eve::acos(2.0) wil returns a NaN value, but kyosu::acos(2.0) will return the pure imaginary
          complex number \f$i\;\log(2+\sqrt{3})\f$

          All these kinds of functions called with a floating value in the kyosu namespace will return a complex value.

  * callables usable with all cayley_dickson types

    Most **EVE** arithmetic functions are provided.

  * callables usable with complex only

  * callables usable with quaternion (and complex) only

Most **EVE** arithmetic functions are provided.
