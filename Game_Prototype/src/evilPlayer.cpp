#include "EvilPlayer.hpp"

EvilPlayer::EvilPlayer() {
	m_graphics = std::make_shared<PlayerGraphicsComponent>("mage");
	m_physics = std::make_shared<PhysicsComponent>();
	m_input = std::make_shared<InputComponent>();

	m_input->BindKey(InputComponent::KEY::KEY_LEFT, sf::Keyboard::Left);
	m_input->BindKey(InputComponent::KEY::KEY_RIGHT, sf::Keyboard::Right);
	m_input->BindKey(InputComponent::KEY::KEY_UP, sf::Keyboard::Up);
	m_input->BindKey(InputComponent::KEY::KEY_DOWN, sf::Keyboard::Down);
}

void EvilPlayer::Update(float timeDelta) {
	GameObject::Update(timeDelta);
}

void EvilPlayer::SetEvilState() {
	m_graphics->GetSprite().setColor(sf::Color::Red);
}