#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <raylib.h>
#include "utils.h"

using namespace std;

class Terminal{
    float font_size;

    vector<string> history;
    string currentInput;
    Font font;

    public:

    Terminal();

    void Start();

    void Clear();

    void AddEntry(std::string entry);
    
    void Draw(int x, int y);
    
    std::string Update();
    std::string Prompt(std::string prompt);
};
