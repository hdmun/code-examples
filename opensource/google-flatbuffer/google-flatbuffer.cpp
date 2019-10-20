#include <iostream>
#include "protocol/user_generated.h"

uint8_t* serialize(flatbuffers::FlatBufferBuilder& fbb)
{
	auto fbb_offset = protocol::CreateuserDirect(fbb, "id_data", "name_data");
	fbb.Finish(fbb_offset);
	return fbb.GetBufferPointer();
}

void deserialize(const uint8_t* buf)
{
	const protocol::user* userData = protocol::Getuser(buf);
	std::cout << "deserialize " << userData->name()->str() << ", " << userData->id()->str() << std::endl;
}

int main()
{
	flatbuffers::FlatBufferBuilder fb;
	uint8_t* buf = serialize(fb);
	
	deserialize(buf);
}
