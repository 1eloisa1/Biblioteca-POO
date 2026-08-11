CXX = g++
CXXFLAGS = -std=c++2a -Wall -Wextra -g -I src

TARGET = biblioteca.exe
SRCS = src/main.cpp src/biblioteca.cpp src/item_acervo.cpp src/livro.cpp src/revista.cpp src/usuario.cpp src/emprestimo.cpp src/registry.cpp src/repositorio.cpp src/excecoes.cpp src/emprestavel.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	del /f /q $(TARGET) 2>nul || rm -f $(TARGET)