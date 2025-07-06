g++ main.cpp -o main \        
    $(pkg-config --cflags --libs opencv4)
./main         