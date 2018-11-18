#include "utils.h"
#include "Entity.h"

// Default constructor.
Entity::Entity() :
m_currentTextureIndex(static_cast<int>(ANIMATION_STATE::WALK_DOWN)),
m_health(0),
m_maxHealth(0),
m_speed(0),
m_velocity({0.f, 0.f})
{
}

// Override the default Object::Update function.
void Entity::Update(float timeDelta)
{
    // Choose animation state.
    ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);
    
    if ((m_velocity.x != 0) || (m_velocity.y != 0))
    {
        if (abs(m_velocity.x) > abs(m_velocity.y))
        {
            if (m_velocity.x <= 0)
            {
                animState = ANIMATION_STATE::WALK_LEFT;
            }
            else
            {
                animState = ANIMATION_STATE::WALK_RIGHT;
            }
        }
        else
        {
            if (m_velocity.y <= 0)
            {
                animState = ANIMATION_STATE::WALK_UP;
            }
            else
            {
                animState = ANIMATION_STATE::WALK_DOWN;
            }
        }
    }
    
    // Set animation speed.
    if ((m_velocity.x == 0) && (m_velocity.y == 0))
    {
        // The character is still.
        if (IsAnimated())
        {
            // Update sprite to idle version.
            m_currentTextureIndex += 4;
            
            // Stop movement animations.
            SetAnimated(false);
        }
    }
    else
    {
        // The character is moving.
        if (!IsAnimated())
        {
            // Update sprite to walking version.
            m_currentTextureIndex -= 4;
            
            // Start movement animations.
            SetAnimated(true);
        }
    }
    
    // Set the sprite.
    if (m_currentTextureIndex != static_cast<int>(animState))
    {
        m_currentTextureIndex = static_cast<int>(animState);
        m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
    }
}

// Gets the entities health.
int Entity::GetHealth() const
{
    return m_health;
}


