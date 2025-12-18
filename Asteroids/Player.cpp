#include "Player.h"
#include "Bullet.h"
#include "Global.h"
#include "Game.h"
#include "Asteroid.h"
#include "Physics.h"
#include "collision.h"

Player::Player()
	: Entity(sf::Vector2f(600, 450), 0), array(sf::LinesStrip, 5), shootTimer() {
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
	
	shootSound.setBuffer(Game::soundBuffers["shoot"]);
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

	//Check if player is moving forward
	bool forward = sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	//If the player is moving forward:
	if (forward)
	{
		//Increase playerSpeed by acceleration
		playerSpeed += acceleration * deltaTime;
		if (playerSpeed > maxSpeed) playerSpeed = maxSpeed;
	}
	else
	{
		//Slow player down if not moving forward
		playerSpeed -= deceleration * deltaTime;
		if (playerSpeed < 0.0f) playerSpeed = 0.0f;
	}

	//Forward movement functionality
	if (playerSpeed > 0.0f) {
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
		shootSound.play(); //Play shoot sound when shooting bullet

		shootTimer = shootDelay; //Reset shoot timer

		float radians = angle * (M_PI / 180.0f);

		//Create bullet and add to toAddList
		Game::toAddList.push_back(new Bullet(position, sf::Vector2f(cos(radians), sin(radians))));
	}

	sf::Transform playerTransform = sf::Transform().translate(position).rotate(angle);


	//Asteroid collision
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (typeid(*entities[i]) == typeid(Asteroid))
		{
			Asteroid* asteroid = dynamic_cast<Asteroid*>(entities[i]); //Create asteroid pointer to current entity

			if (asteroid->getLife() < asteroidHitTime)
			{
				continue;
			}

			sf::Transform asteroidTransform = sf::Transform()
				.translate(asteroid->position)
				.rotate(asteroid->angle);

			//Check for intersection between bullet and asteroid polygon
			if (collision::intersects(collision::getTransformed(array, playerTransform),
				collision::getTransformed(asteroid->getVertexArray(), asteroidTransform)))
			{
				Game::gameOver();
			}
		}
	}

}

//Draw player to screen
void Player::render(sf::RenderWindow& window) {
	window.draw(array, sf::Transform().translate(position).rotate(angle));
}