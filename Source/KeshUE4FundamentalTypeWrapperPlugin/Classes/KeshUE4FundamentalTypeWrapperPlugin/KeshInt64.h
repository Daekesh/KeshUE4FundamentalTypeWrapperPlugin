// Copyright 2014-2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma once

#include "KeshInt64.generated.h"

#define PACKED
#pragma pack(push,1)

USTRUCT( BlueprintType )
struct KESHUE4FUNDAMENTALTYPEWRAPPERPLUGIN_API FKeshInt64
{
	GENERATED_BODY()

	int64 Value;

	operator int64() const { return Value; }

	FKeshInt64() { this->Value = 0; }
	FKeshInt64( const int64& Value ) { this->Value = Value; }

};

#pragma pack(pop)
#undef PACKED
