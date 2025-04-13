#include "pch.h"
#include "Ball.h"

Ball::Ball(float _size, int _WidthWindow, int _heightWindow, float _speed, sf::Vector2f _pos, sf::Vector2f _dir) : WidthWindow(_WidthWindow), heightWindow(_heightWindow), speed(_speed), pos(_pos), size(_size)
{
    dir = Normalize(_dir);
    Init();
}

Ball::~Ball()
{
}

void Ball::Init()
{
    ball.setRadius(size);
    float tempPosX = pos.x - size;
    float tempPosY = pos.y - size;
    ball.setPosition({ tempPosX, tempPosY });
    ball.setFillColor(sf::Color(100, 250, 50));
}

void Ball::Update()
{
    Move();
    sf::Vector2f circlepos;
    circlepos.x = pos.x - size;
    circlepos.y = pos.y - size;
    ball.setPosition(circlepos);
}

void Ball::Move()
{
    pos.x += dir.x * speed;
    pos.y += dir.y * speed;
    OutOfBound();
}

void Ball::Bounce()
{
}

bool Ball::OutOfBound()
{
    if (pos.x - size <= 0 || pos.x + size >= WidthWindow) {
        dir.x *= -1;
        return true;
    }
    if (pos.y - size <= 0 || pos.y + size >= heightWindow) {
        dir.y *= -1;
        return true;
    }
    return false;
}

sf::Vector2f Ball::Normalize(sf::Vector2f vect)
{
    vect.x /= vect.x + vect.y;
    vect.y /= vect.x + vect.y;
    return vect;

}

void Ball::setPos(sf::Vector2f _pos)
{
    pos = _pos;
}

void Ball::setDir(sf::Vector2f _dir)
{
    dir = _dir;
}