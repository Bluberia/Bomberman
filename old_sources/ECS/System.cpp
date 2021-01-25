#include "System.hpp"

template <typename ComponentType>
void ECS::System::addComponent()
{
	addRequiredComponent(typeid(ComponentType).hash_code());
}

void ECS::System::addRequiredComponent(std::size_t componentType)
{
	for (auto& i : _componentsRequired)
		if (i == componentType)
			return;
	_componentsRequired.push_back(componentType);
}
