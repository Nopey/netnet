#pragma once

import networkvar;

/// Generates a pair of getters (const and non-const) for a given NetworkVar field
#define NETWORKVAR_GETTERS( field )								\
	decltype(auto) get_##field() { return field.get( *this ); }	\
	decltype(auto) get_##field() const { return field; }
