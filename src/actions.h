#pragma once
#include <string>
#include <vector>
#include "player.h"
#include "terminal.h"

using namespace std;



class Action {
    public:
    std::vector<std::string> Aliases;
    std::string Description;


    Action(vector<string> aliases, std::string description){
        this->Aliases = aliases;
        this->Description = description;
    }

    void virtual Execute(Player& player, Terminal& terminal, vector<string> args){

    }
};

class LookAction : public Action{

    public :
    LookAction() : Action({"look", "see"}, "look room arround"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override {
        string description = player.CurrentRoom->GetDescription();
        terminal.AddEntry(description);
    }
};

class ExitAction : public Action{
    public:
    ExitAction() : Action({"exit","quit"}, "exit the game"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override {
        exit(0);
    }
};

class ClearAction : public Action{
    public:
    ClearAction() : Action({"clear"}, "clear the terminal"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override {
        terminal.Clear();
    }
};

class MoveAction : public Action{
    public:
    MoveAction() : Action({"move", "go"}, "move to an exit room"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override {

        if (args.size() < 1){
            terminal.AddEntry("where?");
            return;
        }

        auto& nextRoom = args[0];
        if (player.CurrentRoom->Exits.count(nextRoom) > 0){
            player.CurrentRoom = player.CurrentRoom->Exits[nextRoom];
            terminal.AddEntry(
                player.CurrentRoom->GetDescription()
            );
        }
    }
};


vector<shared_ptr<Action>> GetAllActions();

class HelpAction : public Action {
    public :
    HelpAction() : Action({"help"}, "shows all available commands"){

    }

    void Execute(Player& player, Terminal& terminal, vector<string> args) override{
        for (auto& action : GetAllActions()){

            string aliasesStr = "";

            for (size_t i =0; i< action->Aliases.size(); i++){
                aliasesStr += action->Aliases[i];

                if (i < action->Aliases.size()-1){
                    aliasesStr += ", ";
                }
            }

            terminal.AddEntry(
                aliasesStr + " - "+ action->Description
            );
        }
    }

};


vector<shared_ptr<Action>> GetAllActions(){
    return {
        make_shared<LookAction>(),
        make_shared<ExitAction>(),
        make_shared<ClearAction>(),
        make_shared<MoveAction>(),
        make_shared<HelpAction>()
    };
};
