FROM archlinux/base

RUN pacman -Syu --noconfirm
RUN pacman -S --noconfirm tar wget file ripgrep neovim
# prepare several common used tools
RUN pacman -S --noconfirm binutils cmake autoconf
RUN pacman -S --noconfirm clang

ENV HOME /root
WORKDIR /root

ENV FREEBSD_VERSION 11.1
ENV FREEBSD_URL https://download.freebsd.org/ftp/releases/
ENV FREEBSD_BASE_DIR /root/freebsd-base
ENV SYSROOT "${FREEBSD_BASE_DIR}"
ENV _BUILD amd64
ENV BUILD x86_64
ENV TARGET x86_64-unknown-freebsd${FREEBSD_VERSION}

RUN wget "${FREEBSD_URL}/${_BUILD}/${FREEBSD_VERSION}-RELEASE/base.txz"
RUN mkdir -p ${FREEBSD_BASE_DIR}
RUN tar xvf "base.txz" -C ${FREEBSD_BASE_DIR}
RUN rm -rf \
  ${FREEBSD_BASE_DIR}/boot \
  ${FREEBSD_BASE_DIR}/bin \
  ${FREEBSD_BASE_DIR}/sbin \
  ${FREEBSD_BASE_DIR}/share \
  ${FREEBSD_BASE_DIR}/var \
  ${FREEBSD_BASE_DIR}/etc

ENV CC  clang
ENV CXX clang++
ENV BASEFLAGS "--sysroot=${SYSROOT} --target=${TARGET} -I${SYSROOT}/usr/include -L${SYSROOT}/usr/lib -L${SYSROOT}/lib"
ENV CFLAGS "${BASEFLAGS} -std=gnu11"
ENV CXXFLAGS "${BASEFLAGS} -std=gnu++14"

# test compilation
RUN echo -e "#include <stdio.h>\nint main(){}" > test.c && \
    $CC $CFLAGS test.c && \
    file ./a.out | rg FreeBSD && \
    rm -f test.c a.out

CMD ["/bin/sh"]
