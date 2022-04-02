#pragma once
#include <vector>
#include <optional>
#include <cassert>
#include <string>

#include "entity.hpp"

namespace Sumo::Ecs
{
	template<typename... Components>
	class EntityManager;

	template<typename... Components>
	class MemoryPool
	{
		friend class EntityManager<Components...>;
		
		MemoryPool() = default; 

		template<typename Component>
		std::vector<std::optional<Component>>& get_component_vec()
		{
			return std::get<std::vector<std::optional<Component>>>(component_vectors);
		}

		template<typename Component>
		[[nodiscard]] std::optional<Component>& get_component(std::size_t const e_id)
		{
			return get_component_vec<Component>()[e_id];
		}

		void remove_entity(std::size_t const e_id, MemoryPool)
		{
			assert(valid_entities.size() > e_id);

			valid_entities[e_id] = false;
			removed.push_back(e_id);
		}

		[[nodiscard]] bool is_valid(std::size_t const e_id)
		{
			return valid_entities[e_id];
		}

		[[nodiscard]] std::string const& tag(std::size_t const e_id)
		{
			return tags[e_id];
		}

		[[nodiscard]] std::size_t add_entity(std::string const& tag);

		std::tuple<
			std::vector<std::optional<Components>>...
		> component_vectors;

		std::vector<std::string> tags;
		std::vector<bool> valid_entities;
		std::vector<std::size_t> removed;
		std::size_t components_end = 0;
	};

	template <typename ... Components>
	std::size_t MemoryPool<Components...>::add_entity(std::string const& tag)
	{
		if (removed.empty())
		{
			(get_component_vec<Components>().emplace_back(), ...);
			tags.push_back(tag);
			valid_entities.push_back(true);

			return components_end++;
		}
		else
		{
			auto const empty_spot = removed.back();
			removed.pop_back();

			(get_component<Components>(empty_spot).reset(), ...);
			valid_entities[empty_spot] = true;
			tags[empty_spot] = tag;

			return empty_spot;
		}
	}
}
