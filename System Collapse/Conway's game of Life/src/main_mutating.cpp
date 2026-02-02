#include <raylib.h>
#include "simulation_mutating.hpp"
#include <iostream>

int main(){
    Color GREY = {29, 29, 29, 255};
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    const int CELL_SIZE = 25;
    int FPS = 12;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game of Life - Mutating Rules");
    SetTargetFPS(FPS);

    Simulation simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);

    std::cout << "\n<----------------------Mutating Game of Life---------------------->\n";
    std::cout << "This is a Conway's Game of Life variant where rules MUTATE over time!\n\n";
    std::cout << "Classic Rules (B3/S23):\n";
    std::cout << "  Birth: A dead cell with exactly 3 live neighbours becomes alive\n";
    std::cout << "  Survival: A live cell with 2 or 3 live neighbours survives\n";
    std::cout << "  Death: All other cells die or stay dead\n\n";
    std::cout << "MUTATION MECHANIC:\n";
    std::cout << "  • Rules automatically mutate every N generations\n";
    std::cout << "  • Watch as the simulation evolves unexpected behaviors!\n";
    std::cout << "  • Rule notation: B(birth counts)/S(survival counts)\n";
    std::cout << "    Example: B36/S23 means birth on 3 or 6, survive on 2 or 3\n";
    std::cout << "----------------------------------------------------------------\n";
    std::cout << "\nCONTROLS:\n";
    std::cout << "  ENTER       - Start simulation\n";
    std::cout << "  SPACE       - Pause simulation\n";
    std::cout << "  R           - Generate random pattern\n";
    std::cout << "  C           - Clear grid\n";
    std::cout << "  M           - Mutate rules NOW\n";
    std::cout << "  T           - Reset to classic rules (B3/S23)\n";
    std::cout << "  +/=         - Increase mutation interval\n";
    std::cout << "  -           - Decrease mutation interval\n";
    std::cout << "  F           - Speed up (increase FPS)\n";
    std::cout << "  S           - Slow down (decrease FPS)\n";
    std::cout << "  Mouse Click - Toggle cells (when paused)\n";
    std::cout << "----------------------------------------------------------------\n\n";

    //Simulation loop
    while(WindowShouldClose() == false){
        //1. Event Handling
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y/CELL_SIZE;
            int column = mousePosition.x/CELL_SIZE;
            simulation.ToggleCell(row, column);
        }
        
        if(IsKeyPressed(KEY_ENTER)){
            simulation.Start();
            SetWindowTitle("Mutating Game of Life - RUNNING");
        }
        else if (IsKeyPressed(KEY_SPACE)){
            simulation.Stop();
            SetWindowTitle("Mutating Game of Life - PAUSED");
        }
        else if(IsKeyPressed(KEY_F)){
            FPS += 2;
            SetTargetFPS(FPS);
            std::cout << "FPS increased to: " << FPS << std::endl;
        }
        else if(IsKeyPressed(KEY_S)){
            if(FPS > 5){
                FPS -= 2;
                SetTargetFPS(FPS);
                std::cout << "FPS decreased to: " << FPS << std::endl;
            }
        }
        else if(IsKeyPressed(KEY_R)){
            simulation.CreateRandomState();
            std::cout << "Random pattern generated" << std::endl;
        }
        else if(IsKeyPressed(KEY_C)){
            simulation.ClearGrid();
            std::cout << "Grid cleared" << std::endl;
        }
        else if(IsKeyPressed(KEY_M)){
            simulation.MutateRules();
            std::cout << "Rules mutated! New rules: " << simulation.GetCurrentRulesString() << std::endl;
        }
        else if(IsKeyPressed(KEY_T)){
            simulation.ResetRules();
            std::cout << "Rules reset to classic Conway B3/S23" << std::endl;
        }
        else if(IsKeyPressed(KEY_EQUAL) || IsKeyPressed(KEY_KP_ADD)){
            int newInterval = simulation.GetMutationInterval() + 10;
            simulation.SetMutationInterval(newInterval);
            std::cout << "Mutation interval increased to: " << newInterval << " generations" << std::endl;
        }
        else if(IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT)){
            int newInterval = simulation.GetMutationInterval() - 10;
            if(newInterval >= 10){
                simulation.SetMutationInterval(newInterval);
                std::cout << "Mutation interval decreased to: " << newInterval << " generations" << std::endl;
            }
        }

        //2. Update State
        simulation.Update();

        //3. Drawing
        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        simulation.DrawUI();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
