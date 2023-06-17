CXX=gcc
CFLAGS=-Wall -Wextra -Werror -std=c++17 -lstdc++ -g
# CFLAGS=-std=c++17 -lstdc++ -g
TEST = s21_matrix_oop_test
TARGET = s21_matrix_oop

SRC_DIRS := ./Project
SRCS := $(shell find $(SRC_DIRS) -name '*.cc' )
SRCSH := $(shell find $(SRC_DIRS) -name '*.h' )

# TEST_DIR = ./
# TEST_SRC := $(shell find $(TEST_DIR) -name '*.cc' )
# TEST := $(addsuffix .o,$(basename $(TEST_SRC)))
TEST = Project/s21_matrix_oop_test

OBJS = $(addsuffix .o,$(basename $(SRCS)))

all:  $(TARGET).a


push: 
	git add .
	git commit -m'$m'
	git push origin $o


$(TARGET).a: $(OBJS)
	@ar rc $@ $(OBJS)

%.o: %.cc
	$(CXX) $(CFLAGS) -c -o $@ $<

# we added a pattern rule that specifies the desired flags for compiling .cc files. 
# The % symbol is used as a wildcard to match any .cc file, and the $< variable 
# is used to reference the prerequisite file (in this case, the .cc file). 
# The $(CFLAGS) variable is used to specify the desired flags for compilation.

clean: 
	$(RM) $(OBJS) $(TARGET).a

test: clean $(TARGET).a $(OBJS)
	$(CXX) $(CFLAGS) $(TARGET).a $(TEST).cc -o test -lgtest
	# ./test 

leaks: test
	CK_FORK=no leaks --atExit -- ./test

val:
	cd Valgrind && sh run.sh

valgrind: test
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT.txt ./test
	cat RESULT.txt


docker:
	rm -rf ~/Library/Containers/com.docker.docker
	mkdir -p ~/goinfre/Docker/Data
	ln -s ~/goinfre/Docker ~/Library/Containers/com.docker.docker
