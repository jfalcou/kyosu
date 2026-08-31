Bibliography {#biblio}
============

The works the rest of the documentation leans on, whether or not it names them explicitly.

A [**ready to use Bibtex file can be downloaded here**](kyosu.bibtex).

# The construction and its limits

  + L. E. Dickson, *On Quaternions and Their Generalization and the History of the Eight Square
    Theorem*, Annals of Mathematics **20** (3), 1919, pp. 155–171.
    [DOI](https://doi.org/10.2307/1967865) — [free scan](https://archive.org/details/jstor-1967865).
    The doubling procedure in the form used throughout @ref math_background.

  + F. G. Frobenius, *Ueber lineare Substitutionen und bilineare Formen*, Journal für die reine und
    angewandte Mathematik **84**, 1878, pp. 1–63.
    [DOI](https://doi.org/10.1515/crelle-1878-18788403) — [free scan](https://eudml.org/doc/148343).
    The only finite-dimensional associative division algebras over the reals are
    \f$\mathbb{R}\f$, \f$\mathbb{C}\f$ and \f$\mathbb{H}\f$.

  + A. Hurwitz, *Über die Composition der quadratischen Formen von beliebig vielen Variabeln*,
    Nachrichten von der Gesellschaft der Wissenschaften zu Göttingen, 1898, pp. 309–316.
    [Free scan](https://eudml.org/doc/58420).
    The only normed division algebras over the reals are those three together with
    \f$\mathbb{O}\f$ — which is why division fails at dimension 16.

  + R. D. Schafer, *An Introduction to Nonassociative Algebras*, Academic Press, 1966; reprinted by
    Dover, 1995.
    [Free full text](https://www.gutenberg.org/files/25156/25156-pdf.pdf).
    Alternativity, power-associativity and Artin's theorem.

# The algebras themselves

  + J. C. Baez, *The Octonions*, Bulletin of the American Mathematical Society **39** (2), 2002,
    pp. 145–205.
    [DOI](https://doi.org/10.1090/S0273-0979-01-00934-X) —
    [free PDF](https://www.ams.org/journals/bull/2002-39-02/S0273-0979-01-00934-X/S0273-0979-01-00934-X.pdf) —
    [arXiv](https://arxiv.org/abs/math/0105155).
    The standard modern survey, and the most approachable entry point to the subject.

  + J. H. Conway and D. A. Smith, *On Quaternions and Octonions: Their Geometry, Arithmetic, and
    Symmetry*, A K Peters, 2003. ISBN 978-1-56881-134-5.
    [DOI](https://doi.org/10.1201/9781439864180).

# Rotations

  + K. Shoemake, *Animating Rotation with Quaternion Curves*, SIGGRAPH '85, pp. 245–254.
    [DOI](https://doi.org/10.1145/325334.325242).
    The origin of spherical linear interpolation, implemented as kyosu::slerp.
