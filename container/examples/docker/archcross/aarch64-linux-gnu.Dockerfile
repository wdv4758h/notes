FROM archlinux/base

RUN pacman -Syu --noconfirm
RUN pacman -S --noconfirm tar wget file ripgrep neovim
# prepare several common used tools
RUN pacman -S --noconfirm cmake autoconf

ENV HOME /root
WORKDIR /root

ENV BUILD x86_64
ENV TARGET aarch64-linux-gnu
ENV TOOLCHAIN_VERSION gcc-linaro-7.2.1-2017.11
ENV LINARO_URL https://releases.linaro.org/components/toolchain/binaries/latest
ENV LINARO_NAME "${TOOLCHAIN_VERSION}-${BUILD}_${TARGET}"
ENV SYSROOT "/root/${LINARO_NAME}/${TARGET}/libc"

RUN wget "${LINARO_URL}/${TARGET}/${LINARO_NAME}.tar.xz"
RUN tar xvf "${LINARO_NAME}.tar.xz"

ENV CC      /root/${LINARO_NAME}/bin/${TARGET}-gcc
ENV CXX     /root/${LINARO_NAME}/bin/${TARGET}-g++
ENV CPP     /root/${LINARO_NAME}/bin/${TARGET}-cpp
ENV LD      /root/${LINARO_NAME}/bin/${TARGET}-ld
ENV AS      /root/${LINARO_NAME}/bin/${TARGET}-as
ENV AR      /root/${LINARO_NAME}/bin/${TARGET}-ar
ENV RANLIB  /root/${LINARO_NAME}/bin/${TARGET}-ranlib
ENV STRIP   /root/${LINARO_NAME}/bin/${TARGET}-strip
ENV CFLAGS "--sysroot=${SYSROOT} -std=gnu11"
ENV CXXFLAGS "--sysroot=${SYSROOT} -std=gnu++14"

# test compilation
RUN echo -e "#include <stdio.h>\nint main(){}" > test.c && \
    $CC test.c && \
    file ./a.out | rg aarch64 && \
    rm -f test.c a.out

CMD ["/bin/sh"]
