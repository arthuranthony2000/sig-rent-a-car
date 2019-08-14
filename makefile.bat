gcc -c ./start/main.c ./architecture/views/index/index.c
gcc -o executable main.o index.o

executable

rm *.o
rm *.exe

pause