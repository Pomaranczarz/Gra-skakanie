#include <iostream>
#include "IcyTower.h"

int main()
{
    IcyTower game;
    while (game.is_working())
    {
        game.draw();
        game.update();
    }
}
