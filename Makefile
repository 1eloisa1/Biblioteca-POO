CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -g

TARGET=biblioteca
SRCS=src/main.cpp src/livro.cpp src/usuario.cpp src/emprestimo.cpp src/biblioteca.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)