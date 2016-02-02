// Copyright 2014-2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma once

#include "KeshDouble.generated.h"

#define PACKED
#pragma pack(push,1)

USTRUCT( BlueprintType )
struct KESHUE4FUNDAMENTALTYPEWRAPPERPLUGIN_API FKeshDouble
{
	GENERATED_BODY()

	double Value;

	operator double() const { return Value; }

	FKeshDouble() { this->Value = 0; }
	FKeshDouble( const double& Value ) { this->Value = Value; }

};

#pragma pack(pop)
#undef PACKED
