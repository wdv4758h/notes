Table Of Content
----------------
- common

  - [v] WIFI connect
  - [ ] show battery
  - [v] screensaver(lock) & hibernate
  - [v] sound
  - [v] volume change + shortcut
  - [v] input method
  - [v] touchpad toggle [XF86TouchpadToggle]
  - [ ] light change [XF86MonBrightnessUp|XF86MonBrightnessDown]
  - [*] multiple screen or display
  - bar & applet

- me

  - [v] mount windows directory
  - [v] file manager

common
------
- WIFI connect
  
  - CLI

    - ``nmtui(NetworkManager)``
    - ``wifi-menu``
    - `connect_to_internet <../cli/connect_to_internet.rst>`_

  - ``nm-applet(NetworkManager)``, see bar & applet for more.


- show battery
- screensaver(lock) & hibernate

  - https://wiki.archlinux.org/index.php/I3#Shutdown.2C_reboot.2C_lock_screen

  ::

      $ i3lock
      $ systemctl suspend

- sound

  - http://unix.stackexchange.com/a/67535

  ::

    pactl, pacmd
    $ pactl list short sinks
    $ pactl list short sources

- volume change

  pulseaudio-ctl::

    Volume level     : 25 %
    Is sink muted    : no
    Is source muted  : no
    Detected sink    : 1
    Detected source  : 2
    Pulse version    : 7.1

    # Volume level
    $ pulseaudio-ctl up/down
    $ pulseaudio-ctl up/down n
    $ pulseaudio-ctl set n

    $ pulseaudio-ctl mute/mute-input

    Optionally, redefine an upper threshold in ~/.config/pulseaudio-ctl/config
  
- input method

  - ``hime`` & ``~/.xprofile``
  - see `xinput_method <../cli/xinput_method.rst>`_

- touchpad toggle

  - ``xinput``::

      > xinput list
      Virtual core pointer          id=2    [master pointer  (3)]
       ↳ Virtual core XTEST pointer id=4    [slave  pointer  (2)]
       ↳ AlpsPS/2 ALPS GlidePoint   id=16   [slave  pointer  (2)] 

      > xinput list-props 16
      Device 'AlpsPS/2 ALPS GlidePoint':
          Device Enabled (139):   1

      > xinput set-prop 16 "Device Enabled" 0 # disable touchpad
      > xinput set-prop 16 "Device Enabled" 1 # enable touchpad
      
      # shortcut in new version xinput
      > xinput --enable 16
      > xinput --disable 16

- light change
- multiple screen or display

  - ``xrandr``::

      xrandr --output VGA1 [--auto|--mode 1024x768] [--left-of|--right-of|--same-as] LVDS1

  - https://i3wm.org/docs/userguide.html#multi_monitor

- bar & applet

  - EWMH protocol: https://www.wikiwand.com/en/Extended_Window_Manager_Hints
  - i3config::

      bar {
          # output on all monitor
          # tray_output primary
      }
      exec --no-startup-id nm-applet

  - NetworkManager => nm-applet
  - PulseAudio => pa-applet

me
--
- mount windows directory::

    mount -t ntfs -o rw,default_permissions /dev/sda3 /run/media/susu/OS
    mount -t ntfs -o rw,default_permissions /dev/sda5 /run/media/susu/DATA

- file manager

  - preview of picture/video
  - thunar(Xfce), pcmanfm-qt(LXDE)

Misc
----
- libinoify & i3: https://faq.i3wm.org/question/121/whats-a-good-notification-daemon-for-i3/
- Compton: https://wiki.archlinux.org/index.php/Compton

  - standalone composite manager
