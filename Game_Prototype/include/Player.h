#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"
#include "Components/HealthComponent.hpp"

class Player : public GameObject {
public:
	Player();
    void Update(float timeDelta);
	void SetHealth(int healthValue);
	PLAYER_CLASS GetClass() const;

private:
	std::shared_ptr<HealthComponent> m_health;
    PLAYER_CLASS m_class;

};
#endif
