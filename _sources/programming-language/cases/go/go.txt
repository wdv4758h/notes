========================================
Go
========================================

官方的 Go compiler 用了很多 escape analysis，
所以有些 heap allocation 會被轉而長在 stack 上。

Go 的 GC 在 1.5 後又會修正一些 latency 的問題，
待之後研究。


* `Go 1.7 <https://blog.golang.org/go1.7>`_
    - SSA (Static single assignment form)
    - Bounds-checking elimination
    - CSE (Common subexpression elimination)
    - `Looking at your program’s structure in Go 1.7 <https://pauladamsmith.com/blog/2016/08/go-1.7-ssa.html>`_


觀察 SSA 的改變
========================================

測試程式：

.. code-block:: go

    package main

    func main() {
        x := 5

        if 1 < 0 {
            x = -42
        }

        println(x)
    }


編譯並輸出各階段的 SSA ：

.. code-block:: sh

    env GOSSAFUNC=main go build


此時在同個資料夾下會產生 ``ssa.html`` ，
打開簡單的 web server 觀看內容：

.. code-block:: sh

    python -m http.server


可以在網頁上點選某個值或區塊，
此時會對各階段對應的地方上色。


參數
========================================

.. code-block:: sh

    # 輸出所有執行的指令
    go build -x

    # 關閉編譯器優化和 inlining，可以在 ``go tool compile -help`` 找到可傳給編譯器的參數
    go build -gcflags="-N -l"

    # 輸出測試過程
    go test -v

    # 執行 Go 的 race detector
    go test -race

    # 指定要執行的測試
    go test -run=Example

    # 輸出測試涵蓋結果並且在瀏覽器中顯示
    go test -coverprofile=c.out && go tool cover -html=c.out

    # 讓 Go tool 呼叫外部的程式去處理
    go test -exec CMD

    # 取得套件，如果套件已經存在於 GOPATH 的話，將不會更新，要加上 ``-u`` 來強制更新
    go get -u github.com/golang/lint/golint

    # 只下載套件，不編譯、不安裝
    go get -d golang.org/x/oauth2/...

    # 取得測試時需要的額外相依套件
    go get -t

    # 以客製化的格式列出 Go 套件
    go list -f '{{.Deps}}' runtime
    # [runtime/internal/atomic runtime/internal/sys unsafe]




參考
========================================

* `Go - Frequently Asked Questions (FAQ) <http://golang.org/doc/faq>`_
* `Wikipedia - Go <https://en.wikipedia.org/wiki/Go_%28programming_language%29>`_
* `Go GC: Solving the Latency Problem in Go 1.5 <https://sourcegraph.com/blog/live/gophercon2015/123574706480>`_
    - `HackerNews <https://news.ycombinator.com/item?id=9854408>`_

* `Go by Example <https://gobyexample.com/>`_
* `Go tooling essentials <http://golang.rakyll.org/go-tool-flags/>`_
* `go list, your Swiss army knife <http://dave.cheney.net/2014/09/14/go-list-your-swiss-army-knife>`_
