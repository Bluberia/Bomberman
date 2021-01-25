#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Components/Score.hpp"

namespace ECS {
	namespace Systems {
		class UpdateScore : public ECS::System
		{
			void tick(ECS::World &world, float deltaTime);
		};

	}
}
