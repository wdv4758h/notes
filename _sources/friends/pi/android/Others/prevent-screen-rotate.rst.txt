* 在 Manifest 中 ::

    <activity
      ...
      android:screenOrientation="portrait"
      >

  - 改成 ``"landscape"`` 會使螢幕固定為水平

* 在 ``onCreate()`` 中 ::

    setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_NOSENSOR);
