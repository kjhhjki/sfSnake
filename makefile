EXECUTABLE := sfSnake
LIBDIR := "E:/SFML-2.5.1/build/lib"
LIBS :=  sfml-audio-d sfml-graphics-d  sfml-main-d sfml-network-d sfml-system-d  sfml-window-d
INCLUDES:=. "E:/SFML-2.5.1/include"
SRCDIR:=./src

.PHONY: clean all
MKDIR = mkdir
++ = g++

DELETE = del /q
RM = rd /s /q
FLAGS = -Wall -std=c++20 -O2
FLAGS += $(addprefix -I,$(INCLUDES))

DIR_OBJ = obj
DIR = $(DIR_OBJ)
SRCS = $(wildcard *.cpp) $(wildcard */*.cpp)
OBJS = $(SRCS:.cpp=.o)
OBJS := $(notdir $(OBJS))
OBJS := $(addprefix $(DIR_OBJ)/,$(OBJS))
EXES = $(wildcard *.exe)

all:$(DIR) $(EXECUTABLE) clean

debug:
	@echo $(SRCS)
	@echo $(OBJS)
$(DIR):
	$(MKDIR) $@
$(EXECUTABLE):$(OBJS)
	$(++) $^ $(FLAGS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS)) -o $@ 
	@echo making $@
$(DIR_OBJ)/%.o: %.cpp
	$(++) -c $^ $(FLAGS) -o $@
	@echo making $@
$(DIR_OBJ)/%.o: */%.cpp
	$(++) -c $^ $(FLAGS) -o $@
	@echo making $@
clean:
	$(RM) $(DIR)