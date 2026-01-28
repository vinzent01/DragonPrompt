#include "terminal.h"


Terminal::Terminal(){
    font_size = 24;
    font = LoadFont("mozart.ttf");
}

void Terminal::Start(){

}

void Terminal::Clear(){
    history.clear();
}

void Terminal::AddEntry(std::string entry){
    vector<string> lines = split_lines(entry);
    for (auto line : lines){
        history.push_back(line);
    }
}

std::string Terminal::Update(){

    int key = GetCharPressed();
    while (key > 0)
    {
        if (key >= 32 && key <= 125)
            currentInput.push_back((char)key);

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !currentInput.empty())
        currentInput.pop_back();

    if (IsKeyPressed(KEY_ENTER))
    {
        history.push_back("> " + currentInput);
        std::string output = currentInput;
        currentInput.clear();
        return output;
    }
    return "";
}

void Terminal::Draw(int x, int y){

    // Desenha histórico
    for (auto& entry : history)
    {
        DrawMultilineText(entry.c_str(),x,y,font_size, font,GetScreenWidth());
        y += font_size;
    }

    // desenha o prompt
    y+= font_size;

    // Desenha prompt atual
    DrawTextEx(font,"> ", (Vector2){10, (float)y}, font_size,0, YELLOW);
    DrawTextEx(font,currentInput.c_str(), (Vector2){30, (float)y}, font_size,0, YELLOW);

    // Cursor
    auto text_size = MeasureTextEx(font,currentInput.c_str(), font_size,0);
    DrawTextEx(font,"_", (Vector2){30 + text_size.x, (float)y}, font_size,0, YELLOW);
}


std::string Terminal::Prompt(std::string prompt){
    if (prompt != ""){
        AddEntry(prompt);
    }

    std::string output = "";

    while (output == "")
    {

        if (WindowShouldClose()){
            std::exit(0);
            break;
        }

        output = Update();

        BeginDrawing();
            float delta = GetFrameTime();
            float y = 0;

            ClearBackground(BLACK);            

            Draw(10,10);

        EndDrawing();
    }
    return output;
}
