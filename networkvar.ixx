module;

#include <bitset>
#include <cstddef>

export module networkvar;

// Reports field modifications in the Parent class's dirtyset
export template <typename T>
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

	template<typename Parent>
	T &_get_networkvar_raw( Parent &parent, size_t offset )
	{
		parent.dirtyset.mark( offset );
		return inner;
	}

	template <typename Archive, typename Parent>
	void maybe_serialize( Archive &archive, Parent const &parent, size_t offset )
	{
		if ( parent.dirtyset.is_dirty( offset ) )
			archive( inner );
	}
};
