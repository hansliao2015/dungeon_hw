CC = g++

all = ./sources/*.cpp

main: $(all)
	$(CC) $(all) -o main
