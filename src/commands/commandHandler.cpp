
#include "commandHandler.h"

#include <iostream> // std::cout icin eklendi

std::unique_ptr<Command> CommandHandler::createNew(CommandType command, Paddle *paddle)
{
    if (paddle == nullptr)
    {
        throw std::invalid_argument("Paddle is null");
    }

    switch (command)
    {
    case CommandType::MOVEUP:
        return std::unique_ptr<Command>(new MoveUp(paddle));

    case CommandType::MOVEDOWN:
        return std::unique_ptr<Command>(new MoveDown(paddle));
    }

    return nullptr;
}

std::unique_ptr<Command> CommandHandler::createNew(CommandType command, Ball *ball)
{
    std::cerr << "CommandHandler::createNew(CommandType command, Ball* ball) " << std::endl;
    if (ball == nullptr)
    {
        throw std::invalid_argument("Ball is null");
    }

    switch (command)
    {
    case CommandType::MOVE:
        return std::unique_ptr<Command>(new MoveBall(ball));
    }

    return nullptr;
}

std::unique_ptr<Command> CommandHandler::createNew(CommandType command, float inSpeed, Ball *ball, Paddle *paddle1, Paddle *paddle2)
{
    if (ball == nullptr || paddle1 == nullptr || paddle2 == nullptr)
    {
        throw std::invalid_argument("Ball or paddle is null");
    }

    switch (command)
    {
    case CommandType::SETSPEED:
        return std::unique_ptr<Command>(new SetSpeed(inSpeed, ball, paddle1, paddle2));
    }

    return nullptr;
}
