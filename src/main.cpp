#include <string>
#include <vector>
#include <raylib.h>
#include "utils.h"
#include "terminal.h"
#include "player.h"
#include "actions.h"

using namespace std;


int main(){

    InitWindow(800,800,"DragonAi");
    SetTraceLogLevel(LOG_NONE);

    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

    Terminal terminal;
    Player player;
    player.CurrentRoom = CreateWorld();

    float padding = 20;
    bool exit = false;

    string name = terminal.Prompt("what is your name?");
    player.Name = name;

    terminal.AddEntry("Welcome to DragonAi !");
    terminal.AddEntry("Type (help) for help.");

    LookAction lookAction;
    lookAction.Execute(player, terminal);

    auto all_actions = GetAllActions();

    while (exit==false)
    {
        string prompt = terminal.Prompt("");
        string command = "";
        vector<string> args;

        ParseInput(prompt,command,args);        
        
        for (auto& action : all_actions){
            if (action->Name == command){
                action->Execute(player, terminal);
            }
        }
    }

    return 0;
}