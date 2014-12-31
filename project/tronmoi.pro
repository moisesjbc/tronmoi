LIBS += -lSDL_ttf -lSDL

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror -pedantic -pedantic-errors

SOURCES += \
    ../src/main.cpp \
    ../src/game_grid.cpp \
    ../src/tronmoi.cpp

HEADERS += \
    ../src/game_grid.hpp \
    ../src/tronmoi.hpp
