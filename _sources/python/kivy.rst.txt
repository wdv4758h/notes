========================================
Kivy - Python on Android
========================================


.. contents:: 目錄


介紹
========================================

:Site: https://kivy.org/
:Documentation: https://kivy.org/docs/



基本流程 (製作 Android App)
========================================

:Documentation:
    * https://python-for-android.readthedocs.io/en/latest/
    * https://buildozer.readthedocs.io/en/latest/index.html
:Repo:
    * https://github.com/kivy/python-for-android
    * https://github.com/kivy/buildozer/


範例主程式：

.. code-block:: python

    import kivy
    kivy.require('1.10.0')  # replace with your current kivy version !

    from kivy.app import App
    from kivy.uix.label import Label


    class MyApp(App):
        def build(self):
            return Label(text='Hello world')


    if __name__ == '__main__':
        MyApp().run()


利用 Buildozer 製作 Android App：

.. code-block:: sh

    $ pipenv install buildozer
    $ buildozer init  # create buildozer.spec
    # 把 "buildozer.spec" 內的 "log_level" 設成 "2" 可以看到比較多資訊

    # build debug -> deploy to device -> run on device
    # buildozer 會自動下載需要的套件
    # 也可以只下 "buildozer android debug"
    $ buildozer android debug deploy run

    # 看 Android 上的 log
    $ buildozer android logcat -s python



參考
========================================
