#pragma once
#include "grid.hpp"
#include <vector>
#include <string>

struct LifeRules {
    std::vector<int> survivalCounts;  // Number of neighbors for a live cell to survive
    std::vector<int> birthCounts;     // Number of neighbors for a dead cell to be born
    
    LifeRules() {
        // Standard Conway's rules: B3/S23
        survivalCounts = {2, 3};
        birthCounts = {3};
    }
    
    std::string ToString() const {
        std::string result = "B";
        for(int b : birthCounts) result += std::to_string(b);
        result += "/S";
        for(int s : survivalCounts) result += std::to_string(s);
        return result;
    }
};

class Simulation
{
    public:
        Simulation(int width, int height, int cellSize)
        : grid(width, height, cellSize), 
          tempGrid(width, height, cellSize), 
          run(false),
          generationCount(0),
          mutationInterval(50),
          generationsSinceLastMutation(0) {};
        
        void Draw();
        void DrawUI();
        void SetCellValue(int row, int column, int value);
        int CountLiveNeighbors(int row, int column);
        void Update();
        bool IsRunning() {return run;}
        void Start() {run = true;}
        void Stop() {run = false;}
        void ClearGrid();
        void CreateRandomState();
        void ToggleCell(int row, int column);
        void MutateRules();
        void ResetRules();
        int GetGeneration() const { return generationCount; }
        std::string GetCurrentRulesString() const { return currentRules.ToString(); }
        void SetMutationInterval(int interval) { mutationInterval = interval; }
        int GetMutationInterval() const { return mutationInterval; }
        
    private:
        Grid grid;
        Grid tempGrid;
        bool run;
        int generationCount;
        int mutationInterval;
        int generationsSinceLastMutation;
        LifeRules currentRules;
        std::vector<LifeRules> ruleHistory;
        
        bool ShouldCellLive(int liveNeighbors, bool isCurrentlyAlive);
};
