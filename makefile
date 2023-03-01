FLAGS = -Wall -Werror

p_flag:
	gcc myps_pFlag.c -c ${FLAGS}

main: 
	gcc myps_pFlag.o myps.c -o myps.o ${FLAGS}

clean:
	rm -rf *.o