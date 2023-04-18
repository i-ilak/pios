#include "kernel/atag.h"
#include "kernel/kerio.h"
#include "common/stdlib.h"

uint32_t get_mem_size(atag_t *atags)
{
    while(atags->header.tag_type != ATAG_NONE)
        {
            if(atags->header.tag_type == ATAG_MEM)
                {
                    return atags->mem.size;
                }
            atags = tag_next(atags);
        }
    return 0;
}

char *tohex(unsigned int value, unsigned int size)
{
    static char buffer[9];

    unsigned int offset;
    unsigned char ch;

    if(size != 1 && size != 2 && size != 4)
        return "error";

    offset = size * 2;

    buffer[offset] = 0;

    while(offset--)
        {
            ch = 48 + (value & 15);
            if(ch >= 58)
                ch += 7;

            buffer[offset] = ch;
            value = value >> 4;
        }

    return buffer;
}

void print_atag_core(atag_t *atags)
{
    printf("    Flags:        %d\n", atags->core.flags);
    printf("    Page-size:    %d\n", atags->core.pagesize);
    printf("    Root device:  %d\n\n", atags->core.rootdevice);
}

void print_atag_mem(atag_t *atags)
{
    printf("    Size:         %d MB\n", atags->mem.size / 1024 / 1024);
    printf("    Address:      %d\n\n", atags->mem.address);
}

void print_atag_cmdline(atag_t *atags)
{
    printf("    Command Line: ");
    printf(atags->cmdline.commandline);
    printf("\n\n");
}

void print_atags(uint32_t address)
{
    atag_t *atags = (atag_t *)address;
    unsigned int tag;

    puts("Reading ATAGs\n\n");

    do
        {
            tag = atags->header.tag_type;
            puts("  ATAG at address 0x");
            puts(tohex((unsigned int)atags, 4));
            puts(" is ");
            puts(tohex(tag, 4));

            switch(tag)
                {
                case 0: puts(" (ATAG_NONE)\n\n"); break;
                case ATAG_CORE:
                    puts(" (ATAG_CORE)\n\n");
                    print_atag_core(atags);
                    break;
                case ATAG_MEM:
                    puts(" (ATAG_MEM)\n\n");
                    print_atag_mem(atags);
                    break;
                case ATAG_VIDEOTEXT: puts(" (ATAG_VIDEOTEXT)\n"); break;
                case ATAG_RAMDISK:
                    puts(" (ATAG_RAMDISK)\n");
                    // print_atag_ramdisk((struct atag_ramdisk *)atags);
                    break;
                case ATAG_INITRD2:
                    puts(" (ATAG_INITRD2)\n");
                    // print_atag_initrd2((struct atag_initrd2 *)atags);
                    break;
                case ATAG_SERIAL:
                    puts(" (ATAG_SERIAL)\n");
                    // print_atag_serial((struct atag_serial *)atags);
                    break;
                case ATAG_REVISION:
                    puts(" (ATAG_REVISION)\n");
                    // print_atag_revision((struct atag_revision *)atags);
                    break;
                case ATAG_VIDEOLFB:
                    puts(" (ATAG_VIDEOLFB)\n");
                    // print_atag_videolfb((struct atag_videolfb *)atags);
                    break;
                case ATAG_CMDLINE:
                    puts(" (ATAG_CMDLINE)\n\n");
                    print_atag_cmdline(atags);
                    break;
                default: puts(" (UNKNOWN)\n"); return;
                }

            atags = tag_next(atags);
    } while(tag);
}