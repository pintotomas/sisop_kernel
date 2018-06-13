make clean
make kern2
make qemu QEMU_EXTRA="-append 'param1=hola param2=adios'-m 256"
