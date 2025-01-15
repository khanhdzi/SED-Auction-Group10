CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
SRC = src/class/Authenticator.cpp src/class/User.cpp src/class/Item.cpp \
      src/class/Bid.cpp src/dao/userDataHandler.cpp src/dao/ItemDAO.cpp \
      src/dao/BidDAO.cpp src/controller/UserController.cpp \
      src/controller/BidController.cpp src/controller/RatingController.cpp \
      src/dao/RatingDAO.cpp src/ui/WelcomeScreen.cpp src/ui/member/MemberMenu.cpp \
      src/ui/admin/AdminMenu.cpp src/ui/guest/GuestMenu.cpp \
      src/class/RatingRecord.cpp \
      src/ui/BidUI.cpp src/utils/InputValidator.cpp src/utils/utils.cpp \
      src/main.cpp

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
	
# testAverageRatingUpdate: src/testAverageRatingUpdate.cpp src/dao/UserDataHandler.cpp src/dao/RatingDAO.cpp \
#                          src/class/User.cpp src/class/RatingRecord.cpp src/controller/RatingController.cpp
# 	$(CXX) $(CXXFLAGS) -o testAverageRatingUpdate src/testAverageRatingUpdate.cpp \
#         src/dao/UserDataHandler.cpp src/dao/RatingDAO.cpp src/class/User.cpp src/class/RatingRecord.cpp \
#         src/controller/RatingController.cpp

testAverageRatingUpdate: src/testAverageRatingUpdate.cpp src/dao/UserDataHandler.cpp src/class/User.cpp
	$(CXX) $(CXXFLAGS) -o testAverageRatingUpdate src/testAverageRatingUpdate.cpp src/dao/UserDataHandler.cpp src/class/User.cpp

