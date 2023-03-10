FROM ubuntu:22.04 AS base

ARG BUILD_TYPE=Release
ARG BUILD_DIR=build

RUN apt-get update && apt-get install -y \
    gdb-multiarch \
    wget \
    xz-utils \
    make cmake ninja-build bzip2 mc file

RUN mkdir /usr/opt/
# RUN wget --directory-prefix=/usr/opt/ https://developer.arm.com/-/media/Files/downloads/gnu-a/10.3-2021.07/binrel/gcc-arm-10.3-2021.07-aarch64-aarch64-none-elf.tar.xz
# RUN mkdir -p /usr/opt/aarch64-none-elf 
# RUN tar -xf /usr/opt/gcc-arm-10.3-2021.07-aarch64-aarch64-none-elf.tar.xz -C /usr/opt/aarch64-none-elf  --strip-components=1
# RUN ln -s /usr/opt/aarch64-none-elf/bin/aarch64-none-elf-gcc /usr/bin/aarch64-none-elf-gcc
# RUN ln -s /usr/opt/aarch64-none-elf/bin/aarch64-none-elf-ar /usr/bin/aarch64-none-elf-ar
# RUN ln -s /usr/opt/aarch64-none-elf/bin/aarch64-none-elf-as /usr/bin/aarch64-none-elf-as
# RUN ln -s /usr/opt/aarch64-none-elf/bin/aarch64-none-elf-ld /usr/bin/aarch64-none-elf-ld
# RUN ln -s /usr/opt/aarch64-none-elf/bin/aarch64-none-elf-objcopy /usr/bin/aarch64-none-elf-objcopy


# ENV CC="/usr/bin/aarch64-none-elf-gcc"
# ENV CXX="/usr/bin/aarch64-none-elf-gcc"

RUN wget --directory-prefix=/usr/opt/ https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-aarch64-linux.tar.bz2
RUN mkdir -p /usr/opt/gcc-arm-none-eabi
RUN tar -xvjf /usr/opt/gcc-arm-none-eabi-10.3-2021.10-aarch64-linux.tar.bz2 -C /usr/opt/gcc-arm-none-eabi --strip-components=1
RUN ln -s /usr/opt/gcc-arm-none-eabi/bin/arm-none-eabi-gcc /usr/bin/arm-none-eabi-gcc
RUN ln -s /usr/opt/gcc-arm-none-eabi/bin/arm-none-eabi-ar /usr/bin/arm-none-eabi-ar
RUN ln -s /usr/opt/gcc-arm-none-eabi/bin/arm-none-eabi-as /usr/bin/arm-none-eabi-as
RUN ln -s /usr/opt/gcc-arm-none-eabi/bin/arm-none-eabi-ld /usr/bin/arm-none-eabi-ld
RUN ln -s /usr/opt/gcc-arm-none-eabi/bin/arm-none-eabi-objcopy /usr/bin/arm-none-eabi-objcopy

ENV CC="/usr/bin/arm-none-eabi-gcc"
ENV CXX="/usr/bin/arm-none-eabi-gcc"

RUN ls /usr/opt/gcc-arm-none-eabi/lib/

WORKDIR /home/piOS

COPY . .

FROM base AS build
RUN rm -rf ./${BUILD_DIR}
RUN cmake -G Ninja -B ./${BUILD_DIR} -S .
RUN cmake --build ./${BUILD_DIR}

FROM scratch AS export-stage
COPY --from=build ./home/piOS/build/bin .
