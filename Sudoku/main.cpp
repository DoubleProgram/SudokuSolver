#include <iostream>
#include <array>

struct Cell{
    int number = 0;
    bool solved = false;
    int block = 0;
};

using Sudoku = std::array<std::array<Cell,9>,9>;

std::array<Cell,9> GetBlock(Sudoku& sudoku, int i);
bool SolveCell(Sudoku& sudoku,int& y, int& x);
bool CanPlace(const Sudoku& sudoku, int y, int x, int number);
void Print(const Sudoku& sudoku);

std::array<Cell,9> GetBlock(const Sudoku& sudoku, int i){
    if(i < 1 || i > 9)
        return std::array<Cell,9>();
    
    int j = 0;
    std::array<Cell, 9> ret;
    for(int x = 0; x < 9; x++)
        for(int y = 0; y < 9; y++)
            if(sudoku[y][x].block == i){
                ret[j] = sudoku[y][x];
                j++;
            }
   
    return ret;
}

int main(int argc, const char * argv[]) {
    Sudoku sudoku;
    
    {
        int tempSudoku[9][9] = {
            {0,3,0,0,6,0,0,5,0},
            {8,0,0,0,0,4,0,0,2},
            {0,0,0,2,0,1,0,0,0},
            {0,4,5,0,0,0,8,0,0},
            {9,0,0,0,0,0,0,0,1},
            {0,0,3,0,0,0,6,4,0},
            {0,0,0,1,0,7,0,0,0},
            {2,0,0,5,0,0,0,0,9},
            {0,1,0,0,8,0,0,6,0}
        };
        
        int index = 0;
        for(int x = 0; x < 9; x++){
           if(x % 3 != 0 && index != 0) index -= 3;
            for(int y = 0; y < 9; y++){
                if (y % 3 == 0) index++;
                sudoku[y][x].number = tempSudoku[x][y];
                sudoku[y][x].block = index;
                if(tempSudoku[x][y] != 0)
                    sudoku[y][x].solved = true;
            }
        }
    }
    Print(sudoku);
    int y = 0, x = 0;
    std::cout << (SolveCell(sudoku,y,x) ? "\nSuccess!\n" : "\nThe sudoku is not valid!\n") <<std::endl;
    Print(sudoku);
    return 0;
}

void Increment(int& y, int& x, bool& solved){
    if(y == 8 && x == 8)
        solved = true;
    else {
        y++;
        if (y % 9 == 0){
          y = 0;
          x++;
        }
    }
}

void Decrement(int& y, int& x){
    if (y == 0) {
       x--;
       y = 8;
    }
   else y--;
}

bool SolveCell(Sudoku& sudoku, int& y, int& x){
    static bool solved = false;
    
    Print(sudoku);
    for (int number = 1; number < 10; number++){
        if (sudoku[y][x].solved || CanPlace(sudoku,y,x,number)){
            if(!sudoku[y][x].solved)
              sudoku[y][x].number = number;
            Increment(y, x, solved);
            
            if(!solved)
                SolveCell(sudoku, y, x);
            
            if(solved)
                return true;
            
            if(!sudoku[y][x].solved)
                sudoku[y][x].number = 0;
            
            Decrement(y,x);
            
            if (sudoku[y][x].solved)
                return false;
        }
    }
    if(!solved)
        return false;
    return true;
}
    
bool CanPlace(const Sudoku& sudoku, int y, int x, int number){
    std::array<Cell,9> block = GetBlock(sudoku, sudoku[y][x].block);
    
    for(const Cell& c : block)
        if(number == c.number)
            return false;
    
    for(int x2 = 0; x2 < 9; x2++)
        if(sudoku[y][x2].number == number)
            return false;
    
    for(int y2 = 0; y2 < 9; y2++)
        if(sudoku[y2][x].number == number)
            return false;
    
    return true;
}

void Print(const Sudoku& sudoku){
    std::cout << "\n-------------------" << std::endl;
    for(int x = 0; x < 9; x++){
        for(int y = 0; y < 9; y++){
            std::cout << "|" << sudoku[y][x].number;
            if(y == 8) std::cout << "|" << std::endl;
        }
        if((x+1) % 3 == 0)
          std::cout << "-------------------" << std::endl;
    }
}
