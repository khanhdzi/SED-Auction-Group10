CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

# List all source files here
SRC = src/class/Authenticator.cpp src/class/User.cpp src/class/Item.cpp \
      src/class/Bid.cpp src/class/RatingRecord.cpp src/dao/userDataHandler.cpp \
      src/dao/BidDAO.cpp src/dao/RatingDAO.cpp src/dao/ItemListingHandler.cpp \
      src/controller/UserController.cpp src/controller/ItemDataController.cpp \
      src/controller/BidController.cpp src/controller/RatingController.cpp \
      src/ui/WelcomeScreen.cpp src/ui/member/MemberMenu.cpp \
      src/ui/admin/AdminMenu.cpp src/ui/guest/GuestMenu.cpp \
      src/utils/InputValidator.cpp src/utils/utils.cpp src/utils/Category.cpp \
      src/main.cpp 

OBJ = $(SRC:.cpp=.o)
TARGET = Group10_Program.exe

# Default target to build the final executable
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files and the executable (cross-platform)
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\\,$(OBJ)) $(TARGET)
else
	rm -f $(OBJ) $(TARGET)
endif

# Build and run the application
run: all
	./$(TARGET)
