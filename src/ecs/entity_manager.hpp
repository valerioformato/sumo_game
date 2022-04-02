#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>

#include "entity.hpp"
#include "memory_pool.hpp"

namespace Sumo::Ecs
{
	template<typename... Components>
	class EntityManager
	{
	public:
		using entity_vec = std::vector<Entity>;

		EntityManager() = default;

		[[nodiscard]] entity_vec& get_by_tag(std::string const& tag)
		{
			return entities_map_[tag];
		}

		[[nodiscard]] entity_vec& get_all()
		{
			return all_entities_;
		}

		Entity add(std::string const& tag)
		{
			auto const e = Entity{memory_.add_entity(tag)};
			to_add_.push_back(e);
			return e;
		}

		[[nodiscard]] std::string const& tag(Entity const e)
		{
			return memory_.tag(e.id_);
		}

		[[nodiscard]] bool is_valid(Entity const e) const
		{
			return memory_.is_valid(e.id_);
		}

		void destroy(Entity const e) const
		{
			memory_.remove_entity(e.id_);
		}

		template<typename Component>
		void add_component(Entity const e, Component&& component)
		{
			memory_.get_component<Component>(e.id_).emplace(std::forward<Component>(component)); 
		}

		template<typename... EntityComponents>
		[[nodiscard]] bool has_component(Entity const e)
		{
			return (static_cast<bool>(memory_.get_component<EntityComponents>(e.id_)) && ...); 
		}

		template<typename Component>
		[[nodiscard]] std::optional<Component>& get_component(Entity const e)
		{
			return memory_.get_component<Component>(e.id_); 
		}

		void update();

	private:
		std::unordered_map<std::string, entity_vec> entities_map_;
		entity_vec all_entities_; 
		entity_vec to_add_;
		MemoryPool<Components...> memory_; 
	};

	template<typename... Components>
	void EntityManager<Components...>::update()
	{
		for (auto& e : to_add_)
		{
			entities_map_[tag(e)].push_back(e);
		}
		all_entities_.insert(all_entities_.end(), to_add_.begin(), to_add_.end());
		to_add_.clear();
		
		auto const can_be_removed = [&](auto const e){ return is_valid(e);}; 

		for (auto& [tag, vec] : entities_map_)
			std::erase_if(vec, can_be_removed);
		std::erase_if(all_entities_, can_be_removed); 
	}
}

