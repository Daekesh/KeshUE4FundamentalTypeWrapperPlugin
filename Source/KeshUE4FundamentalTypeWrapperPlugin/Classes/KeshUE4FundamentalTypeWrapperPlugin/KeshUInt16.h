// Copyright 2014-2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma once

#include "KeshUInt16.generated.h"

#define PACKED
#pragma pack(push,1)

USTRUCT( BlueprintType )
struct KESHUE4FUNDAMENTALTYPEWRAPPERPLUGIN_API FKeshUInt16
{
	GENERATED_BODY()

	uint16 Value;

	operator uint16() const { return Value; }

	FKeshUInt16() { this->Value = 0; }
	FKeshUInt16( const uint16& Value ) { this->Value = Value; }

};

#pragma pack(pop)
#undef PACKED
