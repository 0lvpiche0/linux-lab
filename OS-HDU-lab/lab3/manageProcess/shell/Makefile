target = myshell   #输出的可执行程序名
CC = gcc       #编译器

#指定搜索c文件的路径
SRC =  $(wildcard ./src/*.c)
SRC +=  $(wildcard ./lib/*.c)

###################################
OBJ = $(patsubst %.c, %.o, $(SRC))

$(target):$(OBJ)
	$(CC) $^ -o $@

.PHONY: clean
clean:
	find . -name "*.o" | xargs rm -f
	find . -name "$(target)" | xargs rm -f

