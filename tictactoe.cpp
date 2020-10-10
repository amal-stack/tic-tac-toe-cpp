#include <iostream>
#include "player.cpp"
#include "grid.cpp"

class Game {
    Grid grid_;
    Player p1, p2, next_, *winner_;   
    bool over_;

public:
    Game(std::string& p1, std::string& p2);
    bool play(int, int);
    bool over() const;
    void reset();
    const Player* winner() const;
    const Player& next() const;
    const Grid& grid() const;
};

Game::Game(std::string& p1_name, std::string& p2_name):
p1(Player(p1_name, 1)), p2(Player(p2_name, 2)), next_(p1), over_(false), winner_(nullptr)
{}

bool Game::play(int x, int y) 
{
    //If game is over
    if(over_)  std::runtime_error("This game has ended!\n");
    
    //Set grid to the current player's symbol
    grid_.set(x, y, next_.name() == p1.name() ? 1 : 0); //FIXME: next is player
    std::cout << "\nDEBUG: " << grid_.has_won(x, y) << '\n'; 
    if(grid_.has_won(x, y)) 
    {
        winner_ = &next_;
        over_ = true;
        return true;
    }
    
    else 
    {
        if(grid_.is_full()) over_ = true;    
        next_ = next_.name() == p1.name() ? p2 : p1;
        return true;
    }
}

bool Game::over() const { return over_; }

const Player* Game::winner() const
{
    if(!over_) throw std::runtime_error("Winner undefined. Game has not ended yet.");
    return winner_;
}
const Player& Game::next() const 
{
    return next_;
}
void Game::reset()
{
    grid_ = Grid();
    over_ = false;
}
const Grid& Game::grid() const
{
    return grid_;
}

int main() 
{
    std::string name1, name2;
    

    do {
        int choice;

        std::cout << "1. Start a New Game\n"  
                  << "2. View Highscores\n"
                  << "Enter a choice:";

        std::cin >> choice;
        switch(choice) 
        {
        case 1: {                   
            std::cout << "Enter Player 1's name: ";
            std::cin >> name1;
            std::cout << "Enter Player 2's name: ";
            std::cin >> name2;

            Game g(name1, name2);
            std::cout << "Press Enter to Start!\n";
            std::cin.get();


            while(!g.over()) 
            {
                std::cout << g.grid();
                std::cout << g.next().name() << "'s Turn!\n";
                int x, y;

                std::cout << "Enter row and column:";
                std::cin >> x >> y;

                try 
                {               
                    g.play(x, y);    
                } 
                catch(std::exception& e) 
                {
                    std::cout << e.what();
                    continue;
                }

            }
            std::cout << g.grid();
            if(g.winner() == nullptr) std::cout << "Draw!!\n";
            else
            { 
               std::cout << (g.winner()->name()) << " has won the game\n";
 
            }
            break;
        }
        case 2:
        {
            throw std::runtime_error("Not Implemented");
        }
        
        default: exit(EXIT_SUCCESS);
        }
    } while (true);
}