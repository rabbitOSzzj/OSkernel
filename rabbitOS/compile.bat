nasm -f elf32 oskernel.asm -o temp\oskernel.o
nasm -f elf32 liba.asm -o temp\liba.o
gcc -c -m16 -march=i386 -masm=intel -nostdlib -ffreestanding -mpreferred-stack-boundary=2 libc.c -o temp\libc.o

ld -r -b binary temp\liba.o temp\libc.o temp\oskernel.o -o temp\oskernel.bin

dd if=E:\oscode\rabbitOS\temp\oskernel.bin of=E:\oscode\rabbitOS.vhd bs=512 count=100 seek=9

echo Done!