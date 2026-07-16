CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -g

TARGET=biblioteca
SRCS=src/main.cpp src/livro.cpp src/usuario.cpp src/emprestimo.cpp src/biblioteca.cpp src/item_acervo.cpp src/revista.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)