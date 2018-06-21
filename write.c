#define VGABUF ((volatile char *) 0xb8000)
#include "decls.h"

void __attribute__((regparm(2)))
vga_write_cyan(const char *s, int8_t linea) {
    vga_write(s, linea, 0xB0);
}


void vga_write(const char *s, int8_t linea, uint8_t color){
  
    volatile char *buf = VGABUF;
    
    if(linea < 0){
        //..
    }

    //else

    buf += 160*linea;

    int pos = 0;
    while (s[pos] != '\0') {
        *buf++ = s[pos];
        *buf++ = color;
        pos++;
    }   
}

static size_t anchura(uint64_t val) {
    uint64_t n = val;
    size_t cantidad_digitos = 0;
    while(n > 0) {
        cantidad_digitos++;
        n /= 10;
    }
    return cantidad_digitos;
}

//funcion fmt_int para el primer challange

// Escribe en ‘s’ el valor de ‘val’ en base 10 si su anchura
// es menor que ‘bufsize’. En ese caso devuelve true, caso de
// no haber espacio suficiente no hace nada y devuelve false.
bool fmt_int(uint64_t val, char *s, size_t bufsize) {

    size_t long_val = anchura(val);
    if (long_val >= bufsize) 
        return false;    
    size_t posicion = long_val;
    uint64_t n = val;
    s[posicion] = '\0';
    while(n > 0) {
        posicion--;
        s[posicion] = (char) ((n % 10) + 48);
        n /= 10;
    }
    return true;
}


