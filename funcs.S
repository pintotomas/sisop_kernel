// funcs.S
.globl vga_write2
vga_write2:
        push %ebp
        movl %esp, %ebp


//vga_write2(const char *s, int8_t linea, uint8_t color);
        push %ecx
        push %edx
        push %eax
        call vga_write

        leave
        ret
