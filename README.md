This is a expermintal rogue-like game.
We're trying to offer a better experience for the normal player, instead of
just a game for geekers.

If you need any help (on code), you could find some documents in docs folder.

We haven't release any binary file yet, so you should compile these source
codes by youself. Fortunately we have created some cmake files for it, so you
can easily make your own binary file by following commands (on Linux):
    
    mkdir build
    cd build
    cmake ..
    make

Make sure you have installed cmake and make tools. You should get

    Unnaming.out

if everything goes well.

Haven't tested on Windows platform, but almost everything should works fine
except 

    system("clear");

in main.cc. You should edit it to

    system("cls");

manually now. Going to fix it later.

Open an issue if you found any bug.
