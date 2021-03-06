#include "GameObject.hpp"

GameObject::GameObject() {
	m_position = { 0,0 };
	m_influenceValue = 1.0f;
}

void GameObject::Update(float timeDelta) {
	if (m_input != nullptr) m_input->Update(*this);
	if (m_physics != nullptr) m_physics->Update(*this, timeDelta);
	if (m_graphics != nullptr) m_graphics->Update(*this, timeDelta);
}

void GameObject::Draw(sf::RenderWindow &window, float timeDelta) {
	if (m_graphics != nullptr) m_graphics->Draw(window, timeDelta);
}

void GameObject::SetPosition(sf::Vector2f position) {
	m_position = position;
	if (m_graphics != nullptr) m_graphics->GetSprite().setPosition(position);
}