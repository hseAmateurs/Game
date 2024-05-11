#include "positions.h"

int pos::getOppositePos(int pos) {
    return (pos + pos::hexPos::count/2) % pos::count;
}