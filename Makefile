
CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

# List all source files here
SRC = src/class/Authenticator.cpp src/controller/UserController.cpp \
      src/dao/userDataHandler.cpp src/utils/InputValidator.cpp src/main.cpp src/class/User.cpp src/ui/WelcomeScreen.cpp \
	  src/utils/Category.cpp src/class/Item.cpp\
	  src/dao/ItemListingHandler.cpp src/controller/ItemDataController.cpp

OBJ = $(SRC:.cpp=.o)
TARGET = app

# Default target to build the final executable
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files and the executable (Windows version)
clean:
	del /Q \"$(subst /,\\,$(OBJ))\" \"$(TARGET)\"

# Build and run the application
run: all
	./$(TARGET)