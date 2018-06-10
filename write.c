#include <stdint.h>
#define VGABUF ((volatile char *) 0xb8000)

void vga_write(const char *s, int8_t linea, uint8_t color){
  
    volatile char *buf = VGABUF;
    
    if(linea < 0){
        //..
    }

    //else
    buf += linea*160;
    int pos = 0;
    while (s[pos] != '\0') {
        *buf++ = s[pos];
        *buf++ = color;
        pos++;
    }   
}
