key binding
-----------
- Mod1 => windows key
- up, down, left, right (window): [Mod1 + jkl;] or [Mod1 + up/down/left/right]
- execute program: Mod1 + d
- split, resize

  - (Mod1 + hvf, r)
  - Mod1 + hvf: horizontal, virtical, fullscreen
  - Mod1 + r: resize
  - 將 window 移出 split 的方式為, move window 到超出邊界的地方 (e.g. window 在最左邊了仍往左邊 move)

- change container layout (stacked, tabbed, toggle split), focus parent

  - (Mod1 + swe, a)
  - Mod1 + s: layout stacking
  - Mod1 + w: layout tabbed
  - Mod1 + e: layout out toggle split
  - focus parent: Mod1 + a

- Mod1 + Lshift + asdf, jkl;

workspace
---------
- Mod1 + <num>
- Mod1 + shift + <num>

note
----
Tree

- info: X11 outputs, workspaces, and layout of windows
- root node: X11 root window

  - followed by: X11 outputs, dock areas, a content container, workspaces, and windows themselves

- build block of tree: Containers

  - Container can host one X11 window
  - Container can contain one or more Containers
  - workspace is also Container

- Split Containers: building layout when using tree data structure
- every Container has Orientation: horizontal, vertical or unspecified

Config
------
- config file: ``/etc/i3/config`` and ``~/.config/i3/config``
- font, dmenu_run font
- volume: ``XF86AudioMute`` + ``pulseaudio-ctl``
- i3status(volume)

  - ``man i3status``

- touchpad

  - ``~/i3/touchpad_toggle.sh``

- dmenu and rofi and Gmrun

  - https://wiki.archlinux.org/index.php/Gmrun

Tool
~~~~
- xfontsel
- xmodmap
  
  - xmodmap -pke

- xev

  - https://help.ubuntu.com/community/XfceMultimediaKeys
  - 目前抓不到 XF86AudioMute, XF86AudioLowerVolume, XF86AudioRaiseVolume

Tuning
------
- screen lock: i3lock
- bg image: feh
