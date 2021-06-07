target1=receiver        
target2=sender       
src=$(wildcard *.c)   
deps=$(wildcard *.h)   
obj=$(patsubst %.c,%.o,$(src))    

all:$(target1) $(target2)    

$(target1):./src/receiver.o  
	gcc $^ -pthread -o $@  
  
$(target2):./src/sender.o   
	gcc $^ -pthread -o $@  

.PHONY:clean  
clean:
	find . -name "*.o" | xargs rm -f
	find . -name "$(target1)" | xargs rm -f  
	find . -name "$(target2)" | xargs rm -f  