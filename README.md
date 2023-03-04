# piOS
This project is trying to build a simple OS for the RaspberryPi Zero W.
There are probably 100s of versions of toy-OS'es for the RaspberryPi-series out there on the internet, but I still think its a cool way to get some first real world experience with baremetal programming.

Some projects that I've used as guiding priciples and inspirations (sometimes more directly, sometimes less) are:
* [armOS (*Thanos Koutroubas*)](https://github.com/thanoskoutr/armOS): Especially for the overall structure and the low-level assembly code/linker-scripts.
* [Bare metal Raspberry Pi 3 tutorials (*Zoltan Baldaszti*)](https://github.com/bztsrc/raspi3-tutorial/): Great tutorial covering a lot of the basics in terms of HW/SW interface.

To build the project run
```bash
DOCKER_BUILDKIT=1 docker build --progress=plain -f Dockerfile --rm -t pi_os:latest . --output ./export/
```

To run it in `qemu` you can use
```
qemu-system-arm -M raspi0 -serial stdio -kernel .export/kernel7.elf
```