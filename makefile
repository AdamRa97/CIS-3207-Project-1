FLAGS = -Wall -Werror

p_flag:
	gcc myps_pFlag.c -c ${FLAGS}

def_flag:
	gcc myps_default.c -c ${FLAGS}

all: 
	gcc myps_pFlag.o myps_default.o myps.c -o myps.o ${FLAGS}

make flags:
	make p_flag
	make def_flag
clean:
	rm -rf *.o