CXX = clang++
LD = clang++
CFLAGS := -std=c++20 -Wall -pedantic -static -g

LIB_DIR := arm64-darwin23-clang
LIB := expression_parser

OBJS = ast.o expression.o value.o position.o test.o spreadsheet.o

all: acme_program

acme_program: $(OBJS)
	$(LD) -L$(LIB_DIR) -l$(LIB) -o $@ $^

clear:
	rm -f acme_program $(OBJS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

