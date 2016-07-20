Target=main

CC=arm-linux-g++ 

Compile=$(CC)

Objects+=Com.cpp Lock.cpp
Lib+= -lpthread -ldl -lm 

main:	
	$(Compile) $(Objects) $(Lib) -o $(Target)

clean:
	rm $(Target)
