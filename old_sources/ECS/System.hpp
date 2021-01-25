#ifndef INDIE_STUDIO_SYSTEM_HPP
#define INDIE_STUDIO_SYSTEM_HPP

#include <vector>

namespace ECS {
	class World;
}

namespace ECS {
	class System {
	public:
		virtual void tick(ECS::World &world, float deltaTime) = 0;
		template <typename ComponentType>
		void addComponent();

	private:

		void addRequiredComponent(std::size_t componentType);

	private:
		std::vector<std::size_t> _componentsRequired;
	};
}

#endif //INDIE_STUDIO_SYSTEM_HPP
