#include <vector>
#include <utility>
#include <algorithm>
#include <raylib.h>
#include "simulation_mutating.hpp"

void Simulation::Draw()
{
    grid.Draw();
}

void Simulation::DrawUI()
{
    // Draw semi-transparent overlay at top
    DrawRectangle(0, 0, 750, 60, Color{0, 0, 0, 200});
    
    // Draw generation counter
    DrawText(TextFormat("Generation: %d", generationCount), 10, 10, 20, WHITE);
    
    // Draw current rules
    std::string rulesStr = "Rules: " + currentRules.ToString();
    DrawText(rulesStr.c_str(), 10, 35, 18, Color{100, 255, 100, 255});
    
    // Draw mutation countdown
    int generationsUntilMutation = mutationInterval - generationsSinceLastMutation;
    std::string mutationText = "Next mutation in: " + std::to_string(generationsUntilMutation) + " gen";
    DrawText(mutationText.c_str(), 400, 10, 18, Color{255, 200, 100, 255});
    
    // Draw mutation interval setting
    std::string intervalText = "Mutation every: " + std::to_string(mutationInterval) + " gen";
    DrawText(intervalText.c_str(), 400, 35, 16, Color{200, 200, 200, 255});
    
    // Draw hint if not running
    if (!run) {
        DrawText("Press ENTER to start | SPACE to pause | R for random | C to clear", 
                 10, 720, 16, Color{150, 150, 150, 255});
        DrawText("Press M to mutate rules now | +/- to change mutation interval", 
                 10, 735, 16, Color{150, 150, 150, 255});
    }
}

void Simulation::SetCellValue(int row, int column, int value)
{
    grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbors(int row, int column)
{
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> neighborOffsets = 
    {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    for(const auto& offset : neighborOffsets)
    {
        int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
        int neighborColumn = (column + offset.second + grid.GetColumns()) % grid.GetColumns();
        liveNeighbors += grid.GetValue(neighborRow, neighborColumn);
    }
    return liveNeighbors;
}

bool Simulation::ShouldCellLive(int liveNeighbors, bool isCurrentlyAlive)
{
    if (isCurrentlyAlive) {
        // Check if the cell survives
        return std::find(currentRules.survivalCounts.begin(), 
                        currentRules.survivalCounts.end(), 
                        liveNeighbors) != currentRules.survivalCounts.end();
    } else {
        // Check if the cell is born
        return std::find(currentRules.birthCounts.begin(), 
                        currentRules.birthCounts.end(), 
                        liveNeighbors) != currentRules.birthCounts.end();
    }
}

void Simulation::Update()
{
    if(IsRunning())
    {
        // Check if it's time to mutate rules
        if (generationsSinceLastMutation >= mutationInterval) {
            MutateRules();
            generationsSinceLastMutation = 0;
        }
        
        // Apply current rules to update the grid
        for(int row = 0; row < grid.GetRows(); row++)
        {
            for(int column = 0; column < grid.GetColumns(); column++)
            {
                int liveNeighbors = CountLiveNeighbors(row, column);
                int cellValue = grid.GetValue(row, column);
                
                bool shouldLive = ShouldCellLive(liveNeighbors, cellValue == 1);
                tempGrid.SetValue(row, column, shouldLive ? 1 : 0);
            }
        }
        
        grid = tempGrid;
        generationCount++;
        generationsSinceLastMutation++;
    }
}

void Simulation::MutateRules()
{
    // Save current rules to history
    ruleHistory.push_back(currentRules);
    
    // Mutation strategies:
    // 1. Add or remove a survival count (30% chance)
    // 2. Add or remove a birth count (30% chance)
    // 3. Shift all counts by ±1 (20% chance)
    // 4. Completely randomize (20% chance)
    
    int mutationType = GetRandomValue(0, 9);
    
    if (mutationType < 3) {
        // Add or remove survival count
        if (GetRandomValue(0, 1) == 0 && currentRules.survivalCounts.size() > 1) {
            // Remove a random survival count
            int idx = GetRandomValue(0, currentRules.survivalCounts.size() - 1);
            currentRules.survivalCounts.erase(currentRules.survivalCounts.begin() + idx);
        } else {
            // Add a new survival count (0-8 neighbors)
            int newCount = GetRandomValue(0, 8);
            if (std::find(currentRules.survivalCounts.begin(), 
                         currentRules.survivalCounts.end(), 
                         newCount) == currentRules.survivalCounts.end()) {
                currentRules.survivalCounts.push_back(newCount);
                std::sort(currentRules.survivalCounts.begin(), currentRules.survivalCounts.end());
            }
        }
    }
    else if (mutationType < 6) {
        // Add or remove birth count
        if (GetRandomValue(0, 1) == 0 && currentRules.birthCounts.size() > 1) {
            // Remove a random birth count
            int idx = GetRandomValue(0, currentRules.birthCounts.size() - 1);
            currentRules.birthCounts.erase(currentRules.birthCounts.begin() + idx);
        } else {
            // Add a new birth count
            int newCount = GetRandomValue(0, 8);
            if (std::find(currentRules.birthCounts.begin(), 
                         currentRules.birthCounts.end(), 
                         newCount) == currentRules.birthCounts.end()) {
                currentRules.birthCounts.push_back(newCount);
                std::sort(currentRules.birthCounts.begin(), currentRules.birthCounts.end());
            }
        }
    }
    else if (mutationType < 8) {
        // Shift all counts
        int shift = GetRandomValue(0, 1) == 0 ? -1 : 1;
        
        for (int& count : currentRules.survivalCounts) {
            count = std::max(0, std::min(8, count + shift));
        }
        for (int& count : currentRules.birthCounts) {
            count = std::max(0, std::min(8, count + shift));
        }
        
        // Remove duplicates and sort
        std::sort(currentRules.survivalCounts.begin(), currentRules.survivalCounts.end());
        currentRules.survivalCounts.erase(
            std::unique(currentRules.survivalCounts.begin(), currentRules.survivalCounts.end()),
            currentRules.survivalCounts.end()
        );
        std::sort(currentRules.birthCounts.begin(), currentRules.birthCounts.end());
        currentRules.birthCounts.erase(
            std::unique(currentRules.birthCounts.begin(), currentRules.birthCounts.end()),
            currentRules.birthCounts.end()
        );
    }
    else {
        // Completely randomize rules
        currentRules.survivalCounts.clear();
        currentRules.birthCounts.clear();
        
        // Add 1-4 random survival counts
        int numSurvival = GetRandomValue(1, 4);
        for (int i = 0; i < numSurvival; i++) {
            int count = GetRandomValue(0, 8);
            if (std::find(currentRules.survivalCounts.begin(), 
                         currentRules.survivalCounts.end(), 
                         count) == currentRules.survivalCounts.end()) {
                currentRules.survivalCounts.push_back(count);
            }
        }
        
        // Add 1-3 random birth counts
        int numBirth = GetRandomValue(1, 3);
        for (int i = 0; i < numBirth; i++) {
            int count = GetRandomValue(0, 8);
            if (std::find(currentRules.birthCounts.begin(), 
                         currentRules.birthCounts.end(), 
                         count) == currentRules.birthCounts.end()) {
                currentRules.birthCounts.push_back(count);
            }
        }
        
        std::sort(currentRules.survivalCounts.begin(), currentRules.survivalCounts.end());
        std::sort(currentRules.birthCounts.begin(), currentRules.birthCounts.end());
    }
    
    // Ensure we have at least one rule
    if (currentRules.survivalCounts.empty()) {
        currentRules.survivalCounts.push_back(2);
    }
    if (currentRules.birthCounts.empty()) {
        currentRules.birthCounts.push_back(3);
    }
}

void Simulation::ResetRules()
{
    currentRules = LifeRules();
    ruleHistory.clear();
    generationCount = 0;
    generationsSinceLastMutation = 0;
}

void Simulation::ClearGrid()
{
    if(!IsRunning())
    {
        grid.Clear();
        generationCount = 0;
        generationsSinceLastMutation = 0;
    }
}

void Simulation::CreateRandomState()
{
    if(!IsRunning())
    {
        grid.FillRandom();
    }
}

void Simulation::ToggleCell(int row, int column)
{
    if(!IsRunning())
    {
        grid.ToggleCell(row, column);
    }
}
