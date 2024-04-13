CC = g++

all = ./sources/*.cpp ./utils/*.cpp

main: $(all)
	$(CC) $(all) -o main
