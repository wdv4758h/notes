- ``lshw -C display``: list hardware with class=display
- ``glxinfo``: OpenGL info

  - how to detect GPU driver: http://pclinuxoshelp.com/index.php/Glxinfo
  - name of display `:0`
  - direct rendering: yes
  - server glx: (SGI, ver 1.4, extensions)
  - client glx: (Mesa Project and SGI, ver 1.4, extensions)
  - Extended renderer info (GLX_MESA_query_renderer)

    - Intel Open Source | Mesa DRI Intel(R) Haswell Mobile 
    - VRAM: 1536MB, unified memory
    - OpenGL core profile version: 3.3 (Core Profile) Mesa 11.1.0
    - OpenGL version: 3.0 Mesa 11.1.0
    - OpenGLES version: 3.0 Mesa 11.1.0
    - 40 GLX Visuals | 64 GLXFBConfigs

- manjaro distro only

  - ``mhwd``: https://wiki.manjaro.org/index.php?title=Manjaro_Hardware_Detection
