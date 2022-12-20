#pragma once

import networkvar;

/// Generates a pair of getters (const and non-const) for a given NetworkVar field
#define NETWORKVAR_GETTERS( field )							\
	decltype(auto) get_##field() const { return field; }	\
	decltype(auto) get_##field() { return field._get_networkvar_raw( *this, offsetof(std::remove_reference<decltype(*this)>::type, field) ); }

#define NETWORKVAR_MAYBESERIALIZE( ar, field )				\
	field.maybe_serialize( ar, *this, offsetof( std::remove_reference<decltype( *this )>::type, field ) )
