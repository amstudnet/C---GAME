#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace sf;
using namespace std;

int main() {
	 
    RenderWindow window(VideoMode(800, 600), "10911235 trash");
    window.setFramerateLimit(70);//fps

 
  	//字體 
    Font arial;
    arial.loadFromFile("Arial.ttf");
	//分數 
    int score = 0;
    ostringstream ssScore;
    ssScore << "Score: " << score;
    //分數字體設置 
    Text Score;
    Score.setFont(arial);
    Score.setCharacterSize(30);
    Score.setPosition(0.f, window.getSize().y / 2);
    Score.setString(ssScore.str());

    int health = 3;

    ostringstream ssHealth;
    ssHealth << "Health: " << health;

    Text Health;
    Health.setFont(arial);
    Health.setCharacterSize(30);
    Health.setPosition(0.f, (window.getSize().y / 2 + 35));
    Health.setString(ssHealth.str());

    Text gameOver;
    gameOver.setFont(arial);
    gameOver.setFillColor(Color::Red);
    gameOver.setCharacterSize(60);
    gameOver.setPosition(window.getSize().x / 4, window.getSize().y / 2);
    gameOver.setString("you are noob qq");

    CircleShape fruit;
    fruit.setRadius(20.f);
    fruit.setFillColor(Color::Green);
    fruit.setPosition(Vector2f(rand() % (window.getSize().x - (int)(2 * fruit.getRadius())), 10.f));

    RectangleShape player;
    player.setSize(Vector2f(100.f, 50.f));
    player.setFillColor(Color::Red);
    player.setPosition(Vector2f(window.getSize().x / 2 - player.getSize().x / 2, window.getSize().y - player.getSize().y));

    bool isMovingLeft = false;
    bool isMovingRight = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::R)) {
             score = 0;
        health = 3;
        ssScore.str("");
        ssScore << "Score: " << score;
        Score.setString(ssScore.str());
        ssHealth.str("");
        ssHealth << "Health: " << health;
        Health.setString(ssHealth.str());
         fruit.setPosition(Vector2f(static_cast<float>(rand() % static_cast<int>(window.getSize().x - 2 * fruit.getRadius())), 10.f));
        }
       
        if(health==0){
        	 fruit.setPosition(Vector2f(fruit.getPosition().x, fruit.getPosition().y));
        	 player.setPosition(Vector2f(player.getPosition().x, player.getPosition().y));
		}
		else{
			// Move player
			 if (Keyboard::isKeyPressed(Keyboard::Left)) {
            isMovingLeft = true;
            isMovingRight = false;
        } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            isMovingLeft = false;
            isMovingRight = true;
        } else {
            isMovingLeft = false;
            isMovingRight = false;
        }

        if (isMovingLeft && player.getPosition().x > 0) {
            player.move(-5.f, 0.f);
        }

        if (isMovingRight && player.getPosition().x + player.getSize().x < window.getSize().x) {
            player.move(5.f, 0.f);
        }
		// Move fruit
        fruit.move(0.f, 5.f);	
		}
        

        // Check collisions
        if (fruit.getPosition().y + 2 * fruit.getRadius() >= window.getSize().y) {
            // Fruit missed
            fruit.setPosition(Vector2f(static_cast<float>(rand() % static_cast<int>(window.getSize().x - 2 * fruit.getRadius())), 10.f));

            health--;

            ssHealth.str("");
            ssHealth << "Health: " << health;
            Health.setString(ssHealth.str());

            if (health == 0) {
                fruit.setPosition(fruit.getPosition().x, fruit.getPosition().y); 
            }
        }

        if (fruit.getGlobalBounds().intersects(player.getGlobalBounds())) {
            // Fruit caught
            fruit.setPosition(Vector2f(static_cast<float>(rand() % static_cast<int>(window.getSize().x - 2 * fruit.getRadius())), 10.f));

            score++;

            ssScore.str("");
            ssScore << "Score: " << score;
            Score.setString(ssScore.str());
        }

        // Draw
        window.clear(Color::Black);
        window.draw(fruit);
        window.draw(Score);
        window.draw(Health);
        window.draw(player);

        if (health == 0) {
            window.draw(gameOver);
        }

        window.display();
    }

    return 0;
}

