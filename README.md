# piOS
[![Build](https://github.com/i-ilak/pios/actions/workflows/Build.yml/badge.svg)](https://github.com/i-ilak/pios/actions/workflows/Build.yml)

This project is trying to build a simple OS for the RaspberryPi Zero W.
I have zero experience with embedded SW-development and unfortunately also never had a change to look at it in university. This is a hobby project that I started to get some familiarity with the subject.
I don't really have a clear goal, but I'm using other peoples projects on the internet as a reference and will see where it will take me... I have three RaspberryPi's (Zero W, Zero 2 W, and B+) and in the end I would like the code to run on all devices.

## ToDo
[ ] Revist memory management... I think the code is a bit to simplisic (want to add virtual memory management.)

## Notes
Since I don't belive there is one perfect source for the relevant topics, I spend a lot of time reading code from others.
* [armOS (*Thanos Koutroubas*)](https://github.com/thanoskoutr/armOS): This project is pretty much where I want to be at the end (I guess), and its nice to see what will be necessary for this...
    I'd like to make clear that a good chunk of the code in this repository is almost 1-to-1 from the armOS project. I really like what was done there and I think its nice to see how all of the parts are supposed to work in the end.
    I changed some things were I found it appropritate, but at the end of the day I think Thanos did a great job and since I'm just trying to learn more about the subject, this project was a godsend!
    Also, a good chunk of the documentation is taken from him... Looking up all the GPIO-addresses etc. must have been a nightmare.
* [Bare metal Raspberry Pi 3 tutorials (*Zoltan Baldaszti*)](https://github.com/bztsrc/raspi3-tutorial/): Really nice tutorial that introduces the basic ways of how HW and SW should interact with each other.
* [Building an Operating System for the RaspberryPi (*Jake Sandler*)](https://jsandler18.github.io) Has a nice introduction to setting up dynamic memeory allocation for 32-bit systems, but seems a little bit light on some things.
* [Raspberry Pi bare metal experiments (*Brian Widdas*)](https://github.com/brianwiddas/pi-baremetal)
* [Learning operating system development using Linux kernel and Raspberry Pi (*Sergey Matyukevich*)](https://github.com/s-matyukevich/raspberry-pi-os) Lots of explenations about concepts related to OS developement using the Linux kernel and RPi OS as an example. Helps to understand some of the code out there doing things/solving things and seeing the bigger picture!

## How to build the project?
As often with embedded projects, the toolchain hassle is real. The tricky part for this project is the compiler. Since we are writing code that is supposed to run on an ARM processor, you will need the corresponding compiler. All compilers to build for ARM CPU's can be found on [ARM's website](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads). You will most probably have to cross-compile (`x86`->`arm`) and you will need to be careful if you are compiling the kernel for a `32-bit` or a `64-bit` CPU (`arm-none-eabi` vs `aarch64-none-elf`). The `CMakeLists.txt` file has all the logic needed to handle which compiler to pick depending on the Raspberry Pi Model you want to compile this code for. You will find in the toplevel `CMakeLists.txt` file a variable thats called `MODEL_X`, where `X` can be `[0,1,2,3,4]`. `MODEL_3` and `MODEL_4` have a `64bit` CPU and thus need the `aarch64` compiler. 

*Note*: This project was started with a `32bit` board (RPi 0) and thus most of the code was initially written with the ARMv6 architecture in mind. For example, the entire memory management code was written with ATAGS (ARM Tags) in mind, which where replaced by DTB's (device tree blob's) in ARMv8-a and would thus need a refresh. I will do this at some point, but for now I will focus more on exploring some of the capabilities of the `32bit` version of the board. In short, the `64bit` boards have a lot less functionality compared to the `32bit` boards with this kernel as of now.   

Once you have all of this setup, you should be able to simple `cd` into the root of this repo and run (assuming you have `cmake` and `ninja-build` installed on your system)
```bash
cmake -G Ninja -B ./build -S .
cmake --build ./build
```
... or you can use Docker
```bash
DOCKER_BUILDKIT=1 docker build --progress=plain -f Dockerfile --rm -t pi_os:latest . --output ${PATH_TO_WHERE_YOU_WANT_THE_ELF_AND_IMG}
```

## How to run the kernel?
While the ultimate goal of course is to run the kernel on a RaspberryPi, for development it is useful to also run it in `qemu`. For the `32-bit` version you can use
```bash
# ARMv6 / 32 bit
qemu-system-arm -M raspi0 -serial null -serial stdio -kernel $PATH_TO_ELF/kernel.elf
# ARMv8-a / 64 bit
qemu-system-aarch64 -M raspi3b -serial null -serial stdio -kernel $PATH_TO_ELF/kernel7.elf
```

*Note:* To run the code with `qemu` you use the `.elf`, i.e. the full executable. If you want to test the kernel out on a real Raspberry Pi, then you need to move the `.img` file onto the SD card. 


## How to generate documentation?
To generate the documentation you can run
```bash
doxygen .doxyfile
```
Please make sure to install doxygen and graphviz.
