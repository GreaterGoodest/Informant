.PHONY = clean

hello_world.o: hello_world.asm
	nasm -f elf64 hello_world.asm -o hello_world.o

clean:
	rm hello_world.o -f