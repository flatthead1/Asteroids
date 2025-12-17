#include "Player.h"
#include "Bullet.h"
#include "Global.h"
#include "Game.h"
#include "Asteroid.h"

Player::Player()
	: Entity(sf::Vector2f(500, 500), 0), array(sf::LinesStrip, 5), shootTimer() {
	//Making player shape
	array[0].position = sf::Vector2f(20, 0);
	array[1].position = sf::Vector2f(-30, -20);
	array[2].position = sf::Vector2f(-15, 0);
	array[3].position = sf::Vector2f(-30, 20);
	array[4].position = array[0].position;

	//Make player white
	for (size_t i = 0; i < array.getVertexCount(); i++) {
		array[i].color = sf::Color::White;
	}
}

void Player::update(float deltaTime) {
	//Decrease shootTimer by deltaTime for every frame
	shootTimer -= deltaTime;

	//Turn left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		angle -= turnSpeed * deltaTime;
	}

	//Turn right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		angle += turnSpeed * deltaTime;
	}

	//Move forward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		float radians = angle * (M_PI / 180.0f); //Convert degrees to radians

		//Move player forward in direction they're facing
		position.x += cos(radians) * playerSpeed * deltaTime;
		position.y += sin(radians) * playerSpeed * deltaTime;

		//Keep player bound to inside screen
		position.x = std::min(std::max(position.x, playerWidth / 2.0f),
			screenWidth - playerWidth / 2.0f);
		position.y = std::min(std::max(position.y, playerHeight / 2.0f),
			screenHeight - playerHeight / 2.0f);
	}

	//Shoot bullets
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0.0f) 
	{
		shootTimer = shootDelay;

		float radians = angle * (M_PI / 180.0f);

		Game::toAddList.push_back(new Bullet(position, sf::Vector2f(cos(radians), sin(radians))));
	}

	sf::Transform playerTransform = sf::Transform().translate(position).rotate(angle);
}

void Player::render(sf::RenderWindow& window) {
	window.draw(array, sf::Transform().translate(position).rotate(angle));
}