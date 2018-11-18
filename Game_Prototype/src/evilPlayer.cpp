//
//  evilPlayer.cpp
//  AssetManagerv1
//
//  Created by Denis Flynn on 16/10/2018.
//  Copyright © 2018 Denis Flynn. All rights reserved.
//

#include "evilPlayer.hpp"
void evilPlayer::Update(float timeDelta)
{
    m_timeDelta = timeDelta;
    // Calculate movement speed based on the timeDelta since the last update.
    sf::Vector2f movementSpeed(0.f, 0.f);
    sf::Vector2f previousPosition = m_position;
    
    // Calculate where the current movement will put us.
    ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);
    
    if (Input::IsKeyPressed(Input::KEY::KEY_E_LEFT))
    {
        // Set movement speed.
        movementSpeed.x = -m_speed * timeDelta;
        
        // Chose animation state.
        animState = ANIMATION_STATE::WALK_LEFT;
    }
    else if (Input::IsKeyPressed(Input::KEY::KEY_E_RIGHT))
    {
        // Set movement speed.
        movementSpeed.x = m_speed * timeDelta;
        
        // Chose animation state.
        animState = ANIMATION_STATE::WALK_RIGHT;
    }
    
    if (Input::IsKeyPressed(Input::KEY::KEY_E_UP))
    {
        // Set movement speed.
        movementSpeed.y = -m_speed * timeDelta;
        
        // Chose animation state.
        animState = ANIMATION_STATE::WALK_UP;
    }
    else if (Input::IsKeyPressed(Input::KEY::KEY_E_DOWN))
    {
        // Set movement speed.
        movementSpeed.y = m_speed * timeDelta;
        
        // Chose animation state.
        animState = ANIMATION_STATE::WALK_DOWN;
    }
    
    // Calculate horizontal movement.
    
    
    {
        m_position.x += movementSpeed.x;
        // std::cout <<"player ="<<movementSpeed.x<<std::endl;
    }
    
    // Calculate horizontal movement.
    
    
    {
        m_position.y += movementSpeed.y;
    }
    
    // update the sprite position
    m_sprite.setPosition(m_position);
    
    // Set the sprite.
    if (m_currentTextureIndex != static_cast<int>(animState))
    {
        m_currentTextureIndex = static_cast<int>(animState);
        m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
        //m_sprite.setColor(sf::Color::Red); //"evil" version
    }
    
    // set animation speed
    if ((movementSpeed.x == 0) && (movementSpeed.y == 0))
    {
        // the character is still
        if (IsAnimated())
        {
            // Update sprite to idle version.
            // In our enum we have 4 walking sprites followed by 4 idle sprites.
            // Given this, we can simply add 4 to a walking sprite to get its idle counterpart.
            m_currentTextureIndex += 4;
            m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
            
            // Stop movement animations.
            SetAnimated(false);
        }
    }
    else
    {
        // the character is moving
        if (!IsAnimated())
        {
            // Update sprite to walking version.
            m_currentTextureIndex -= 4;
            m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
            
            // Start movement animations.
            SetAnimated(true);
        }
    }
    
    
}
