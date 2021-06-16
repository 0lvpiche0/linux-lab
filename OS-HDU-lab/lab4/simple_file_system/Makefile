target = simple_file_system   #输出的可执行程序名
CC = g++       #编译器


SRC =  $(wildcard ./src/*.cpp)

###################################
OBJ = $(patsubst %.cpp, %.o, $(SRC))

$(target):$(OBJ)
	$(CC) $^ -o $@

.PHONY: clean
clean:
	find . -name "*.o" | xargs rm -f
	find . -name "$(target)" | xargs rm -f

