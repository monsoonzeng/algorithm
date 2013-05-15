include ./makefile.def
SRCS = $(wildcard *.cpp)
SRCS = rb_tree.cpp
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
TARGET = a.out 
OK = \\e[1m\\e[32m OK \\e[m
FAILURE = \\e[1m\\e[31m FAILURE \\e[m
all:$(TARGET)


$(TARGET):$(OBJS)
		@echo -ne Linking $(TARGET) ...
		@$(CXX) $(C_FLAGS)  $(INC) -o $@ $^ $(LIB) && echo  -e $(OK) || echo -e $(FAILURE)

%.o:%.cpp
		@echo -ne Compiling $<  ...
		@$(CXX) $(C_FLAGS)  $(INC) -c -o $@ $< && echo  -e $(OK) || echo -e $(FAILURE)
clean:
	@rm -f *.o
	@rm -f ./$(TARGET)

install:clean all
	strip $(TARGET)

