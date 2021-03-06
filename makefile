#Set compiler commands
#----------------------
NAME = PoolTable
CC = g++
COMMONFLAGS = -std=c++11 -Wall -w #-w ignores the warnings
OBJS = *.cpp
HDRS = *.h
LDFLAGS =  -L/usr/local/opt/opencv3/lib
CPPFLAGS = $(COMMONFLAGS) $(shell pkg-config opencv --cflags)
LDLIBS:=  $(shell pkg-config opencv --libs)
SRCS = $(shell find src -name '*.cpp')
OBJS = $(SRCS:src/%.cpp=bin/%.o)
	DEPS = $(SRCS:src/%.cpp=bin/%.d)



#----------------------
#file1 = main.cpp
all: $(NAME)
$(NAME): $(OBJS)
	$(CXX) $^ $(LDLIBS) $(CPPFLAGS) -o $(NAME) 
#ensures the bin directory is created
$(SRCS): | bin


bin:
	        mkdir -p $(shell find src -type d | sed "s/src/bin/")

bin/%.o: src/%.cpp
	        $(CXX) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $< -c -o $@ 

#file1_exe: $(OBJS) $(HDRS)
#	$(CC) $(OBJS) $(CFLAGS) -o cv $(LDFLAGS) $(CPPFLAGS) $(LDLIBS)
#file2_exe: $(OBJS) $(HDRS)
#	$(CC) $(PKG) $(OBJS) $(CPPFlags) -o cv $(LDFLAGS)

test1: $(NAME)
	./$(NAME) src/Photos/TableHalf/1/IMG_0227.jpg src/Photos/TableHalf/1/IMG_0228.jpg

test2: $(NAME)
	./$(NAME) src/Photos/TableHalf/2/IMG_0232.jpg src/Photos/TableHalf/2/IMG_0231.jpg

test3: $(NAME)
	./$(NAME) src/Photos/TableHalf/3/IMG_0234.jpg src/Photos/TableHalf/3/IMG_0235.jpg

test4: $(NAME)
	./$(NAME) src/Photos/TableHalf/4/IMG_0236.jpg src/Photos/TableHalf/4/IMG_0237.jpg

test5: $(NAME)
	./$(NAME) src/Photos/TableHalf/5/IMG_0238.jpg src/Photos/TableHalf/5/IMG_0239.jpg

test6: $(NAME)
	./$(NAME) src/Photos/TableHalf/6/IMG_0240.jpg src/Photos/TableHalf/6/IMG_0241.jpg

test7: $(NAME)
	./$(NAME) src/Photos/TableHalf/7/IMG_1.jpg src/Photos/TableHalf/7/IMG_2.jpg

test8: $(NAME)
	./$(NAME) src/Photos/TableHalf/7.5/IMG_1.jpg src/Photos/TableHalf/7.5/IMG_2.jpg

test9: $(NAME)
	./$(NAME) src/Photos/TableHalf/8/IMG_1.jpg src/Photos/TableHalf/8/IMG_2.jpg

test10: $(NAME)
	./$(NAME) src/Photos/TableHalf/8.5/IMG_1.jpg src/Photos/TableHalf/8.5/IMG_2.jpg

test11: $(NAME)
	./$(NAME) src/Photos/TableHalf/9/IMG_1.jpg src/Photos/TableHalf/9/IMG_2.jpg

test12: $(NAME)
	./$(NAME) src/Photos/TableHalf/10/IMG_1.jpg src/Photos/TableHalf/10/IMG_2.jpg

clean:
		rm -rf $(NAME)* bin/
