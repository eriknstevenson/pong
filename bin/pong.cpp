
#include "Pong.h"

// Entry point to pong game.
int main(int argc, char **argv)
{
    Pong pong;
    pong.Run();

    std::cout << "Thanks for playing.\n";
    return EXIT_SUCCESS;
}

