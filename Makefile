CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

# List all source files here
SRC = src/class/Authenticator.cpp src/class/User.cpp src/class/Item.cpp src/class/Bid.cpp \
      src/dao/userDataHandler.cpp src/dao/ItemDAO.cpp src/dao/BidDAO.cpp\
      src/controller/UserController.cpp src/controller/BidController.cpp\
      src/ui/WelcomeScreen.cpp \
      src/ui/member/MemberMenu.cpp src/ui/admin/AdminMenu.cpp src/ui/guest/GuestMenu.cpp \
      src/ui/BidUI.cpp \
      src/utils/InputValidator.cpp src/utils/utils.cpp \
      src/main.cpp \

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
