#include "Player.h"
#include <iostream>

Player::Player() {
	m_graphics = std::make_shared<PlayerGraphicsComponent>("mage");
	m_physics = std::make_shared<PhysicsComponent>();
	m_input = std::make_shared<InputComponent>();
	m_health = std::make_shared<HealthComponent>();
}

// Updates the player object.
void Player::Update(float timeDelta) {
	GameObject::Update(timeDelta);
}

// Returns the player's class.
PLAYER_CLASS Player::GetClass() const {
    return m_class;
}

// Set the player's health.
void Player::SetHealth(int healthValue)
{
	if (m_health == nullptr) return;

	m_health->SetHealth(healthValue);
}
