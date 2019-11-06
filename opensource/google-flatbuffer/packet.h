#pragma once
#include "flatbuffers/flatbuffers.h"

namespace packet {

class Serializer
{
public:
	Serializer();
	virtual ~Serializer();

	template<typename T, typename... _Args>
	void Pack( T* t, const _Args&&... args )
	{
	}

	template< typename T >
	void Pack( const T* data )
	{
	}

private:
	std::vector<uint8_t> buffer_;
	flatbuffers::FlatBufferBuilder builder_;
};


class Deserializer
{
public:
	Deserializer();
	Deserializer( const uint8_t* buffer, uint32_t size );
	virtual ~Deserializer();

	template<typename T>
	const T* UnPack()
	{
		flatbuffers::Verifier verifier( buffer_.data(), buffer_.size() );
		bool ok = verifier.VerifyBuffer<T>( nullptr );
		if ( !ok ) {
			__noop;  // throw exception
		}
		return flatbuffers::GetRoot<T>( buffer_.data() );
	}

private:
	std::vector<uint8_t> buffer_;
};

}  // end of namespace packet
