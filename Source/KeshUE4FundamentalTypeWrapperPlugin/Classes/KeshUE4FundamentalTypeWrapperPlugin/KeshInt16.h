// Copyright 2014-2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma once

#include "KeshInt16.generated.h"

#define PACKED
#pragma pack(push,1)

USTRUCT( BlueprintType )
struct KESHUE4FUNDAMENTALTYPEWRAPPERPLUGIN_API FKeshInt16
{
	GENERATED_BODY()

	int16 Value;

	operator int16() const { return Value; }

	FKeshInt16() { this->Value = 0; }
	FKeshInt16( const int16& Value ) { this->Value = Value; }

};

#pragma pack(pop)
#undef PACKED
