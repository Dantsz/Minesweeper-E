#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
//Typpes Defines
namespace Empaerior
{
	//BASIC TYPES
	//one byte interger
	using byte = uint8_t;
	//type compatible with SDL
	using u_int = uint32_t;
	using s_int = int32_t;
	//the type the engine works with 
	using u_inter = uint64_t;
	using s_inter = int64_t;
	using boole = bool;
	using ch = char;
	using fl_point = float;

	//OTHER TYPES

	//stl aliasses 
	//value tuple // 
	template <typename T, typename Y>
	using v_pair = std::pair<T, Y>;



	template <typename T>
	using vector = std::vector<T>;

	template <typename T>
	using queue = std::queue<T>;

	template < class key,                                    // unordered_map::key_type
		class value,                                      // unordered_map::mapped_type
		class Hash = std::hash<key>,                       // unordered_map::hasher
		class Pred = std::equal_to<key>,                   // unordered_map::key_equal
		class Alloc = std::allocator< std::pair<const key, value> >  // unordered_map::allocator_type
	>
		using hash_map = std::unordered_map < key, value, Hash, Pred, Alloc> ;

	using string = std::string;

}

//HASHING FOR STD::Pair
struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator() (const Empaerior::v_pair<T1, T2>& pair) const
	{
		return (std::hash<T1>()(pair.first) << 1) + std::hash<T1>()(pair.first) + std::hash<T2>()(pair.second);
	}
};

//INLINE DEFINE
#if defined(__clang__)
#define EMP_FORCEINLINE SDL_FORCE_INLINE
#elif defined(__GNUC__) || defined(__GNUG__)
#define EMP_FORCEINLINE SDL_FORCE_INLINE
#elif defined(_MSC_VER)
#define EMP_FORCEINLINE SDL_FORCE_INLINE
#endif