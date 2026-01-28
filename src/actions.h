#pragma once
#include <string>
#include <vector>
#include "player.h"
#include "terminal.h"

using namespace std;



class Action {
    public:
    std::string Name;
    std::vector<std::string> Aliases;
    std::string Description;


    Action(std::string name, std::string description, std::vector<std::string> Aliases){
        this->Name = name;
        this->Aliases = Aliases;
        this->Description = description;
    }

    virtual void Execute(Player& Player, Terminal& terminal) {

    }
};

class LookAction : public Action{

    public :
    LookAction() : Action("look", "look room arround", std::vector<std::string>{"see"}){

    }

    void Execute(Player& player, Terminal& terminal) override{
        string description = player.CurrentRoom->GetDescription();
        terminal.AddEntry(description);
    }
};

class ExitAction : public Action{
    public:
    ExitAction() : Action("exit", "exit the game", std::vector<std::string>{"quit"}){

    }

    void Execute(Player& player, Terminal& terminal) override {
        exit(0);
    }
};

class ClearAction : public Action{
    public:
    ClearAction() : Action("clear", "clear the terminal", std::vector<std::string>{}){

    }

    void Execute(Player& player, Terminal& terminal) override {
        terminal.Clear();
    }
};

vector<shared_ptr<Action>> GetAllActions();

class HelpAction : public Action {
    public :
    HelpAction() : Action("help", "shows all available commands",{}){

    }

    void Execute(Player& player, Terminal& terminal) override{
        for (auto& action : GetAllActions()){
            terminal.AddEntry(
                action->Name + " - "+ action->Description
            );
        }
    }

};


vector<shared_ptr<Action>> GetAllActions(){
    return {
        make_shared<LookAction>(),
        make_shared<ExitAction>(),
        make_shared<ClearAction>(),
        make_shared<HelpAction>()
    };
};
