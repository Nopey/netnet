module;

#include <bitset>
#include <cstddef>

export module networkvar;

// Tracks field modifications in a `dirty` bitset on the Parent class
export template <typename Parent, size_t dirty_bit_index, typename T>
class NetworkVar
{
	T inner;

public:
	NetworkVar() = default;
	NetworkVar( T const &inner ) : inner( inner ) {}
	operator T const &() const
	{
		return inner;
	}

	T &get( Parent &parent )
	{
		parent.dirty[dirty_bit_index] = true;
		return inner;
	}

	template <class Archive>
	void maybe_serialize( Archive &archive, Parent const &parent )
	{
		if ( parent.dirty[dirty_bit_index] )
			archive( inner );
	}
};
