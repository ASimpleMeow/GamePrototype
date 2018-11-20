//-------------------------------------------------------------------------------------
// Player.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"
#include "Components/HealthComponent.hpp"

//#include "Projectile.h"

class Player : public GameObject
{
public:
	/**
	 * Default constructor.
	 */
	Player();

	/**
	 * Updates the player object.
	 * The main purpose of this function is to update the players position.
	 * @param timeDelta The time, in MS, since the last game tick.
	 * @param level A reference to the level object.
	 */
    void Update(float timeDelta);//, Level& level);


	
	/**
	 * Set the player's health.
	 * @param healthValue The player's new health.
	 */
	void SetHealth(int healthValue);



	/**
	 * Gets the player's class.
	 * @return The player's class.
	 */
	PLAYER_CLASS GetClass() const;

private:

	/**
	* Components of the player
	*/
	std::shared_ptr<HealthComponent> m_health;
    
    /**
     * The player's class.
     */
    PLAYER_CLASS m_class;

};
#endif
