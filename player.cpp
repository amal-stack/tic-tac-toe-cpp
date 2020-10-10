#include <string>


class Player {
    std::string name_;
    int id_;
    int score_;

public:
    Player(std::string, int);
    const std::string& name() const;
    const int& id() const;
    const int& score() const;
    void add_score(const int&);
};

Player::Player(std::string name, int id) : name_(name), id_(id), score_(0)
{}

const int& Player::score() const { return score_; }

const int& Player::id() const { return id_; } 

const std::string& Player::name() const {return name_; }

void Player::add_score(const int& score) { score_ += score; }
