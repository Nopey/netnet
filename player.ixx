module;

#include <bitset>
#include <unordered_set>

#include "networkvar.h"

export module player;

import dirtyset;

export struct Player
{
	DirtySet dirtyset;

	// these two lines could be combined into one C macro, but then intellisense can't find the field.
	NetworkVar<int> x = 0;
	NETWORKVAR_GETTERS( x );
	NetworkVar<int> y = 0;
	NETWORKVAR_GETTERS( y );

	template <class Archive>
	void serialize( Archive &ar )
	{
		// must deserialize dirty bit before networkvar fields.
		ar( dirtyset );

		NETWORKVAR_MAYBESERIALIZE( ar, x );
		NETWORKVAR_MAYBESERIALIZE( ar, y );
	}
};
