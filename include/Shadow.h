#ifndef BATTLESHIP_SHADOW_H
#define BATTLESHIP_SHADOW_H

class Board;

class Shadow {
public:
    Shadow(Board &board);

private:
    Board &board;
};


#endif //BATTLESHIP_SHADOW_H
