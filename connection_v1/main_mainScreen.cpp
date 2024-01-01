#include "HomeScreen.hpp"

int main(int argc, char *argv[]) {
    if ( argc != 2 ) { 
        std::cout << "Client <IPaddress>\n";
        return 1;
    }

    HomeScreen homeScreen;
    homeScreen.init(argv[1]);
    homeScreen.run();

    return 0;
}

