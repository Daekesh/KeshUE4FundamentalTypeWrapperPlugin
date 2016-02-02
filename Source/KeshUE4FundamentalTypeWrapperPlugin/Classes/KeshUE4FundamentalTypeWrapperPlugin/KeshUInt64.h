// Copyright 2014-2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma once

#include "KeshUInt64.generated.h"

#define PACKED
#pragma pack(push,1)

USTRUCT( BlueprintType )
struct KESHUE4FUNDAMENTALTYPEWRAPPERPLUGIN_API FKeshUInt64
{
	GENERATED_BODY()

	uint64 Value;

	operator uint64() const { return Value; }

	FKeshUInt64() { this->Value = 0; }
	FKeshUInt64( const uint64& Value ) { this->Value = Value; }

};

#pragma pack(pop)
#undef PACKED
