FROM archlinux/base

RUN pacman -Syu --noconfirm
RUN pacman -S --noconfirm clang cmake autoconf

ENV HOME /root
WORKDIR /root
CMD ["/bin/sh"]
