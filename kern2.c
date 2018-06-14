#include "decls.h"
#include "multiboot.h"
#include "lib/string.h"

// mbinfo.c (ejercicio opcional kern2-meminfo)
void print_mbinfo(const struct multiboot_info *mbi){

    char memoria[256] = "Physical memory: ";
    char tmp[64] = "";
    uint32_t memSize = mbi->mem_upper - mbi->mem_lower;
    memSize = (memSize >> 10) + 1;

    if (fmt_int(memSize, tmp, sizeof(tmp))) {
        strlcat(memoria, tmp, sizeof(memoria));
        strlcat(memoria, "MiB total (", sizeof(memoria));
    }
    if (fmt_int(mbi->mem_lower, tmp, sizeof(tmp))) {
        strlcat(memoria, tmp, sizeof(memoria));
        strlcat(memoria, " base, ", sizeof(memoria));
    }
    if (fmt_int(mbi->mem_upper, tmp, sizeof(tmp))) {
        strlcat(memoria, tmp, sizeof(memoria));
        strlcat(memoria, "KiB extended)", sizeof(memoria));
    }

    vga_write(memoria, 10, 0x07);


}

void kmain(const multiboot_info_t *mbi) {

    vga_write("kern2 loading.........", 8, 0x70);

    if(mbi){
        char *cmdline = (void *) mbi->cmdline;
        char buf[12] = "cmdline: ";
        strlcat( buf, cmdline, strlen(buf) + strlen(cmdline) + 1);
        vga_write(buf, 9, 0x07);
        //Primer challange
        print_mbinfo(mbi);
    }
    two_stacks();
    
    while (1){
        __asm__("hlt");
    }

}
