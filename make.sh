mkdir -p obj

src="."
obj="$src/obj"

FLAGS_ANSI="\
    -Os \
    -std=c89 \
    -ansi \
    -pedantic \
    -Wall"

C_FLAGS=$FLAGS_ANSI

#ELF_FLAGS="-I/lib/ld-linux.so.2 --hash-style=gnu"
ELF_FLAGS="-I/lib64/ld-linux-x86-64.so.2 --hash-style=gnu"

echo Compiling C source code...
cc -o $obj/spconfig.s $src/spconfig.c -S $C_FLAGS

echo Assembling compiled sources...
as -o $obj/spconfig.o $obj/spconfig.s

echo Linking assembled object files...
ld -o $obj/spconfig $obj/spconfig.o -lc -e main $ELF_FLAGS -s
