#ifndef Command_hpp
#define Command_hpp

#include "GameObject.hpp"
#include "Components/PhysicsComponent.hpp"
#include "Enums.hpp"

class GameObject;

class Command {
public:
	virtual ~Command() {}
	virtual void Execute(GameObject& obj) = 0;

protected:
	void Walk(GameObject& obj, sf::Vector2f newVelocity);
};

class AttackCommand : public Command {
	void Execute(GameObject& obj) {
		std::cout << "Attack Not Implemented" << std::endl;
	}
};

class WalkLeftCommand : public Command {
public:
	void Execute(GameObject& obj) { Walk(obj, { -WALK_ACCELERATION, 0 }); }
};

class WalkRightCommand : public Command {
public:
	void Execute(GameObject& obj) { Walk(obj, { WALK_ACCELERATION, 0 }); }
};

class WalkUpCommand : public Command {
public:
	void Execute(GameObject& obj) { Walk(obj, { 0, -WALK_ACCELERATION }); }
};

class WalkDownCommand : public Command {
public:
	void Execute(GameObject& obj) { Walk(obj, { 0, WALK_ACCELERATION }); }
};

#endif // !Command_hpp

