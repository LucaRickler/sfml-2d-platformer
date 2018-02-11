CXXFLAGS =	-std=c++11	-O2 -g  -Wall -fmessage-length=0 -lpthread -lsfml-graphics -lsfml-window -lsfml-system

COMP = src/Component.o src/Entity.o src/SpriteComponent.o src/RigidBody.o src/TextureDrawer.o src/WorldSpace.o src/TileMap.o src/TileMapSprite.o src/Character.o src/TrackerComponent.o src/AIController.o src/WeaponArm.o
OBJS = main.o $(COMP)

LIBS = 

TARGET =	bin/game

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) $(CXXFLAGS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
