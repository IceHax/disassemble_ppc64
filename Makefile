# capstone library name (without prefix 'lib' and suffix '.so')
LIBNAME = capstone
HEADERS = disassemble_tools.h  elf.h  error.h  little_endian.h  printer.h
FILES	= disassemble_ppc64 disassemble_tools error printer
OBJ	= $(addsuffix .o, $(FILES))
EXEC	= disassemble_ppc64

all: $(OBJ)
	${CC} -o $(EXEC) $(OBJ) -O3 -Wall -l$(LIBNAME)

%.o: %.c $(HEADERS)
	${CC} -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) *~


