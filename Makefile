CXX = g++
CXXFLAGS = -std=c++2a -Wall -Wextra -g -I src

TARGET = biblioteca.exe
SRCS = src/main.cpp src/item_acervo.cpp src/livro.cpp src/revista.cpp src/usuario.cpp src/emprestimo.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	del /f /q $(TARGET) 2>nul || rm -f $(TARGET)