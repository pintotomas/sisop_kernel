#include "decls.h"
#include "multiboot.h"
#include "lib/string.h"

void kmain(const multiboot_info_t *mbi) {
    char *cmdline = (void *) mbi->cmdline;
    vga_write("kern2 loading.........", 8, 0x70);


        char buf[12] = "cmdline: ";
        
        strlcat( buf, cmdline, strlen(buf) + strlen(cmdline) + 1);
    
        vga_write(buf, 9, 0x07);

    while (1){
        __asm__("hlt");
    }

}
