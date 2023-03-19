# piOS
![pipeline](https://gitlab.com/iilak/pios/badges/master/pipeline.svg)

This project is trying to build a simple OS for the RaspberryPi Zero W.
I have zero experience with embedded SW-development and unfortunately also never had a change to look at it in university. This is a hobby project that I started to get some familiarity with the subject.
I don't really have a clear goal, but I'm using other peoples projects on the internet as a reference and will see where it will take me... I have two RaspberryPi's (Zero W, Zero 2 W, and B+) and in the end I would like the code to run on all devices.

[[_TOC_]]

## Notes
Since I don't belive there is one perfect source for the relevant topics, I spend a lot of time reading code from others.
* [armOS (*Thanos Koutroubas*)](https://github.com/thanoskoutr/armOS): This project is pretty much where I want to be at the end (I guess), and its nice to see what will be necessary for this...
    I'd like to make clear that a good chunk of the code in this repository is almost 1-to-1 from the armOS project. I really like what was done there and I think its nice to see how all of the parts are supposed to work in the end.
    I changed some things were I found it appropritate, but at the end of the day I think Thanos did a great job and since I'm just trying to learn more about the subject, this project was a godsend! 
* [Bare metal Raspberry Pi 3 tutorials (*Zoltan Baldaszti*)](https://github.com/bztsrc/raspi3-tutorial/): Really nice tutorial that introduces the basic ways of how HW and SW should interact with each other.

## How to build the project?
As often with embedded projects, the toolchain hassle is real. The tricky part for this project is the compiler. Since we are writing code that is supposed to run on an ARM processor, you will need the corresponding compiler. All compilers to build for ARM CPU's can be found on [ARM's website](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads). You will most probably have to cross-compile (`x86`->`arm`) and you will need to be careful if you are compiling the kernel for a `32-bit` or a `64-bit` CPU (`arm-none-eabi` vs `aarch64-none-elf`).

Once you have all of this setup, you should be able to simple `cd` into the root of this repo and run (assuming you have `cmake` and `ninja-build` installed on your system)
```bash
cmake -G Ninja -B ./build -S .
cmake --build ./build
```
If you like to use docker, you can also use this minimal `Dockerfile` (for the `32-bit` version):
```docker
FROM rushmash/gcc-arm-embedded-docker:latest AS base

ARG BUILD_DIR=build

WORKDIR /home/piOS

COPY . .

FROM base AS build

RUN rm -rf ./${BUILD_DIR}
RUN cmake -G Ninja -B ./${BUILD_DIR} -S .
RUN cmake --build ./${BUILD_DIR}

FROM scratch AS export-stage
COPY --from=build ./home/piOS/build/bin .

```
and run it via
```bash
DOCKER_BUILDKIT=1 docker build --progress=plain -f Dockerfile --rm -t pi_os:latest . --output ${PATH_TO_WHERE_YOU_WANT_THE_ELF_AND_IMG}
```

## How to run the kernel?
While the ultimate goal of course is to run the kernel on a RaspberryPi, for development it is useful to also run it in `qemu`. For the `32-bit` version you can use
```bash
qemu-system-arm -M raspi0 -serial null stdio -kernel ${PATH_TO_ELF_FILE}/kernel7.elf
```