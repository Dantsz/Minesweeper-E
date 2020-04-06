#pragma once
#include <vector>

namespace Empaerior
{

	//a vector that doesn't immediately delete an element when deletion is called
	//it's not advised to iterate upon and serves as just a container of data 
	//iteration is done throught the returned indexes of push_back
	//this class main pupose is to be a vector without iterator invalidation upon erasion
	template <typename T, typename indexing_type = size_t>
	class unsafe_vector
	{
	public:
		[[nodiscard]] indexing_type push_back(T object)
		{
			if (freed_indexes.empty())
			{
				objects.push_back(object);
				return objects.size() - 1;
				
			}
			else
			{
				std::cout << "d";
				indexing_type index = freed_indexes[freed_indexes.size() - 1];
				freed_indexes.pop_back();
				objects[index] = object;
				return index;

			}
		}

		void remove(indexing_type index)
		{
			
			freed_indexes.push_back(index);

		}

		T& at(indexing_type index)
		{
			return objects[index];
		}


		std::vector<T> objects;
		std::vector<indexing_type> freed_indexes;

	};

}