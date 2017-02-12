- Driver Domain: http://wiki.xenproject.org/wiki/Driver_Domain

  - 原本設計是由 Dom0 的 linux guest OS 提供 driver
  - 現在把提供 driver 這個需求剝離到獨立的 guest OS 上負責, 這種 guest OS 就被命名為 Driver Dom.
  - 需要有 IOMMU 支援, 才能提供安全性的隔離以及支援非 Para-Virtualization 的 guest.
