#include "decls.h"
#include "multiboot.h"
#include "lib/string.h"

#define USTACK_SIZE 4096

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
    two_stacks_c();
    while (1){
        __asm__("hlt");
    }


}

static uint8_t stack1[USTACK_SIZE] __attribute__((aligned(4096)));
static uint8_t stack2[USTACK_SIZE] __attribute__((aligned(4096)));

void two_stacks_c() {
    // Inicializar al *tope* de cada pila.
    uintptr_t *a = (uintptr_t*) (stack1+USTACK_SIZE);
    uintptr_t *b = (uintptr_t*) (stack2+USTACK_SIZE);

    // Preparar, en stack1, la llamada:
    //vga_write("vga_write() from stack1", 15, 0x57);

    // AYUDA 1: se puede usar alguna forma de pre- o post-
    // incremento/decremento, según corresponda:
    //
    //     *(a++) = ...
    //     *(++a) = ...
    //     *(a--) = ...
    //     *(--a) = ...

    //Ahora estamos en el tope de la pila y se que 'crece hacia arriba'
    //Paso los stacks de manera inversa
    *(--a) = 0x57; 
    *(--a) = 15;  
    *(--a) = (uintptr_t) "vga_write() from stack1"; 
    
    
    //Primera llamada usando task_exec().
    //Supongo que con s1 quisieron poner a?
    task_exec((uintptr_t) vga_write, (uintptr_t) a);
    

    // AYUDA 2: para apuntar a la cadena con el mensaje,
    // es suficiente con el siguiente cast:
    //
    //   ... a ... = (uintptr_t) "vga_write() from stack1";

    // Preparar, en s2, la llamada:
    //vga_write("vga_write() from stack2", 16, 0xD0);

    // AYUDA 3: para esta segunda llamada, usar esta forma de
    // asignación alternativa:
    //b -= 3;
    //b[0] = ...
    //b[1] = ...
    //b[2] = ...
    b -= 3;
    b[0] = (uintptr_t) "vga_write() from stack2";
    b[1] = 16;
    b[2] = 0xD0;
    
    // Segunda llamada con ASM directo. Importante: no
    // olvidar restaurar el valor de %esp al terminar, y
    // compilar con: -fasm -fno-omit-frame-pointer.
  //  asm("...; call *%1; ..."
  //      : /* no outputs */
  //      : "r"(s2), "r"(vga_write));
  asm("movl %%esp,%%esi; movl %0,%%esp; call *%1; movl %%esi,%%esp":: "r"(&(b[0])), "r" (vga_write));
}
