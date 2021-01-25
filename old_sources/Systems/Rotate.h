#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Components/Transform.hpp"

namespace ECS {
	namespace Systems {
		class Rotate: public ECS::System
		{
			void tick(ECS::World &world, float deltaTime);
		};

	}
}
