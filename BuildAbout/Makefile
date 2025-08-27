# Makefile内容通常由以下三部分组成
# <目标文件名称>:<前置依赖>
#  \t<执行的命令>

# 引入变量，定义变量 objects
objects := hello.o main.o

# 自动推导

# 伪目标:解决名称冲突，声明伪目标

# 放在第一个的是依赖目标
# 目标是编译出main文件 依赖是 hello.o 和 main.o 文件
# 编译的命令是gcc hello.o main.o -o main
#main: hello.o main.o
main: $(objects)
	gcc $(objects) -o main

# 目标是main.o 依赖main.c和hello.h
# 编译的命令是gcc -c main.c -o main.o
# main.o: main.c hello.h
# 	gcc -c main.c
main.o: main.c 


#目标是hello.o 依赖hello.c 和 Hello.h
# 编译的命令是gcc -c hello.c
# hello.o: hello.c hello.h
# 	gcc -c hello.c
hello.o: hello.h

#声明伪目标
.PHONY : clean

clean:
	-rm main $(objects)