CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
SRC = src/class/Authenticator.cpp src/controller/UserController.cpp \
      src/dao/userDataHandler.cpp src/utils/InputValidator.cpp src/main.cpp src/class/User.cpp src/ui/WelcomeScreen.cpp src/ui/WelcomeScreen.cpp \
	  src/ui/member/MemberMenu.cpp src/ui/admin/AdminMenu.cpp  src/ui/guest/GuestMenu.cpp \
	  src/ui/BidUI.cpp src/DAO/BidDAO.cpp src/controller/BidController.cpp src/class/Bid.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
