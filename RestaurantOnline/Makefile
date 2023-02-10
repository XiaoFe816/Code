pp   : sqlite3.o fu.o sql_fun.o menu.o
	gcc sqlite3.o -lsqlite3 fu.o -lsqlite3 sql_fun.o -lsqlite3 menu.o
sqlite3.o : sqlite3.c
	gcc -c sqlite3.c -o sqlite3.o 
fu.o : fu.c
	gcc -c fu.c -o fu.o
7.o:7.c
	gcc -c sql_fun.c -o sql_fun.o
menu.o : menu.c
	gcc -c menu.c -o menu.o
.PHONY : clean
clean : 
	rm *.o ./a.out 

