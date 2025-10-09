#pragma once 

#include "Button.h"
#include "shared.h"


class HomeScreen{
    private:
        const char* start_path="res/homeScreen/start.png"; 
        Button start;
    public:
        void init();
        void draw();
        void started(byte&);

};