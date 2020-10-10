#include <iostream>

class Grid {
    char grid[3][3];
    int set_count;
public:
    Grid();
    friend std::ostream& operator<<(std::ostream&, const Grid&) ;
    void set(int, int, int);
    bool is_set(int, int) const;
    bool has_won(int, int) const;
    bool is_full() const;
};

Grid::Grid() : set_count(0)
{
    for(auto& row : grid)
            for(auto& cell : row)
                cell = '_';
}
std::ostream& operator<<(std::ostream& out, const Grid& g)
{
    out << "-------------" << '\n';
    for(auto& row : g.grid)
    out << "| " << row[0] << " | " << row[1] << " | " << row[2] << " |"<< '\n';
    out << "-------------" << '\n';
}
void Grid::set(int row, int col, int p) 
{
    
    if(is_set(row, col)) throw std::runtime_error("Position already set");
    grid[row][col] = p ? 'X' : 'O'; //FIXME
    set_count++;

}
bool Grid::is_set(int x, int y) const
{
    return grid[x][y] != '_';
}
bool Grid::has_won(int x, int y) const
{
    if(x == y || x + y == 2) {
        if( (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != '_') ||  
            (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != '_') 
        ) 
            return true;
    } 
    return (grid[0][y] == grid[1][y] && grid[1][y] == grid[2][y] && grid[0][y] != '_') || 
           (grid[x][0] == grid[x][1] && grid[x][1] == grid[x][2] && grid[x][0] != '_');
}
bool Grid::is_full() const 
{
        return set_count >= 9;
}
