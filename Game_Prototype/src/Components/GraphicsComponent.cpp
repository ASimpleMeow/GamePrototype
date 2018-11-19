#include "Components/GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent() :
m_animationSpeed(0),
m_isAnimated(false),
m_frameCount(0),
m_currentFrame(0),
m_frameWidth(0),
m_frameHeight(0),
m_timeDelta(0) {}

void GraphicsComponent::Draw(sf::RenderWindow &window, float timeDelta) {
	if (m_isAnimated) {
		m_timeDelta += timeDelta;
		if (m_timeDelta >= (1.f / m_animationSpeed)) {
			NextFrame();
			m_timeDelta = 0;
		}
	}

	window.draw(m_sprite);
}

bool GraphicsComponent::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed) {
	m_sprite.setTexture(texture);
	m_animationSpeed = frameSpeed;
	m_frameCount = frames;

	sf::Vector2u texSize = m_sprite.getTexture()->getSize();
	m_frameWidth = texSize.x / m_frameCount;
	m_frameHeight = texSize.y;

	if (frames > 1) {
		m_isAnimated = true;
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
	} else m_isAnimated = false;

	m_sprite.setOrigin(m_frameWidth / 2.f, m_frameHeight / 2.f);

	return true;
}

void GraphicsComponent::NextFrame() {
	if (m_currentFrame == (m_frameCount - 1)) m_currentFrame = 0;
	else m_currentFrame++;
	m_sprite.setTextureRect(sf::IntRect(m_frameWidth * m_currentFrame, 0, m_frameWidth, m_frameHeight));
}

sf::Sprite& GraphicsComponent::GetSprite() { return m_sprite; }

int GraphicsComponent::GetFrameCount() const { return m_frameCount; }

bool GraphicsComponent::IsAnimated() { return m_isAnimated; }

void GraphicsComponent::SetAnimated(bool isAnimated) { 
	m_isAnimated = isAnimated;

	if (isAnimated) m_currentFrame = 0;
	else m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}