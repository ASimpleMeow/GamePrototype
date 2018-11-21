#ifndef EvilPlayer_hpp
#define EvilPlayer_hpp

#include "GameObject.hpp"

class EvilPlayer : public GameObject {
public:
	EvilPlayer();
	void Update(float deltaTime);
	void SetEvilState();
};

#endif // !EvilPlayer_hpp

