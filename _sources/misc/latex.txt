========================================
LaTeX 教學
========================================


.. contents:: 目錄


基本介紹
========================================

安裝
========================================

基本語法
========================================

範例一 — 非中文內容）
------------------------------

撰寫：

.. code-block:: tex

    \documentclass{article}
    \begin{document}

    % 以下撰寫內容

    Hello World

    % 以上撰寫內容

    \end{document}


轉成 PDF：

.. code-block:: sh

    $ pdflatex hello.tex    # 產生 hello.pdf


轉成圖片：

.. code-block:: sh

    # PNG
    $ latex2png hello.tex    # 產生 hello.png

    # TODO: SVG


範例二 — 稍微完整一點的架構
------------------------------

撰寫：

.. code-block:: tex

    \documentclass{article}

    % 設定區域

    \title{文章標題}
    \author{作者}

    \begin{document}

    % 以下撰寫內容

    Hello World

    % 以上撰寫內容

    \end{document}


範例三 — 數學式子
------------------------------

數學模式分成兩種，
分別為 inline 和 display，
inline 用於插在文字中，
用 ``$`` 包夾，
display 則是把數學獨立置中，
包夾的方式就比較多，
例如 ``$$ ... $$`` 、 ``\[ ... \]`` 、 ``\begin{equation} ... \end{equation}`` 。


範例：

.. code-block:: tex

    The formula $f(x)=x^3-2x+6$ is important.

    ---

    The formula
    $$
    f(x)=x^3-2x+6
    $$
    is important.


完整範例：

.. code-block:: tex

    \documentclass{article}

    % 設定區域

    \title{文章標題}
    \author{作者}

    \begin{document}

    % 以下撰寫內容

    The formula $f(x)=x^3-2x+6$ is important.

    ---

    The formula
    $$
    f(x)=x^3-2x+6
    $$
    is important.

    % 以上撰寫內容

    \end{document}


.. image:: /images/latex/math-example0.png


範例四 — 中文支援
------------------------------

要支援中文要設定兩個東西，
一個是使用 xeCJK 套件，
另一個是選中文字型。

需要加入的內容：

.. code-block:: tex

    \usepackage{xeCJK}
    \setCJKmainfont{Noto Sans CJK TC}


字型可以選擇系統上的中文字型，
尋找系統上的中文字型來用：

.. code-block:: sh

    $ fc-list | rg CJK


完整範例：

.. code-block:: tex

    \documentclass{article}

    % 設定區域

    \usepackage{xeCJK}
    \setCJKmainfont{Noto Sans CJK TC}

    \title{文章標題}
    \author{作者}

    \begin{document}

    % 以下撰寫內容

    我們的 \LaTeX 終於可以打中文啦

    % 以上撰寫內容

    \end{document}


轉成 PDF：

.. code-block:: sh

    $ xelatex chinese.tex


範例五 — 不同中文字體用不同字型
-------------------------------

通常我們會對不同的字體選用不同的字型，
而要指定不同的字型也很簡單，
需要加入的內容：

.. code-block:: tex

    % 不過目前 Noto Sans 沒有中文的斜體 :(
    \setCJKmainfont[
        BoldFont={Noto Sans CJK TC Bold},
        ItalicFont={Noto Sans CJK TC Medium}]
        {Noto Sans CJK TC}

另外這是可以使用的設定：

* \setCJKmainfont
* \setCJKsansfont
* \setCJKmonofont


完整範例：

.. code-block:: tex

    \documentclass{article}

    % 設定區域

    \usepackage{xeCJK}
    \setCJKmainfont[
        BoldFont={Noto Sans CJK TC Bold},
        ItalicFont={Noto Sans CJK TC Medium}]
        {Noto Sans CJK TC}

    \title{文章標題}
    \author{作者}

    \begin{document}

    % 以下撰寫內容

    我們的 \LaTeX 終於可以打中文啦

    % {\bf{CONTENT}}
    % {\bf CONTENT}
    % \textbf{CONTENT}
    這 {\it 真的} 很 {\bf 重要}

    % 以上撰寫內容

    \end{document}


轉成 PDF：

.. code-block:: sh

    $ xelatex chinese.tex


範例六 — 英文字型
-------------------------------

範例七 — AMS-LaTeX
-------------------------------

AMS-LaTeX 是由美國數學學會（American Mathematical Society）開發的套件，
提供了許多數學相關的支援。

其中包含：

* amssymb：提供原本 LaTeX 沒有的符號
* amsamth：提供 align 等方便的環境
* amsthm：提供比較好使用定理的環境


使用：

.. code-block:: tex

    \usepackage{amssymb, ammath, amsthm}


AMS-LaTeX 也提供一種 Document Class 可以使用，
使用時會自動 amsmath、amsthm 和部份 amssymb，
如果要全套 amssymb 還是需要自己讀入，
使用範例：

.. code-block:: tex

    \documentclass{amsstart}


定義定理：

.. code-block:: tex

    % 定義定理環境 thm
    % 顯示時標示為 Theorem
    \newtheorem{thm}{Theorem}

    \begin{thm}
    The statements of the theorem.
    \end{thm}

還可以加上 ``[section]`` 來編號，
範例：

.. code-block:: tex

    \newtheorem{thm}{Theorem}[section]


完整範例：

.. code-block:: tex

    \documentclass{article}

    % 設定區域

    \usepackage{amssymb, amsmath, amsthm}

    \title{文章標題}
    \author{作者}

    \newtheorem{thm}{My Theorem}[section]

    \begin{document}

    % 以下撰寫內容

    \AmS-\LaTeX


    \begin{thm}
        \begin{align}
            y &= (x+1)^2 \\
              &= x^2+2x+1
        \end{align}

        The statements of the theorems.
    \end{thm}


    % 以上撰寫內容

    \end{document}


.. image:: /images/latex/math-example1.png



服務
========================================

* `Overleaf <https://www.overleaf.com/>`_
* `Papeeria <https://papeeria.com/>`_



參考
========================================

* `LaTeX 快速入門 (Quick LaTeX) <https://github.com/yenlung/quicklatex/>`_
* `由 TeX/LaTeX 製作中文 PDF 檔 <http://www.study-area.org/tips/latex/chpdf.html>`_
