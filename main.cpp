#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/unordered_set.hpp>
#include <sstream>
#include <iostream>

import player;

int main()
{
	std::stringstream buffer;

	{
		cereal::PortableBinaryOutputArchive archive( buffer );
		Player server;

		server.get_x() = 100; // need to use getter for mutations
		server.dirtyset.reset(); // reset the dirty bit to prevent x from being sent
		server.get_y() = 200;

		archive( server );

		// don't need to use getters here, we're just reading.
		std::cout << "server state: " << server.x << ", " << server.y << std::endl;
	}

	std::cout << buffer.tellp() << " bytes on the wire" << std::endl;

	// rewind stringstream
	buffer.clear();
	buffer.seekg( 0 );

	{
		cereal::PortableBinaryInputArchive archive( buffer );
		Player client;

		archive( client );

		std::cout << "resulting client state: " << client.x << ", " << client.y << std::endl;
	}

	return 0;
}
