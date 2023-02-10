stu : menu.o student.o teacher.o dlist.o main.o
	gcc -o $@ $^ -Wall -g
	rm *.o -rf
%.o : %.c
	gcc -c -Wall *.c
