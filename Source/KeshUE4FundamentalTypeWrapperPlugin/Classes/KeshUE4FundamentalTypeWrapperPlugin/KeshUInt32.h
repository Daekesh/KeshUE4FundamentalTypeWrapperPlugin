// Copyright 2014-2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma once

#include "KeshUInt32.generated.h"

#define PACKED
#pragma pack(push,1)

USTRUCT( BlueprintType )
struct KESHUE4FUNDAMENTALTYPEWRAPPERPLUGIN_API FKeshUInt32
{
	GENERATED_BODY()

	int32 Value;

	operator int32() const { return Value; }

	FKeshUInt32() { this->Value = 0; }
	FKeshUInt32( const int32& Value ) { this->Value = Value; }

};

#pragma pack(pop)
#undef PACKED
