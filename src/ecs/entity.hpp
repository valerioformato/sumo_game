#pragma once

#include <string>
#include <optional>

namespace Sumo::Ecs
{
	class Entity
	{
		template<typename... Components>
		friend class EntityManager;

		explicit Entity(std::size_t id) :
			id_{ id }
		{

		}

		std::size_t id_;
	};

}