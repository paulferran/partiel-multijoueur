#pragma once
class Ball
{
public:
    Ball(float size, int _WidthWindow, int _heightWindow, float speed, sf::Vector2f pos, sf::Vector2f _dir);
    ~Ball();
    void Init();
    void Update();
    void Move();
    void Bounce();
    bool OutOfBound();
    sf::Vector2f Normalize(sf::Vector2f vect);
    void setPos(sf::Vector2f _pos);
    void setDir(sf::Vector2f _dir);
    sf::CircleShape GetShape() { return ball; }
    sf::Vector2f GetPos() { return pos; }

private:
    sf::CircleShape ball;
    sf::Vector2f pos;
    sf::Vector2f dir;
    int WidthWindow;
    int heightWindow;
    float speed;
    float size;
};