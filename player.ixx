module;

#include <bitset>

#include "networkvar.h"

export module player;

export struct Player
{
	enum class DirtyBit: size_t {
		Position,
		Count
	};

	typedef Player ThisClass;
	// typedef BaseClass;
	std::bitset<(size_t)DirtyBit::Count> dirty;

	// these two lines could be combined into one C macro, but then intellisense can't find the field.
	NetworkVar<ThisClass, (size_t)DirtyBit::Position, int> x = 0;
	NETWORKVAR_GETTERS( x );
	NetworkVar<ThisClass, (size_t)DirtyBit::Position, int> y = 0;
	NETWORKVAR_GETTERS( y );

	template <class Archive>
	void serialize( Archive &ar )
	{
		// must deserialize dirty bit before networkvar fields.
		ar( dirty );

		x.maybe_serialize( ar, *this );
		y.maybe_serialize( ar, *this );
	}
};
