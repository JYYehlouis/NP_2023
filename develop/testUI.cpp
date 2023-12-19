#include <SFML/Graphics.hpp>
#include "lib_v2.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

int main() {
    windowManage = 1;
    while ( windowManage ) {
        switch ( windowManage ) {
            case STARTUP:
                startupWindowShow();
                break;
            case LOBBY:
                lobbyWindowShow();
                break;
            case PLAY:
                playWindowShow();
                break;
            case CLOSE:
                break;
        }
    }

    return 0;
}