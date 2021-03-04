.PHONY = clean

all: hello_world_payload

hello_world.o: hello_world.asm
	nasm -f elf64 hello_world.asm -o hello_world.o

hello_world_payload: hello_world.o
	./getShellcode.sh hello_world.o > hello_world_payload

clean:
	rm hello_world.o hello_world_payload -f
