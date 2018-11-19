#include "Components/InuptComponent.hpp"

void InputComponent::BindKey(InputComponent::KEY key, sf::Keyboard::Key keyToBind) {
	m_keyMappings[key] = keyToBind;
}

void InputComponent::Update(GameObject& obj) {
	if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_LEFT])) m_keyLeftCommand->Execute(obj);
	else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_RIGHT])) m_keyRightCommand->Execute(obj);
	else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_UP])) m_keyUpCommand->Execute(obj);
	else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_DOWN])) m_keyDownCommand->Execute(obj);
	else if (sf::Keyboard::isKeyPressed(m_keyMappings[KEY::KEY_ATTACK])) m_keyAttackCommand->Execute(obj);
}