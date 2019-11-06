#include <streambuf>
#include <fstream>
#include <sstream>
#include <iostream>

#include <utility>
#include <string>
#include <vector>

#include "packet.h"
#include "protocol/version_generated.h"
#include "protocol/monster_generated.h"


namespace test {

void version()
{
	packet::Serializer serializer__;

	flatbuffers::FlatBufferBuilder builder__;
	auto version = protocol::CreateVersion( builder__, 1, 3 );
	builder__.Finish( version );
	std::cout << "Version buffer size: " << builder__.GetSize() << std::endl;

	{
		const uint8_t* buf = builder__.GetBufferPointer();
		const uint32_t size = builder__.GetSize();

		packet::Deserializer deserializer__( buf, size );
		auto unpack_ver = deserializer__.UnPack<protocol::Version>();
		std::cout << "Version major: " << unpack_ver->major() << ", minor: " << unpack_ver->minor() << std::endl;
	}
}

flatbuffers::Offset<protocol::Monster> monster_create( flatbuffers::FlatBufferBuilder& builder )
{
	auto weapon_one_name = builder.CreateString( "Sword" );
	short weapon_one_damage = 3;
	auto weapon_two_name = builder.CreateString( "Axe" );
	short weapon_two_damage = 5;

	// Use the `CreateWeapon` shortcut to create Weapons with all the fields set.
	auto sword = protocol::CreateWeapon( builder, weapon_one_name, weapon_one_damage );
	auto axe = protocol::CreateWeapon( builder, weapon_two_name, weapon_two_damage );

	// Serialize a name for our monster, called "Orc".
	auto name = builder.CreateString( "Orc" );
	// Create a `vector` representing the inventory of the Orc. Each number
	// could correspond to an item that can be claimed after he is slain.
	unsigned char treasure[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto inventory = builder.CreateVector( treasure, 10 );

	// Place the weapons into a `std::vector`, then convert that into a FlatBuffer `vector`.
	std::vector<flatbuffers::Offset<protocol::Weapon>> weapons_vector;
	weapons_vector.push_back( sword );
	weapons_vector.push_back( axe );
	auto weapons = builder.CreateVector( weapons_vector );

	protocol::Vec3 points[] = { protocol::Vec3( 1.0f, 2.0f, 3.0f ), protocol::Vec3( 4.0f, 5.0f, 6.0f ) };
	auto path = builder.CreateVectorOfStructs( points, 2 );

	// Create the position struct
	auto position = protocol::Vec3( 1.0f, 2.0f, 3.0f );
	// Set his hit points to 300 and his mana to 150.
	int hp = 300;
	int mana = 150;
	// Finally, create the monster using the `CreateMonster` helper function
	// to set all fields.
	auto orc = protocol::CreateMonster( builder,
		999999999,
		name,
		hp,
		mana,
		1,
		false,
		& position,
		inventory,
		protocol::Color_Red,
		weapons,
		protocol::Equipment_Weapon,
		axe.Union(),
		path );

	// Call `Finish()` to instruct the builder that this monster is complete.
	// Note: Regardless of how you created the `orc`, you still need to call
	// `Finish()` on the `FlatBufferBuilder`.
	return orc;
}

void monster()
{
	flatbuffers::FlatBufferBuilder builder;
	auto orc = monster_create( builder );
	builder.Finish(orc); // You could also call `FinishMonsterBuffer(builder,
						 //                                          orc);`.

	{
		std::cout << "Monster buffer size: " << builder.GetSize() << std::endl;

		// This must be called after `Finish()`.
		uint8_t* buf = builder.GetBufferPointer();
		int size = builder.GetSize(); // Returns the size of the buffer that
									  // `GetBufferPointer()` points to.

		packet::Deserializer deserializer__( buf, size );
		auto monster = deserializer__.UnPack<protocol::Monster>();
		// Note: root object pointers are NOT the same as `buffer_pointer`.
		// `GetMonster` is a convenience function that calls `GetRoot<Monster>`,
		// the latter is also available for non-root types.

		auto hp = monster->hp();
		auto mana = monster->mana();
		auto name = monster->name()->c_str();
		std::cout << "Monster hp: " << hp << std::endl;
		std::cout << "Monster mana: " << mana << std::endl;
		std::cout << "Monster name: " << name << std::endl;

		auto pos = monster->pos();
		auto x = pos->x();
		auto y = pos->y();
		auto z = pos->z();
		std::cout << "Monster pos.x: " << x << std::endl;
		std::cout << "Monster pos.y: " << y << std::endl;
		std::cout << "Monster pos.z: " << z << std::endl;

		auto inv = monster->inventory(); // A pointer to a `flatbuffers::Vector<>`.
		auto inv_len = inv->Length();
		auto third_item = inv->Get( 2 );

		auto weapons = monster->weapons(); // A pointer to a `flatbuffers::Vector<>`.
		auto weapon_len = weapons->Length();
		auto second_weapon_name = weapons->Get( 1 )->name()->str();
		auto second_weapon_damage = weapons->Get( 1 )->damage();

		auto union_type = monster->equipped_type();
		if ( union_type == protocol::Equipment_Weapon ) {
			auto weapon = static_cast<const protocol::Weapon*>(monster->equipped()); // Requires `static_cast`
																		   // to type `const Weapon*`.
			auto weapon_name = weapon->name()->str(); // "Axe"
			auto weapon_damage = weapon->damage();    // 5
		}
	}
}

namespace file {

void write()
{
	flatbuffers::FlatBufferBuilder builder__;
	auto orc = monster_create( builder__ );
	builder__.Finish( orc );

	const uint8_t* buf = builder__.GetBufferPointer();
	const uint32_t size = builder__.GetSize();

	std::ofstream ofile( "monster.bin", std::ios::binary );
	ofile.write( (char*)buf, size );
	ofile.close();
}

void read()
{
	const std::string filename = "monster.bin";
	std::ifstream read_file( filename, std::ios_base::binary );

	std::istreambuf_iterator<char> file_iter( read_file );
	std::vector<char> buffer_(
		file_iter, {}
	);

	uint8_t* buf = reinterpret_cast<uint8_t*>( buffer_.data() );
	uint32_t size = static_cast<uint32_t>( buffer_.size() );
	packet::Deserializer deserializer__( buf, size );

	auto monster = deserializer__.UnPack<protocol::Monster>();
	std::cout << "Monster id: " << monster->id() << std::endl;
	std::cout << "Monster name: " << monster->name()->c_str() << std::endl << std::endl;
	std::cout << "Monster hp: " << monster->hp() << std::endl;
	std::cout << "Monster mana: " << monster->mana() << std::endl;
	std::cout << "Monster exp: " << monster->exp() << std::endl;
	std::cout << "Monster boss: " << monster->boss() << std::endl;

	auto pos = monster->pos();
	std::cout << "Monster pos.x: " << pos->x() << std::endl;
	std::cout << "Monster pos.y: " << pos->y() << std::endl;
	std::cout << "Monster pos.z: " << pos->z() << std::endl;
}

}  // end of namespace file
}  // end of namespace test


int main()
{
// 	test::version();
// 	test::monster();
	test::file::write();
	test::file::read();
	return 0;
}
