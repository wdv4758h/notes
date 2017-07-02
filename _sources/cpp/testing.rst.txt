========================================
C++ Testing
========================================


.. contents:: 目錄


介紹
========================================

C++ 官方並沒有定義撰寫測試一整套工具，
所以有很多第三方的實做，
其中的 Google Test 使用於 LLVM、OpenCV、Chromium 等專案。

其他語言的狀況：

* Python 內建了 ``unittest`` module，但是仍有更為方便的第三方套件實做，例如 ``pytset`` 和 ``nose``
* Rust 官方有實做撰寫測試程式的方式，也有第三方套件在上面做擴充



Google Test
========================================

`Google Test <https://github.com/google/googletest>`_ 是一套 Google 開發的測試 Framework，
除了 Google 自身使用外，
也設計了擴充機制，
期望能整合 C++ 測試 Framework 過於多套、分散的狀況。

Google Test 不需要 Exception 和 RTTI 的支援，
但是開啟的話可以提供額外的功能。


要使用 Google Test 的話要把它編譯成一個 Library，
所有測試程式都要連結到這個 Libray，
而 Google Test 內建多種 Build System 的支援，
可以選擇其中一種使用，
例如 CMake。

專案範例： `CMake + Google Test <https://github.com/wdv4758h/template-cmake-googletest>`_


Google Test 官方文件：

* `Introduction: Why Google C++ Testing Framework? <https://github.com/google/googletest/blob/master/googletest/docs/Primer.md>`_
* `Samples <https://github.com/google/googletest/blob/master/googletest/docs/Samples.md>`_
* `Advanced Guide <https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md>`_
* `FAQ <https://github.com/google/googletest/blob/master/googletest/docs/FAQ.md>`_

Google Mock 官方文件：

* `For Dummies <https://github.com/google/googletest/blob/master/googlemock/docs/ForDummies.md>`_
* `Cook Book <https://github.com/google/googletest/blob/master/googlemock/docs/CookBook.md>`_
* `Cheat Sheet <https://github.com/google/googletest/blob/master/googlemock/docs/CheatSheet.md>`_


.. code-block:: cpp

    TEST(FactorialTest, HandlesPositiveInput) {
        EXPECT_EQ(1, Factorial(1));
        EXPECT_EQ(2, Factorial(2));
        EXPECT_EQ(6, Factorial(3));
        EXPECT_EQ(40320, Factorial(8));
    }


定義客製化 assertions

.. code-block:: cpp

    AssertionResult IsInRange(int value, int low, int high) {
      if (value < low)
        return AssertionFailure()
            << value << " < lower bound " << low;
      else if (value > high)
        return AssertionFailure()
            << value << " > upper bound " << high;
      else
        return AssertionSuccess()
            << value << " is in range ["
            << low << ", " << high << "]";
    }

``EXPECT_TRUE(IsInRange(SomeFunction(), low, high))`` ::

    Value of: IsInRange(SomeFunction(), low, high)
      Actual: false (13 < lower bound 20)
    Expected: true

``EXPECT_FALSE(IsInRange(SomeFunction(), low, high))`` ::

    Value of: IsInRange(AnotherFunction(), low, high)
     Actual: true (25 is in range [20, 60])
    Expected: false



參考
========================================

* [2012] `Why Are There So Many C++ Testing Frameworks? <https://testing.googleblog.com/2012/10/why-are-there-so-many-c-testing.html>`_
* [GitHub] `Google Test <https://github.com/google/googletest>`_
* [GitHub] `UnitTest++ <https://github.com/unittest-cpp/unittest-cpp>`_
* `Qt Test <http://doc.qt.io/qt-5/qttest-index.html>`_
* `Boost Test <http://www.boost.org/doc/libs/release/libs/test/>`_
