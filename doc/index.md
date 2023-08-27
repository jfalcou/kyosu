Kyosu
=====

**KYOSU** is an unified implementation of the complex, quaternions, octonions and more generally all
Cayley-Dickson algebras in an SIMD aware context provided by **EVE**

The Cayley-@Dickson construction defines a new algebra as a Cartesian product of an algebra with itself,
 with multiplication defined in a specific way (different from the componentwise multiplication)
 and an involution known as conjugation.

We currently only implement the Cayley-Dickson algebras bsed on the IEEE float and double
 representations of real numbers.

Cayley-Dickson algebras
=======================

These are algebras over the real numbers with an involution named conjugation.
The product of an element by its conjugate is 'real' and and its positive square root is a norm on the
vector space defined by the algebra.

Starting from the real numbers (supported by type T float or double) we define:

  - complex numbers (dimension 2)
  - quaternion      (dimension 4)
  - octonion        (dimension 8)

  - and more generally for any integral power of 2: N, the cayley_dickson algebra of dimension N

Higher are the dimension weider are these algebras

   - real numbers is a commutative ordered field
   - complex      is a commutative field with no cmpatible order
   - quaternion   is a non-commutative field
   - octonion     is a non associative (but alternative) division algebra

Greater dimesion are not even alternative but keep power-asociativity.


What does this Implementation provides
======================================

All operators and functions implemented can receive a mix of scalar or simd of caylet-dickson and reals of various
dimensionnality and are defined in the namespace kyosu.

Of course the algebra operation +, -, * and / are provided, but as \ is not an usable **C++**
character as an operator, the left division a\b is provided as the call ldiv(a,b).

Constructors
------------

TODO LIST

Extractors
----------

TODO LIST

Arithmetic
----------

Most **EVE** arithmetic functions are provided:

TODO LIST

Mathematic
----------

Most elementary analytic  mathematical functions are provided

TODO LIST
