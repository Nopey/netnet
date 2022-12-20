module;
#include <unordered_set>
#include <limits>
#include <cstdint>
#include <cassert>
export module dirtyset;

typedef uint16_t dirtyoffset_t;
size_t const dirtyset_capacity = 100;

export class DirtySet
{
	std::unordered_set<dirtyoffset_t> set;
	bool all_dirty = false;

	dirtyoffset_t as_offset( size_t offset ) const;

public:
	void mark( size_t offset );
	bool is_dirty( size_t offset ) const;
	void reset( void );

	template<typename Archive>
	void serialize(Archive &ar)
	{
		ar( set, all_dirty );
	}
};

dirtyoffset_t DirtySet::as_offset( size_t offset ) const
{
	assert( offset <= std::numeric_limits<dirtyoffset_t>::max() );
	return static_cast<dirtyoffset_t>( offset );
}

void DirtySet::mark( size_t offset )
{
	if ( all_dirty || set.size() > dirtyset_capacity )
	{
		all_dirty = true;
		set.clear();
		return;
	}
	set.insert( as_offset( offset ) );
}

bool DirtySet::is_dirty( size_t offset ) const
{
	return all_dirty || set.contains( as_offset( offset ) );
}

void DirtySet::reset( void )
{
	all_dirty = false;
	set.clear();
}
