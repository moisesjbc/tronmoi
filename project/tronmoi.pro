CONFIG += c++11

LIBS += -lSDL_ttf -lSDL

SOURCES += \
    ../src/main.cpp \
    ../src/game_grid.cpp \
    ../src/tronmoi.cpp

HEADERS += \
    ../src/game_grid.hpp \
    ../src/tronmoi.hpp
