LaTeX
===============================================================================

.. highlight:: latex

:math:`\LaTeX`


Command
----------------------------------------------------------------------

::

    \command[optional param]{param}

- command starts with ``\``

- whitespace is ignored after commands.

- force whitespace after commands

.. math::

    \TeX and{} \LaTeX.

Comments
----------------------------------------------------------------------

::

    Hello % here is commen
    , World

e.g.:

.. math::

    Hello % comment
    , World


File Structure
----------------------------------------------------------------------

``.tex``
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

::

    \documentclass{...}  % LaTeX2e doc required This
    \usepackage{...}     % setup

    \title{title}
    \author{Iblis Lin}

    \begin{document}

    content

    \end{document}


- ``.sty``:
  :math:`\LaTeX` package.


Line/page breaking
----------------------------------------------------------------------

:paragraph: a set of words to convey the same, coherent idea.
            Placing blank line between two paragraph.

:line break:
    - just use ``\\`` or ``\newline`` in same paragraph.

    - ``\\*``: *prohibit* page breaking after this new line

    - ``\pagebreak``


Quoting
----------------------------------------------------------------------

::

    `` for open
    '' for close

e.g::

    ``quoting some text''


Tilde
----------------------------------------------------------------------

::

    \~{}

    http://foo/\~{}bar


Accents
----------------------------------------------------------------------

::

    H\^otel, na\"\i ve, \’el\‘eve,\\
    sm\o rrebr\o d, !‘Se\~norita!,\\
    Sch\"onbrunner Schlo\ss{}
    Stra\ss e


TikZ
----------------------------------------------------------------------

Preamble::

    \usepackage{tikz}

::

    \begin{tikzpicture}
        \draw (0, 0) to (2, 2) -- (4, 0) -- cycle;
        \draw (2, 2) -- (1, 0);
    \end{tikzpicture}

Plot function::

    \draw[green, ultra thick, domain=0:0.5] plot (\x, {0.025+\x+\x*\x});

Plot label::

    \node [above left] at (1, 1) {$x$};
