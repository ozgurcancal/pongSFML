

#include "gameScreen.h"
#include <thread>
#include <chrono>

GameScreen::GameScreen(sf::RenderWindow &window, std::shared_ptr<Paddle> &paddle1, std::shared_ptr<Paddle> &paddle2, std::shared_ptr<Ball> &ball, std::shared_ptr<CommandHandler> &commendHandler) : m_paddle1(paddle1.get()), m_paddle2(paddle2.get()), m_ball(ball.get()), m_commandHandler(commendHandler.get())
{
}

void GameScreen::refreshScreen(sf::RenderWindow &window)
{
    m_ball->reset(window);
    m_paddle1->reset(window);
    m_paddle2->reset(window);
}

void GameScreen::draw(sf::RenderWindow &window)
{
    window.clear();
    window.draw(m_paddle1->getSprite());
    window.draw(m_paddle2->getSprite());
    window.draw(m_ball->getSprite());
    drawScore(window);
    window.display();

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    handleCollision(m_paddle1->getSprite(), m_paddle2->getSprite(), m_ball->getSprite(), window);
}

void GameScreen::handleBallOffScreen(sf::RenderWindow &window, std::function<void(const std::string &)> &switchScreenCallback)
{
    if (m_ball->getSprite().getPosition().x < 0)
    {
        m_ScoreY++;
        refreshScreen(window);
    }
    else if (m_ball->getSprite().getPosition().x > 800)
    {
        m_ScoreX++;
        refreshScreen(window);
    }
    else if (m_ScoreX == 5 || m_ScoreY == 5)
    {
        m_ScoreX = 0;
        m_ScoreY = 0;
        switchScreenCallback("GameOverScreen");
    }

    m_scores[0] = std::to_string(m_ScoreX);
    m_scores[1] = std::to_string(m_ScoreY);
    sf::Text item;

    for (int i = 0; i < m_scores.size(); ++i)
    {
        item.setFont(m_font);
        item.setString(m_scores[i]);
        item.setCharacterSize(50);
        item.setFillColor(sf::Color::White);
        item.setPosition(window.getSize().x / 2 - 75 + (150 * i), 30.f);
        m_scoreItems[i] = item;
    }
}

void GameScreen::drawScore(sf::RenderWindow &window)
{

    for (auto &item : m_scoreItems)
    {
        window.draw(item);
    }
}

void GameScreen::handleCollision(sf::Sprite &spritePaddle1, sf::Sprite &spritePaddle2, sf::Sprite &spriteBall, sf::RenderWindow &window)
{

    sf::FloatRect rectSprite1 = spritePaddle1.getGlobalBounds();
    sf::FloatRect rectSprite2 = spritePaddle2.getGlobalBounds();
    sf::FloatRect rectBall = spriteBall.getGlobalBounds();

    // Reverse the ball's X direction when it collides with one of the paddles
    if (rectBall.intersects(rectSprite1))
    {
        m_ball->setVelocityX(m_ball->getVelocityX() * -1);
    }
    else if (rectBall.intersects(rectSprite2))
    {
        m_ball->setVelocityX(m_ball->getVelocityX() * -1);
    }

    auto drawBounce = [&spritePaddle1, &spritePaddle2, &window]()
    {
        window.clear();
        window.draw(spritePaddle1);
        window.draw(spritePaddle2);
        window.display();
    };

    // create a bounce
    if (rectSprite1.top <= BOUNDRY_TOP)
    {
        spritePaddle1.move(0, MOVE_DISTANCE);
        drawBounce();
    }
    else if (rectSprite1.top + rectSprite1.height >= BOUNDRY_BOTTOM)
    {
        spritePaddle1.move(0, -MOVE_DISTANCE);
        drawBounce();
    }

    if (rectSprite2.top <= BOUNDRY_TOP)
    {
        spritePaddle2.move(0, MOVE_DISTANCE);
        drawBounce();
    }
    else if (rectSprite2.top + rectSprite2.height >= BOUNDRY_BOTTOM)
    {
        spritePaddle2.move(0, -MOVE_DISTANCE);
        drawBounce();
    }
}
