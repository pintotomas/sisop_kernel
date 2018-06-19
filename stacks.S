#define USTACK_SIZE 4096

.data
        .align 4096
stack1:
        .space USTACK_SIZE
stack1_top:

        .p2align 12
stack2:
        .space USTACK_SIZE
stack2_top:

msg1:
        .asciz "vga_write() from stack1"
msg2:
        .asciz "vga_write() from stack2"


// stacks.S continuado
.text
.globl two_stacks
two_stacks:
        // Preámbulo estándar
        push %ebp
        movl %esp, %ebp

        // Registros para apuntar a stack1 y stack2.
        mov $stack1_top, %eax
        mov $stack2_top, %esi   // Decidir qué registro usar.

        // Cargar argumentos a ambos stacks en paralelo. Ayuda:
        // usar offsets respecto a %eax ($stack1_top), y lo mismo
        // para el registro usado para stack2_top.
        movl $0x17, -4(%eax)
        movl $0x90, -4(%esi)

        movl $12, -8(%eax)
        movl $13, -8(%esi)

        movl $msg1, -12(%eax)
        movl $msg2, -12(%esi)

        // Realizar primera llamada con stack1. Ayuda: usar LEA
        // con el mismo offset que los últimos MOV para calcular
        // la dirección deseada de ESP.
        leal -12(%eax), %esp
        call vga_write

        // Restaurar stack original. ¿Es %ebp suficiente?
        movl %ebp, %esp
        

        // Realizar segunda llamada con stack2.
        leal -12(%esi), %esp
        call vga_write

        // Restaurar registros callee-saved, si se usaron.
        //...

        leave
        ret


.globl task_swap
task_swap:
      //En esp esta la dirección de memoria donde se encuentra el stack dormido
      // Lo almaceno en ecx
      pop %ecx
      // Lo almaceno en eax desde el stack actual
      pop %eax
      
      
      
      //En el stack actual guardo los registros called-saved
      //push %EBX
      //push %EDI
      //push %ESI 
      
      push %ecx // proxima instruccion antes de la llamada 
      movl %ecx, %esi
      
      // Guardo el stack actual en un registro auxiliar ecx
      movl %esp,%ecx
      
      // cambio el stack actual por el dormido
      movl (%eax), %esp
      
      //Copio en la variable esp el stack que se va a dormir
      movl %ecx, (%eax)

      // En orden inverso recupero los registros called-saved del proceso dormido
      //pop %EBX
      //pop %EDI
      
      movl %esi, %ecx 
      pop %ESI
      //pop %EDX
      push %ecx
      
      ret

      
        