// Copyright 2014-2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma once

#include "KeshInt8.generated.h"

#define PACKED
#pragma pack(push,1)

USTRUCT( BlueprintType )
struct KESHUE4FUNDAMENTALTYPEWRAPPERPLUGIN_API FKeshInt8
{
	GENERATED_BODY()

	int8 Value;

	operator int8() const { return Value; }

	FKeshInt8() { this->Value = 0; }
	FKeshInt8( const int8& Value ) { this->Value = Value; }

};

#pragma pack(pop)
#undef PACKED
