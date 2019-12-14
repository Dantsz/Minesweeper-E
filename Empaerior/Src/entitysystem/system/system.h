#pragma once
#include <set>
#include <unordered_map>
#include "../Entity.h"
namespace Empaerior {
	//Thanks to 
	//"A system is any functionality that iterates upon a list of entities with a certain signature of components."
	//
	class System
	{
	public:
		//the id od the entities the systemworks on
		std::set<uint64_t> entities_id;

	};

	class SystemManager
	{
	public:
		template <typename T>
		std::shared_ptr<T>  register_system()
		{
			const char* system_type = typeid(T).name();
			try
			{
				//if the system is already present //  throw
				if (typetosystem.find(system_type) != typetosystem.end())
				{

					throw E_runtime_exception("Unable to register system: system is already registered.", __FILE__, __LINE__);

				}
				std::shared_ptr<T> system = std::make_shared<T>();
				typetosystem.insert({ system_type,system });

				return system;

			}
			catch (E_runtime_exception & e)
			{
				std::cout << e.what() << '\n';
			}
			



		}

		template<typename T>
		void set_signature(const std::vector<bool>& signature)
		{
			const char* system_type = typeid(T).name();	
			try
			{
				//if the system is not found  //throw
				if (typetosystem.find(system_type) == typetosystem.end())
				{
					throw E_runtime_exception("Unable to set the signature: system does not exist.", __FILE__, __LINE__);
				}
				
				typetosignature[system_type] = std::move(signature);


			}
			catch (E_runtime_exception & e)
			{
				std::cout << e.what() << '\n';
			}
		}

		//erase entity from all systems
		void OnEntityDestroy(Entity& entity)
		{
			for (auto const& it : typetosystem)
			{
				it.second->entities_id.erase(entity.id);
			}

		}

		// Notify each system that an entity's signature changed
		void OnEntitySignatureChange(Entity& entity,std::vector<bool>& signature)
		{
			for (auto const& it : typetosystem)
			{
				auto const& type = it.first;
				auto const& system = it.second;
				auto const& systemSignature = typetosignature[type];
				if (compare_signatures(signature,systemSignature))
				{
					system->entities_id.insert(entity.id);
				}
				else
				{
					system->entities_id.erase(entity.id);
				}

			}

		}

		//compare the signature//return 1  if ther are equal
		bool compare_signatures(const std::vector<bool>& signature1, const std::vector<bool>& signature2)
		{
			if (signature1.size() != signature2.size()) return false;
			for (int i = 0; i < signature1.size(); i++)
			{
				if (signature1[i] & signature2[i]) return false;
			}
			return true;
		}


	private:
		//get the signature of a system based on type
		std::unordered_map<const char*, std::vector<bool>> typetosignature;
		//get the system based on type
		std::unordered_map<const char*, std::shared_ptr<System>> typetosystem;

	};




}
