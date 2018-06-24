/*.globl breakpoint
breakpoint:
        // Manejador mínimo.
        iret
*/

// A
/*.globl breakpoint
breakpoint:
        nop
        test %eax, %eax
        iret
*/
//FIN A

// B
/*.globl breakpoint
breakpoint:
        nop
        test %eax, %eax
        ret
*/
//FIN B


//OPCION B -- vga_write2 --
.globl breakpoint
breakpoint:
    // (1) Guardar registros.
    //Guardo esp en ebp momentaneamente
    push %ebp
    movl %esp, %ebp
    push %eax
    push %edx
    push %ecx

// begin: vga_write2 //
    /*
    // (2) Preparar argumentos de la llamada.
    // argumentos de vga_write2(  eax, edx , ecx )
    // Se carga en orden inverso es decir primero el último
    movl $0xB0, %ecx
    movl $14, %edx
    movl $breakpoint_msg, %eax
    
    // (3) Invocar a vga_write2()
    call vga_write2
    */
// end: vga_write2 //

// begin: vga_write //
    
    // (2) Preparar argumentos de la llamada.
    // argumentos de vga_write deben estar en una pila
    // Se carga en orden inverso es decir primero el último
    push $0xB0
    push $14
    push $breakpoint_msg
    
    // (3) Invocar a vga_write()
    call vga_write
    
// end: vga_write //


    // (4) Restaurar registros.
    pop %ecx
    pop %edx
    pop %eax
    // Restauro esp desde ebp
    movl %ebp, %esp
    pop %ebp

// (5) Finalizar ejecución del manejador.
        iret

#define PIC1 0x20
#define ACK_IRQ 0x20

.globl ack_irq
ack_irq:
    // Indicar que se manejó la interrupción.
    movl $ACK_IRQ, %eax
    outb %al, $PIC1
    call keyboard
    iret

.globl timer_asm
timer_asm:
    // Guardar registros e invocar handler
    pusha
    call timer

    // Ack *antes* de llamar a sched()
    movl $ACK_IRQ, %eax
    outb %al, $PIC1

    // Llamada a sched con argumento
    push %esp
    call sched

    // Retornar (si se volvió de sched)
    addl $4, %esp
    popa
    iret



.globl divzero
divzero:
    //Incrementamos ebx
    inc %ebx
    //Guardamos los registros
    push %ecx
    push %edx
    push %eax
    // Preparo los argumentos para la llamada vga_write_cyan

    movl $17, %edx //Segundo arg
    movl $msg_div, %eax //Primer arg

    //Invocar a la funcion que imprime
    call vga_write_cyan

    //Restauramos registros
    
    pop %eax
    pop %edx
    pop %ecx

    iret

.data
breakpoint_msg:
        .asciz "Hello, breakpoint vga_write"
msg_div:
    .asciz "Se divide por ++ebx"
        
