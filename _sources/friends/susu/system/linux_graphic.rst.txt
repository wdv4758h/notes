DRM
---
- DRM drivers (``drivers/gpu/drm/<driver_name>/``)

  - intel i810/i915, nvidia nouveau (3xx series isn't open source), amd radeon
  - [Virtualization] qemu qxl, vmware vmwgfx
  - amd HSA driver amdkfd
  - [ARM SoC] atmel, exynos, msm, rockchip, nvidia tegra
  - ...

- DRM Internal

  - http://events.linuxfoundation.org/sites/events/files/slides/brezillon-drm-kms.pdf 
  - https://www.kernel.org/doc/htmldocs/drm/

- Gallium3D & TGSI(Tungsten Graphic Shader Infrastructure) IR

  - https://conference2008.kde.org/conference/slides/zack-akademy2008.pdf
  - generic 3d rendering IR

    - gpu hardware abstraction (API)
    - OS abstraction 

  - mesa & Gallium3D: http://www.slideshare.net/olvaffe/gallium3d-mesas-new-driver-model

- virgl(virgil) - virtualized GPU for 3D (use Gallium3D)
  
  - https://lwn.net/Articles/611212/

- drm_gralloc - gralloc HAL API implemented by DRM

  - https://github.com/pstglia/drm_gralloc
