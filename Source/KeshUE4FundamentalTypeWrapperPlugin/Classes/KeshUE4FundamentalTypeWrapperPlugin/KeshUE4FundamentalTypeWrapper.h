// Copyright 2014-2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma once

#include "KeshUE4FundamentalTypeWrapperPlugin/KeshUE4FundamentalTypeWrapperDefines.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshDouble.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshInt8.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshInt16.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshUInt16.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshUInt32.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshInt64.h"
#include "KeshUE4FundamentalTypeWrapperPlugin/KeshUInt64.h"
#include "KeshUE4FundamentalTypeWrapper.generated.h"


UCLASS( ClassGroup = "Kesh|CPP UE4FundamentalType Wrapper", BlueprintType )
class KESHUE4FUNDAMENTALTYPEWRAPPERPLUGIN_API UKeshUE4FundamentalTypeWrapper : public UObject
{
	GENERATED_BODY()

public:

	UKeshUE4FundamentalTypeWrapper( const class FObjectInitializer& ObjectInitializer );

	/************/
	/* Creators */
	/************/

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types", BlueprintPure, DisplayName = "Create Double" )
	static FKeshDouble CreateDouble( float Value )
	{
		return { static_cast< double >( Value ) };
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types", BlueprintPure, DisplayName = "Create int64" )
	static FKeshInt64 CreateInt64( int32 Value )
	{
		return { static_cast< int64 >( Value ) };
	}

	// The low value is the first 31 bits. The high mid value is bits 32 to 62. The high value is the last bit.
	UFUNCTION( Category = "Kesh|UE4 Fundamental Types", BlueprintPure, DisplayName = "Create Int 64 Full" )
	static FKeshInt64 CreateInt64Full( bool bNegative, int32 Low, int32 Mid, uint8 High )
	{
		if ( bNegative )
			return -static_cast< int64 >( Low > 0 ? Low : 0 ) -
			( static_cast< int64 >( Mid > 0 ? Mid : 0 ) << 31 ) -
			( static_cast< int64 >( ( High > 0 ? High : 0 ) & 1 ) << 62 );

		else
			return static_cast< int64 >( Low > 0 ? Low : 0 ) +
			( static_cast< int64 >( Mid > 0 ? Mid : 0 ) << 31 ) +
			( static_cast< int64 >( ( High > 0 ? High : 0 ) & 1 ) << 62 );
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types", BlueprintPure, DisplayName = "Create UInt 64" )
	static FKeshUInt64 CreateUInt64( int32 Value )
	{
		return { static_cast< uint64 >( Value ) };
	}

	// The low value is the first 31 bits. The high mid value is bits 32 to 62. The high value is the last 2 bits.
	UFUNCTION( Category = "Kesh|UE4 Fundamental Types", BlueprintPure, DisplayName = "Create UInt 64 Full" )
	static FKeshInt64 CreateUInt64Full( int32 Low, int32 Mid, uint8 High )
	{
		return static_cast< uint64 >( Low > 0 ? Low : 0 ) +
			( static_cast< uint64 >( Mid > 0 ? Mid : 0 ) << 31 ) +
			( static_cast< uint64 >( ( High > 0 ? High : 0 ) & 3 ) << 62 );
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types", BlueprintPure, DisplayName = "Create UInt 32" )
	static FKeshUInt32 CreateUInt32( int32 Value )
	{
		return { static_cast< uint16 >( Value ) };
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types", BlueprintPure, DisplayName = "Create Int 16" )
	static FKeshInt16 CreateInt16( int32 Value )
	{
		return { static_cast< int16 >( Value ) };
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types", BlueprintPure, DisplayName = "Create UInt 16" )
	static FKeshUInt16 CreateUInt16( int32 Value )
	{
		return { static_cast< uint16 >( Value ) };
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types", BlueprintPure, DisplayName = "Create Int 8" )
	static FKeshInt8 CreateInt8( int32 Value )
	{
		return { static_cast< int8 >( Value ) };
	}


	/*************/
	/* Extractors */
	/*************/

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Extractor", BlueprintPure, DisplayName = "double #")
		static void ExtractDouble(const FKeshDouble& D, float& F)
	{
		F = static_cast< float >(D.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Extractor", BlueprintPure, DisplayName = "int64 #")
		static void ExtractInt64(const FKeshInt64& I64, int32& I32)
	{
		I32 = static_cast< int32 >(I64.Value);
	}

	// Low is the first 31 bits. Mid is bits 32 to 62. High is the last bit.
	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Extractor", BlueprintPure, DisplayName = "int64 #F")
		static void ExtractInt64Full(const FKeshInt64& I64, bool& bNegative, int32& Low, int32& Mid, uint8& High)
	{
		bNegative = I64.Value < 0;
		Low = (bNegative ? -I64.Value : I64.Value) & 0x7FFFFFFF;
		Mid = ((bNegative ? -I64.Value : I64.Value) >> 31) & 0x7FFFFFFF;
		High = ((bNegative ? -I64.Value : I64.Value) >> 62) & 0x1;
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Extractor", BlueprintPure, DisplayName = "uint64 #")
		static void ExtractUInt64(const FKeshUInt64& UI64, int32& I32)
	{
		I32 = static_cast< int32 >(UI64.Value & 0x7FFFFFFF);
	}

	// Low is the first 31 bits. Mid is bits 32 to 62. High is the last two bits.
	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Extractor", BlueprintPure, DisplayName = "uint64 #F")
		static void ExtractUInt64Full(const FKeshUInt64& UI64, int32& Low, int32& Mid, uint8& High)
	{
		Low = UI64.Value & 0x7FFFFFFF;
		Mid = (UI64.Value >> 31) & 0x7FFFFFFF;
		High = (UI64.Value >> 62) & 0x3;
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Extractor", BlueprintPure, DisplayName = "uint32 #")
		static void ExtractUInt32(const FKeshUInt32& UI32, int32& I32)
	{
		I32 = static_cast< int32 >(UI32.Value & 0x7FFFFFFF);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Extractor", BlueprintPure, DisplayName = "uint32 #")
		static void ExtractUInt32Full(const FKeshUInt32& UI32, int32& I32, uint8& HighBit)
	{
		I32 = static_cast< int32 >(UI32.Value & 0x7FFFFFFF);
		HighBit = UI32.Value >> 31;
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Extractor", BlueprintPure, DisplayName = "int16 #")
		static void ExtractInt16(const FKeshInt16& I16, int32& I32)
	{
		I32 = static_cast< int32 >(I16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Extractor", BlueprintPure, DisplayName = "uint16 #")
		static void ExtractUInt16(const FKeshUInt16& UI16, int32& I32)
	{
		I32 = static_cast< int32 >(UI16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Extractor", BlueprintPure, DisplayName = "int8 #")
		static void ExtractInt8(const FKeshInt8& I8, int32& I32)
	{
		I32 = static_cast< int32 >(I8.Value);
	}

	
	/************/
	/*   Cast   */
	/************/
	/* String */

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int64 (String)")
		static FKeshInt64 StringToInt64(FString Value)
	{
		return { static_cast< int64 >(FCString::Atoi64(*Value)) };
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To String (int64)")
		static FString KeshUE4FTInt64ToString(FKeshInt64 Data)
	{
		return FString::Printf(TEXT("%lld)"), Data.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Double (String)")
		static FKeshDouble StringToDouble(FString Value)
	{
		return { static_cast< double >(FCString::Atod(*Value)) };
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To String (Double)")
		static FString DoubleToString(FKeshDouble Data)
	{
		return FString::Printf(TEXT("%lld)"), Data.Value);
	}



	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Double (float)")
		static float CastDoubleToFloat(const FKeshDouble& D)
	{
		return static_cast< float >(D.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To float (Double)")
		static FKeshDouble CastFloatToDouble(float F)
	{
		return static_cast< double >(F);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Double (int64)")
		static FKeshInt64 CastDoubleToInt64(const FKeshDouble& D)
	{
		return static_cast< int64 >(D.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int64 (Double)")
		static FKeshDouble CastInt64ToDouble(const FKeshInt64& I64)
	{
		return static_cast< double >(I64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Double (uInt64)")
		static FKeshUInt64 CastDoubleToUInt64(const FKeshDouble& D)
	{
		return static_cast< uint64 >(D.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt64 (Double)")
		static FKeshDouble CastUInt64ToDouble(const FKeshUInt64& UI64)
	{
		return static_cast< double >(UI64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Double (int32)")
		static int32 CastDoubleToInt32(const FKeshDouble& D)
	{
		return static_cast< int32 >(D.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int32 (Double)")
		static FKeshDouble CastInt32ToDouble(FKeshUInt32 I32)
	{
		return static_cast< double >(I32);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Double (uint32)")
		static FKeshUInt32 CastDoubleToUInt32(const FKeshDouble& D)
	{
		return static_cast< uint32 >(D.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt32 (Double)")
		static FKeshDouble CastUInt32ToDouble(const FKeshUInt32& UI32)
	{
		return static_cast< double >(UI32.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Double (Int16)")
		static FKeshInt16 CastDoubleToInt16(const FKeshDouble& D)
	{
		return static_cast< int16 >(D.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int16 (Double)")
		static FKeshDouble CastInt16ToDouble(const FKeshInt16& I16)
	{
		return static_cast< double >(I16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Double (uint16)")
		static FKeshUInt16 CastDoubleToUInt16(const FKeshDouble& D)
	{
		return static_cast< uint16 >(D.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt16 (Double)")
		static FKeshDouble CastUInt16ToDouble(const FKeshUInt16& UI16)
	{
		return static_cast< double >(UI16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Double (int8)")
		static FKeshInt8 CastDoubleToInt8(const FKeshDouble& D)
	{
		return static_cast< int8 >(D.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int8 (Double)")
		static FKeshDouble CastInt8ToDouble(const FKeshInt8& I8)
	{
		return static_cast< double >(I8.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Double (uint8)")
		static uint8 CastDoubleToUInt8(const FKeshDouble& D)
	{
		return static_cast< uint8 >(D.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt8 (Double)")
		static FKeshDouble CastUInt8ToDouble(uint8 UI8)
	{
		return static_cast< double >(UI8);
	}

	/* float */

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To float (int64)")
		static FKeshInt64 CastFloatToInt64(float F)
	{
		return static_cast< int64 >(F);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int64 (float)")
		static float CastInt64ToFloat(const FKeshInt64& I64)
	{
		return static_cast< float >(I64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To float (uInt64)")
		static FKeshUInt64 CastFloatToUInt64(float F)
	{
		return static_cast< uint64 >(F);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt64 (float)")
		static float CastUInt64ToFloat(const FKeshUInt64& UI64)
	{
		return static_cast< float >(UI64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To float (int32)")
		static int32 CastFloatToInt32(float F)
	{
		return static_cast< int32 >(F);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int32 (float)")
		static float CastInt32ToFloat(int32 I32)
	{
		return static_cast< float >(I32);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To float (uint32)")
		static FKeshUInt32 CastFloatToUInt32(float F)
	{
		return static_cast< uint32 >(F);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt32 (float)")
		static float CastUInt32ToFloat(const FKeshUInt32& UI32)
	{
		return static_cast< float >(UI32.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To float (Int16)")
		static FKeshInt16 CastFloatToInt16(float F)
	{
		return static_cast< int16 >(F);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int16 (float)")
		static float CastInt16ToFloat(const FKeshInt16& I16)
	{
		return static_cast< float >(I16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To float (uint16)")
		static FKeshUInt16 CastFloatToUInt16(float F)
	{
		return static_cast< uint16 >(F);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt16 (float)")
		static float CastUInt16ToFloat(const FKeshUInt16& UI16)
	{
		return static_cast< float >(UI16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To float (int8)")
		static FKeshInt8 CastFloatToInt8(float F)
	{
		return static_cast< int8 >(F);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int8 (float)")
		static float CastInt8ToFloat(const FKeshInt8& I8)
	{
		return static_cast< float >(I8.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To float (uint8)")
		static uint8 CastFloatToUInt8(float F)
	{
		return static_cast< uint8 >(F);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt8 (float)")
		static float CastUInt8ToFloat(uint8 UI8)
	{
		return static_cast< float >(UI8);
	}

	/* Int 64 */

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int64 (uInt64)")
		static FKeshUInt64 CastInt64ToUInt64(const FKeshInt64& I64)
	{
		return static_cast< uint64 >(I64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt64 (int64)")
		static FKeshInt64 CastUInt64ToInt64(const FKeshUInt64& UI64)
	{
		return static_cast< int64 >(UI64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int64 (int32)")
		static int32 CastInt64ToInt32(const FKeshInt64& I64)
	{
		return static_cast< int32 >(I64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int32 (int64)")
		static FKeshInt64 CastInt32ToInt64(int32 I32)
	{
		return static_cast< int64 >(I32);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int64 (uint32)")
		static FKeshUInt32 CastInt64ToUInt32(const FKeshInt64& I64)
	{
		return static_cast< uint32 >(I64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt32 (int64)")
		static FKeshInt64 CastUInt32ToInt64(const FKeshUInt32& UI32)
	{
		return static_cast< int64 >(UI32.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int64 (Int16)")
		static FKeshInt16 CastInt64ToInt16(const FKeshInt64& I64)
	{
		return static_cast< int16 >(I64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int16 (int64)")
		static FKeshInt64 CastInt16ToInt64(const FKeshInt16& I16)
	{
		return static_cast< int64 >(I16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int64 (uint16)")
		static FKeshUInt16 CastInt64ToUInt16(const FKeshInt64& I64)
	{
		return static_cast< uint16 >(I64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt16 (int64)")
		static FKeshInt64 CastUInt16ToInt64(const FKeshUInt16& UI16)
	{
		return static_cast< int64 >(UI16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int64 (int8)")
		static FKeshInt8 CastInt64ToInt8(const FKeshInt64& I64)
	{
		return static_cast< int8 >(I64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int8 (int64)")
		static FKeshInt64 CastInt8ToInt64(const FKeshInt8& I8)
	{
		return static_cast< int64 >(I8.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int64 (uint8)")
		static uint8 CastInt64ToUInt8(const FKeshInt64& I64)
	{
		return static_cast< uint8 >(I64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt8 (int64)")
		static FKeshInt64 CastUInt8ToInt64(uint8 UI8)
	{
		return static_cast< int64 >(UI8);
	}

	/* UInt 64 */

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt64 (int32)")
		static int32 CastUInt64ToInt32(const FKeshUInt64& UI64)
	{
		return static_cast< int32 >(UI64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int32 (uInt64)")
		static FKeshUInt64 CastInt32ToUInt64(int32 I32)
	{
		return static_cast< uint64 >(I32);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt64 (uint32)")
		static FKeshUInt32 CastUInt64ToUInt32(const FKeshUInt64& UI64)
	{
		return static_cast< uint32 >(UI64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt32 (uInt64)")
		static FKeshUInt64 CastUInt32ToUInt64(const FKeshUInt32& UI32)
	{
		return static_cast< uint64 >(UI32.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt64 (Int16)")
		static FKeshInt16 CastUInt64ToInt16(const FKeshUInt64& UI64)
	{
		return static_cast< int16 >(UI64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int16 (uInt64)")
		static FKeshUInt64 CastInt16ToUInt64(const FKeshInt16& I16)
	{
		return static_cast< uint64 >(I16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt64 (uint16)")
		static FKeshUInt16 CastUInt64ToUInt16(const FKeshUInt64& UI64)
	{
		return static_cast< uint16 >(UI64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt16 (uInt64)")
		static FKeshUInt64 CastUInt16ToUInt64(const FKeshUInt16& UI16)
	{
		return static_cast< uint64 >(UI16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt64 (int8)")
		static FKeshInt8 CastUInt64ToInt8(const FKeshUInt64& UI64)
	{
		return static_cast< int8 >(UI64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int8 (uInt64)")
		static FKeshUInt64 CastInt8ToUInt64(const FKeshInt8& I8)
	{
		return static_cast< uint64 >(I8.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt64 (uint8)")
		static uint8 CastUInt64ToUInt8(const FKeshUInt64& UI64)
	{
		return static_cast< uint8 >(UI64.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt8 (uInt64)")
		static FKeshUInt64 CastUInt8ToUInt64(uint8 UI8)
	{
		return static_cast< uint64 >(UI8);
	}

	/* Int 32 */

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int32 (uint32)")
		static FKeshUInt32 CastInt32ToUInt32(int32 I32)
	{
		return static_cast< uint32 >(I32);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt32 (int32)")
		static int32 CastUInt32ToInt32(const FKeshUInt32& UI32)
	{
		return static_cast< int32 >(UI32.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int32 (Int16)")
		static FKeshInt16 CastInt32ToInt16(int32 I32)
	{
		return static_cast< int16 >(I32);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int16 (int32)")
		static int32 CastInt16ToInt32(const FKeshInt16& I16)
	{
		return static_cast< int32 >(I16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int32 (uint16)")
		static FKeshUInt16 CastInt32ToUInt16(int32 I32)
	{
		return static_cast< uint16 >(I32);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt16 (int32)")
		static int32 CastUInt16ToInt32(const FKeshUInt16& UI16)
	{
		return static_cast< int32 >(UI16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int32 (int8)")
		static FKeshInt8 CastInt32ToInt8(int32 I32)
	{
		return static_cast< int8 >(I32);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int8 (int32)")
		static int32 CastInt8ToInt32(const FKeshInt8& I8)
	{
		return static_cast< int32 >(I8.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int32 (uint8)")
		static uint8 CastInt32ToUInt8(int32 I32)
	{
		return static_cast< uint8 >(I32);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt8 (int32)")
		static int32 CastUInt8ToInt32(uint8 UI8)
	{
		return static_cast< int32 >(UI8);
	}

	/* UInt 32 */

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt32 (Int16)")
		static FKeshInt16 CastUInt32ToInt16(const FKeshUInt32& UI32)
	{
		return static_cast< int16 >(UI32.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int16 (uint32)")
		static FKeshUInt32 CastInt16ToUInt32(const FKeshInt16& I16)
	{
		return static_cast< uint32 >(I16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt32 (uint16)")
		static FKeshUInt16 CastUInt32ToUInt16(const FKeshUInt32& UI32)
	{
		return static_cast< uint16 >(UI32.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt16 (uint32)")
		static FKeshUInt32 CastUInt16ToUInt32(const FKeshUInt16& UI16)
	{
		return static_cast< uint32 >(UI16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt32 (int8)")
		static FKeshInt8 CastUInt32ToInt8(const FKeshUInt32& UI32)
	{
		return static_cast< int8 >(UI32.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int8 (uint32)")
		static FKeshUInt32 CastInt8ToUInt32(const FKeshInt8& I8)
	{
		return static_cast< uint32 >(I8.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt32 (uint8)")
		static uint8 CastUInt32ToUInt8(const FKeshUInt32& UI32)
	{
		return static_cast< uint8 >(UI32.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt8 (uint32)")
		static FKeshUInt32 CastUInt8ToUInt32(uint8 UI8)
	{
		return static_cast< uint32 >(UI8);
	}

	/* Int 16 */

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int16 (uint16)")
		static FKeshUInt16 CastInt16ToUInt16(const FKeshInt16& I16)
	{
		return static_cast< uint16 >(I16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt16 (Int16)")
		static FKeshInt16 CastUInt16ToInt16(const FKeshUInt16& UI16)
	{
		return static_cast< int16 >(UI16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int16 (int8)")
		static FKeshInt8 CastInt16ToInt8(const FKeshInt16& I16)
	{
		return static_cast< int8 >(I16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int8 (Int16)")
		static FKeshInt16 CastInt8ToInt16(const FKeshInt8& I8)
	{
		return static_cast< int16 >(I8.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To Int16 (uint8)")
		static uint8 CastInt16ToUInt8(const FKeshInt16& I16)
	{
		return static_cast< uint8 >(I16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt8 (Int16)")
		static FKeshInt16 CastUInt8ToInt16(uint8 UI8)
	{
		return static_cast< int16 >(UI8);
	}

	/* UInt 16 */

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt16 (int8)")
		static FKeshInt8 CastUInt16ToInt8(const FKeshUInt16& UI16)
	{
		return static_cast< int8 >(UI16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int8 (uint16)")
		static FKeshUInt16 CastInt8ToUInt16(const FKeshInt8& I8)
	{
		return static_cast< uint16 >(I8.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt16 (uint8)")
		static uint8 CastUInt16ToUInt8(const FKeshUInt16& UI16)
	{
		return static_cast< uint8 >(UI16.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt8 (uint16)")
		static FKeshUInt16 CastUInt8ToUInt16(uint8 UI8)
	{
		return static_cast< uint16 >(UI8);
	}

	/* Int 8 */

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To int8 (uint8)")
		static uint8 CastInt8ToUInt8(const FKeshInt8& I8)
	{
		return static_cast< uint8 >(I8.Value);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Cast", BlueprintPure, DisplayName = "To UInt8 (int8)")
		static FKeshInt8 CastUInt8ToInt8(uint8 UI8)
	{
		return static_cast< int8 >(UI8);
	}


	/********/
	/* Plus */
	/********/

	/* Double */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl + dbl" )
	static FKeshDouble KeshUE4FTDoublePlusDouble( const FKeshDouble& D1, const FKeshDouble& D2 )
	{
		return D1.Value + D2.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl + flt" )
	static FKeshDouble KeshUE4FTDoublePlusFloat( const FKeshDouble& D, float F )
	{
		return D.Value + F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt + dbl" )
	static FKeshDouble KeshUE4FTFloatPlusDouble( float F, const FKeshDouble& D )
	{
		return F + D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl + int64" )
	static FKeshDouble KeshUE4FTDoublePlusInt64( const FKeshDouble& D, const FKeshInt64& I64 )
	{
		return D.Value + I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 + dbl" )
	static FKeshDouble FKeshInt64PlusDouble( const FKeshInt64& I64, const FKeshDouble& D )
	{
		return I64.Value + D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl + uint64" )
	static FKeshDouble KeshUE4FTDoublePlusUInt64( const FKeshDouble& D, const FKeshUInt64& UI64 )
	{
		return D.Value + UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 + dbl" )
	static FKeshDouble KeshUE4FTUInt64PlusDouble( const FKeshUInt64& UI64, const FKeshDouble& D )
	{
		return UI64.Value + D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl + int32" )
	static FKeshDouble KeshUE4FTDoublePlusInt32( const FKeshDouble& D, int32 I32 )
	{
		return D.Value + I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 + dbl" )
	static FKeshDouble KeshUE4FTInt32PlusDouble( int32 I32, const FKeshDouble& D )
	{
		return I32 + D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl + uint32" )
	static FKeshDouble KeshUE4FTDoublePlusUInt32( const FKeshDouble& D, const FKeshUInt32& UI32 )
	{
		return D.Value + UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 + dbl" )
	static FKeshDouble FKeshUInt32PlusDouble( const FKeshUInt32& UI32, const FKeshDouble& D )
	{
		return UI32.Value + D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl + int16" )
	static FKeshDouble KeshUE4FTDoublePlusInt16( const FKeshDouble& D, const FKeshInt16& I16 )
	{
		return D.Value + I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 + dbl" )
	static FKeshDouble FKeshInt16PlusDouble( const FKeshInt16& I16, const FKeshDouble& D )
	{
		return I16.Value + D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl + uint16" )
	static FKeshDouble KeshUE4FTDoublePlusUInt16( const FKeshDouble& D, const FKeshUInt16& UI16 )
	{
		return D.Value + UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 + dbl" )
	static FKeshDouble FKeshUInt16PlusDouble( const FKeshUInt16& UI16, const FKeshDouble& D )
	{
		return UI16.Value + D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl + int8" )
	static FKeshDouble KeshUE4FTDoublePlusInt8( const FKeshDouble& D, const FKeshInt8& I8 )
	{
		return D.Value + I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 + dbl" )
	static FKeshDouble FKeshInt8PlusDouble( const FKeshInt8& I8, const FKeshDouble& D )
	{
		return I8.Value + D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl + uint8" )
	static FKeshDouble KeshUE4FTDoublePlusUInt8( const FKeshDouble& D, uint8 UI8 )
	{
		return D.Value + UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 + dbl" )
	static FKeshDouble KeshUE4FTUInt8PlusDouble( uint8 UI8, const FKeshDouble& D )
	{
		return UI8 + D.Value;
	}

	/* float */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt + int64" )
	static float KeshUE4FTFloatPlusInt64( float F, const FKeshInt64& I64 )
	{
		return F + I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 + flt" )
	static float FKeshInt64PlusFloat( const FKeshInt64& I64, float F )
	{
		return I64.Value + F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt + uint64" )
	static float KeshUE4FTFloatPlusUInt64( float F, const FKeshUInt64& UI64 )
	{
		return F + UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 + flt" )
	static float KeshUE4FTUInt64PlusFloat( const FKeshUInt64& UI64, float F )
	{
		return UI64.Value + F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt + uint32" )
	static float KeshUE4FTFloatPlusUInt32( float F, const FKeshUInt32& UI32 )
	{
		return F + UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 + flt" )
	static float FKeshUInt32PlusFloat( const FKeshUInt32& UI32, float F )
	{
		return UI32.Value + F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt + int16" )
	static float KeshUE4FTFloatPlusInt16( float F, const FKeshInt16& I16 )
	{
		return F + I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 + flt" )
	static float FKeshInt16PlusFloat( const FKeshInt16& I16, float F )
	{
		return I16.Value + F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt + uint16" )
	static float KeshUE4FTFloatPlusUInt16( float F, const FKeshUInt16& UI16 )
	{
		return F + UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 + flt" )
	static float FKeshUInt16PlusFloat( const FKeshUInt16& UI16, float F )
	{
		return UI16.Value + F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt + int8" )
	static float KeshUE4FTFloatPlusInt8( float F, const FKeshInt8& I8 )
	{
		return F + I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 + flt" )
	static float FKeshInt8PlusFloat( const FKeshInt8& I8, float F )
	{
		return I8.Value + F;
	}

	/* Int 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 + int64" )
	static FKeshInt64 FKeshInt64PlusInt64( const FKeshInt64& I641, const FKeshInt64& I642 )
	{
		return I641.Value + I642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 + uint64" )
	static FKeshInt64 FKeshInt64PlusUInt64( const FKeshInt64& I64, const FKeshUInt64& UI64 )
	{
		return I64.Value + UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 + int64" )
	static FKeshInt64 KeshUE4FTUInt64PlusInt64( const FKeshUInt64& UI64, const FKeshInt64& I64 )
	{
		return UI64.Value + I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 + int32" )
	static FKeshInt64 FKeshInt64PlusInt32( const FKeshInt64& I64, int32 I32 )
	{
		return I64.Value + I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 + int64" )
	static FKeshInt64 KeshUE4FTInt32PlusInt64( int32 I32, const FKeshInt64& I64 )
	{
		return I32 + I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 + uint32" )
	static FKeshInt64 FKeshInt64PlusUInt32( const FKeshInt64& I64, const FKeshUInt32& UI32 )
	{
		return I64.Value + UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 + int64" )
	static FKeshInt64 FKeshUInt32PlusInt64( const FKeshUInt32& UI32, const FKeshInt64& I64 )
	{
		return UI32.Value + I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 + int16" )
	static FKeshInt64 FKeshInt64PlusInt16( const FKeshInt64& I64, const FKeshInt16& I16 )
	{
		return I64.Value + I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 + int64" )
	static FKeshInt64 FKeshInt16PlusInt64( const FKeshInt16& I16, const FKeshInt64& I64 )
	{
		return I16.Value + I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 + uint16" )
	static FKeshInt64 FKeshInt64PlusUInt16( const FKeshInt64& I64, const FKeshUInt16& UI16 )
	{
		return I64.Value + UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 + int64" )
	static FKeshInt64 FKeshUInt16PlusInt64( const FKeshUInt16& UI16, const FKeshInt64& I64 )
	{
		return UI16.Value + I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 + int8" )
	static FKeshInt64 FKeshInt64PlusInt8( const FKeshInt64& I64, const FKeshInt8& I8 )
	{
		return I64.Value + I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 + int64" )
	static FKeshInt64 FKeshInt8PlusInt64( const FKeshInt8& I8, const FKeshInt64& I64 )
	{
		return I8.Value + I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 + uint8" )
	static FKeshInt64 FKeshInt64PlusUInt8( const FKeshInt64& I64, uint8 UI8 )
	{
		return I64.Value + UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 + int64" )
	static FKeshInt64 KeshUE4FTUInt8PlusInt64( uint8 UI8, const FKeshInt64& I64 )
	{
		return UI8 + I64.Value;
	}

	/* UInt 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 + uint64" )
	static FKeshUInt64 KeshUE4FTUInt64PlusUInt64( const FKeshUInt64& UI641, const FKeshUInt64& UI642 )
	{
		return UI641.Value + UI642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 + int32" )
	static FKeshUInt64 KeshUE4FTUInt64PlusInt32( const FKeshUInt64& UI64, int32 I32 )
	{
		return UI64.Value + I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 + uint64" )
	static FKeshUInt64 KeshUE4FTUInt32PlusInt64( int32 I32, const FKeshUInt64& UI64 )
	{
		return I32 + UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 + uint32" )
	static FKeshUInt64 KeshUE4FTUInt64PlusUInt32( const FKeshUInt64& UI64, const FKeshUInt32& UI32 )
	{
		return UI64.Value + UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 + uint64" )
	static FKeshUInt64 KeshUE4FTUUInt32PlusInt64( const FKeshUInt32& UI32, const FKeshUInt64& UI64 )
	{
		return UI32.Value + UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 + int16" )
	static FKeshUInt64 KeshUE4FTUInt64PlusInt16( const FKeshUInt64& UI64, const FKeshInt16& I16 )
	{
		return UI64.Value + I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 + uint64" )
	static FKeshUInt64 FKeshInt16PlusUInt64( const FKeshInt16& I16, const FKeshUInt64& UI64 )
	{
		return I16.Value + UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 + uint16" )
	static FKeshUInt64 KeshUE4FTUInt64PlusUInt16( const FKeshUInt64& UI64, const FKeshUInt16& UI16 )
	{
		return UI64.Value + UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 + uint64" )
	static FKeshUInt64 FKeshUInt16PlusUInt64( const FKeshUInt16& UI16, const FKeshUInt64& UI64 )
	{
		return UI16.Value + UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 + int8" )
	static FKeshUInt64 KeshUE4FTUInt64PlusInt8( const FKeshUInt64& UI64, const FKeshInt8& I8 )
	{
		return UI64.Value + I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 + uint64" )
	static FKeshUInt64 FKeshInt8PlusUInt64( const FKeshInt8& I8, const FKeshUInt64& UI64 )
	{
		return I8.Value + UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 + uint8" )
	static FKeshUInt64 KeshUE4FTUInt64PlusUInt8( const FKeshUInt64& UI64, uint8 UI8 )
	{
		return UI64.Value + UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 + uint64" )
	static FKeshUInt64 KeshUE4FTUInt8PlusUInt64( uint8 UI8, const FKeshUInt64& UI64 )
	{
		return UI8 + UI64.Value;
	}

	/* Int 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 + uint32" )
	static int32 KeshUE4FTInt32PlusUInt32( int32 I32, const FKeshUInt32& UI32 )
	{
		return I32 + UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 + int32" )
	static int32 FKeshUInt32PlusInt32( const FKeshUInt32& UI32, int32 I32 )
	{
		return UI32.Value + I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 + int16" )
	static int32 KeshUE4FTInt32PlusInt16( int32 I32, const FKeshInt16& I16 )
	{
		return I32 + I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 + int32" )
	static int32 FKeshInt16PlusInt32( const FKeshInt16& I16, int32 I32 )
	{
		return I16.Value + I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 + uint16" )
	static int32 KeshUE4FTInt32PlusUInt16( int32 I32, const FKeshUInt16& UI16 )
	{
		return I32 + UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 + int32" )
	static int32 FKeshUInt16PlusInt32( const FKeshUInt16& UI16, int32 I32 )
	{
		return UI16.Value + I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 + int8" )
	static int32 KeshUE4FTInt32PlusInt8( int32 I32, const FKeshInt8& I8 )
	{
		return I32 + I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 + int32" )
	static int32 FKeshInt8PluInt32s( const FKeshInt8& I8, int32 I32 )
	{
		return I8.Value + I32;
	}

	/* UInt 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 + uint32" )
	static FKeshUInt32 FKeshUInt32PlusUInt32( const FKeshUInt32& UI321, const FKeshUInt32& UI322 )
	{
		return UI321.Value + UI322.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 + int16" )
	static FKeshUInt32 FKeshUInt32PlusInt16( const FKeshUInt32& UI32, const FKeshInt16& I16 )
	{
		return UI32.Value + I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 + uint32" )
	static FKeshUInt32 FKeshInt16PlusUInt32( const FKeshInt16& I16, const FKeshUInt32& UI32 )
	{
		return I16.Value + UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 + uint16" )
	static FKeshUInt32 FKeshUInt32PlusUInt16( const FKeshUInt32& UI32, const FKeshUInt16& UI16 )
	{
		return UI32.Value + UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 + uint32" )
	static FKeshUInt32 FKeshUInt16PlusUInt32( const FKeshUInt16& UI16, const FKeshUInt32& UI32 )
	{
		return UI16.Value + UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 + int8" )
	static FKeshUInt32 FKeshUInt32PlusInt8( const FKeshUInt32& UI32, const FKeshInt8& I8 )
	{
		return UI32.Value + I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 + uint32" )
	static FKeshUInt32 FKeshInt8PlusUInt32( const FKeshInt8& I8, const FKeshUInt32& UI32 )
	{
		return I8.Value + UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 + uint8" )
	static FKeshUInt32 FKeshUInt32PlusUInt8( const FKeshUInt32& UI32, uint8 UI8 )
	{
		return UI32.Value + UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 + uint32" )
	static FKeshUInt32 KeshUE4FTUInt8PlusUInt32( uint8 UI8, const FKeshUInt32& UI32 )
	{
		return UI8 + UI32.Value;
	}

	/* Int 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 + int16" )
	static FKeshInt16 FKeshInt16PlusInt16( const FKeshInt16& I161, const FKeshInt16& I162 )
	{
		return I161.Value + I162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 + uint16" )
	static FKeshInt16 FKeshInt16PlusUInt16( const FKeshInt16& I16, const FKeshUInt16& UI16 )
	{
		return I16.Value + UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 + int16" )
	static FKeshInt16 FKeshUInt16PlusInt16( const FKeshUInt16& UI16, const FKeshInt16& I16 )
	{
		return UI16.Value + I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 + int8" )
	static FKeshInt16 FKeshInt16PlusInt8( const FKeshInt16& I16, const FKeshInt8& I8 )
	{
		return I16.Value + I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 + int16" )
	static FKeshInt16 FKeshInt8PlusInt16( const FKeshInt8& I8, const FKeshInt16& I16 )
	{
		return I8.Value + I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 + uint8" )
	static FKeshInt16 FKeshInt16PlusUInt8( const FKeshInt16& I16, uint8 UI8 )
	{
		return I16.Value + UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 + int16" )
	static FKeshInt16 KeshUE4FTUInt8PlusInt16( uint8 UI8, const FKeshInt16& I16 )
	{
		return UI8 + I16.Value;
	}

	/* UInt 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 + uint16" )
	static FKeshUInt16 FKeshUInt16PlusUUInt16( const FKeshUInt16& UI161, const FKeshUInt16& UI162 )
	{
		return UI161.Value + UI162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 + int8" )
	static FKeshUInt16 FKeshUInt16PlusInt8( const FKeshUInt16& UI16, const FKeshInt8& I8 )
	{
		return UI16.Value + I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 + uint16" )
	static FKeshUInt16 FKeshInt8PlusUInt16( const FKeshInt8& I8, const FKeshUInt16& UI16 )
	{
		return I8.Value + UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 + uint8" )
	static FKeshUInt16 FKeshUInt16PlusUInt8( const FKeshUInt16& UI16, uint8 UI8 )
	{
		return UI16.Value + UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 + uint16" )
	static FKeshUInt16 KeshUE4FTUInt8PlusUInt16( uint8 UI8, const FKeshUInt16& UI16 )
	{
		return UI8 + UI16.Value;
	}

	/* Int 8 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 + int8" )
	static FKeshInt8 FKeshInt8PlusInt8( const FKeshInt8& I81, const FKeshInt8& I82 )
	{
		return I81.Value + I82.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 + uint8" )
	static FKeshInt8 FKeshInt8PlusUInt8( const FKeshInt8& I8, uint8 UI8 )
	{
		return I8.Value + UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 + int8" )
	static FKeshInt8 KeshUE4FTUInt8PlusInt8( uint8 UI8, const FKeshInt8& I8 )
	{
		return UI8 + I8.Value;
	}


	/************/
	/* Subtract */
	/************/

	/* Double */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl - dbl" )
	static FKeshDouble KeshUE4FTDoubleSubtractDouble( const FKeshDouble& D1, const FKeshDouble& D2 )
	{
		return D1.Value - D2.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl - flt" )
	static FKeshDouble KeshUE4FTDoubleSubtractFloat( const FKeshDouble& D, float F )
	{
		return D.Value - F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt - dbl" )
	static FKeshDouble KeshUE4FTFloatSubtractDouble( float F, const FKeshDouble& D )
	{
		return F - D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl - int64" )
	static FKeshDouble KeshUE4FTDoubleSubtractInt64( const FKeshDouble& D, const FKeshInt64& I64 )
	{
		return D.Value - I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 - dbl" )
	static FKeshDouble FKeshInt64SubtractDouble( const FKeshInt64& I64, const FKeshDouble& D )
	{
		return I64.Value - D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl - uint64" )
	static FKeshDouble KeshUE4FTDoubleSubtractUInt64( const FKeshDouble& D, const FKeshUInt64& UI64 )
	{
		return D.Value - UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 - dbl" )
	static FKeshDouble KeshUE4FTUInt64SubtractDouble( const FKeshUInt64& UI64, const FKeshDouble& D )
	{
		return UI64.Value - D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl - int32" )
	static FKeshDouble KeshUE4FTDoubleSubtractInt32( const FKeshDouble& D, int32 I32 )
	{
		return D.Value - I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 - dbl" )
	static FKeshDouble KeshUE4FTInt32SubtractDouble( int32 I32, const FKeshDouble& D )
	{
		return I32 - D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl - uint32" )
	static FKeshDouble KeshUE4FTDoubleSubtractUInt32( const FKeshDouble& D, const FKeshUInt32& UI32 )
	{
		return D.Value - UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 - dbl" )
	static FKeshDouble FKeshUInt32SubtractDouble( const FKeshUInt32& UI32, const FKeshDouble& D )
	{
		return UI32.Value - D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl - int16" )
	static FKeshDouble KeshUE4FTDoubleSubtractInt16( const FKeshDouble& D, const FKeshInt16& I16 )
	{
		return D.Value - I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 - dbl" )
	static FKeshDouble FKeshInt16SubtractDouble( const FKeshInt16& I16, const FKeshDouble& D )
	{
		return I16.Value - D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl - uint16" )
	static FKeshDouble KeshUE4FTDoubleSubtractUInt16( const FKeshDouble& D, const FKeshUInt16& UI16 )
	{
		return D.Value - UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 - dbl" )
	static FKeshDouble FKeshUInt16SubtractDouble( const FKeshUInt16& UI16, const FKeshDouble& D )
	{
		return UI16.Value - D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl - int8" )
	static FKeshDouble KeshUE4FTDoubleSubtractInt8( const FKeshDouble& D, const FKeshInt8& I8 )
	{
		return D.Value - I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 - dbl" )
	static FKeshDouble FKeshInt8SubtractDouble( const FKeshInt8& I8, const FKeshDouble& D )
	{
		return I8.Value - D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl - uint8" )
	static FKeshDouble KeshUE4FTDoubleSubtractUInt8( const FKeshDouble& D, uint8 UI8 )
	{
		return D.Value - UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 - dbl" )
	static FKeshDouble KeshUE4FTUInt8SubtractDouble( uint8 UI8, const FKeshDouble& D )
	{
		return UI8 - D.Value;
	}

	/* float */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt - int64" )
	static float KeshUE4FTFloatSubtractInt64( float F, const FKeshInt64& I64 )
	{
		return F - I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 - flt" )
	static float FKeshInt64SubtractFloat( const FKeshInt64& I64, float F )
	{
		return I64.Value - F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt - uint64" )
	static float KeshUE4FTFloatSubtractUInt64( float F, const FKeshUInt64& UI64 )
	{
		return F - UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 - flt" )
	static float KeshUE4FTUInt64SubtractFloat( const FKeshUInt64& UI64, float F )
	{
		return UI64.Value - F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt - uint32" )
	static float KeshUE4FTFloatSubtractUInt32( float F, const FKeshUInt32& UI32 )
	{
		return F - UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 - flt" )
	static float FKeshUInt32SubtractFloat( const FKeshUInt32& UI32, float F )
	{
		return UI32.Value - F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt - int16" )
	static float KeshUE4FTFloatSubtractInt16( float F, const FKeshInt16& I16 )
	{
		return F - I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 - flt" )
	static float FKeshInt16SubtractFloat( const FKeshInt16& I16, float F )
	{
		return I16.Value - F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt - uint16" )
	static float KeshUE4FTFloatSubtractUInt16( float F, const FKeshUInt16& UI16 )
	{
		return F - UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 - flt" )
	static float FKeshUInt16SubtractFloat( const FKeshUInt16& UI16, float F )
	{
		return UI16.Value - F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt - int8" )
	static float KeshUE4FTFloatSubtractInt8( float F, const FKeshInt8& I8 )
	{
		return F - I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 - flt" )
	static float FKeshInt8SubtractFloat( const FKeshInt8& I8, float F )
	{
		return I8.Value - F;
	}

	/* Int 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 - int64" )
	static FKeshInt64 FKeshInt64SubtractInt64( const FKeshInt64& I641, const FKeshInt64& I642 )
	{
		return I641.Value - I642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 - uint64" )
	static FKeshInt64 FKeshInt64SubtractUInt64( const FKeshInt64& I64, const FKeshUInt64& UI64 )
	{
		return I64.Value - UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 - int64" )
	static FKeshInt64 KeshUE4FTUInt64SubtractInt64( const FKeshUInt64& UI64, const FKeshInt64& I64 )
	{
		return UI64.Value - I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 - int32" )
	static FKeshInt64 FKeshInt64SubtractInt32( const FKeshInt64& I64, int32 I32 )
	{
		return I64.Value - I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 - int64" )
	static FKeshInt64 KeshUE4FTInt32SubtractInt64( int32 I32, const FKeshInt64& I64 )
	{
		return I32 - I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 - uint32" )
	static FKeshInt64 FKeshInt64SubtractUInt32( const FKeshInt64& I64, const FKeshUInt32& UI32 )
	{
		return I64.Value - UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 - int64" )
	static FKeshInt64 FKeshUInt32SubtractInt64( const FKeshUInt32& UI32, const FKeshInt64& I64 )
	{
		return UI32.Value - I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 - int16" )
	static FKeshInt64 FKeshInt64SubtractInt16( const FKeshInt64& I64, const FKeshInt16& I16 )
	{
		return I64.Value - I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 - int64" )
	static FKeshInt64 FKeshInt16SubtractInt64( const FKeshInt16& I16, const FKeshInt64& I64 )
	{
		return I16.Value - I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 - uint16" )
	static FKeshInt64 FKeshInt64SubtractUInt16( const FKeshInt64& I64, const FKeshUInt16& UI16 )
	{
		return I64.Value - UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 - int64" )
	static FKeshInt64 FKeshUInt16SubtractInt64( const FKeshUInt16& UI16, const FKeshInt64& I64 )
	{
		return UI16.Value - I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 - int8" )
	static FKeshInt64 FKeshInt64SubtractInt8( const FKeshInt64& I64, const FKeshInt8& I8 )
	{
		return I64.Value - I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 - int64" )
	static FKeshInt64 FKeshInt8SubtractInt64( const FKeshInt8& I8, const FKeshInt64& I64 )
	{
		return I8.Value - I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 - uint8" )
	static FKeshInt64 FKeshInt64SubtractUInt8( const FKeshInt64& I64, uint8 UI8 )
	{
		return I64.Value - UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 - int64" )
	static FKeshInt64 KeshUE4FTUInt8SubtractInt64( uint8 UI8, const FKeshInt64& I64 )
	{
		return UI8 - I64.Value;
	}

	/* UInt 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 - uint64" )
	static FKeshUInt64 KeshUE4FTUInt64SubtractUInt64( const FKeshUInt64& UI641, const FKeshUInt64& UI642 )
	{
		return UI641.Value - UI642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 - int32" )
	static FKeshUInt64 KeshUE4FTUInt64SubtractInt32( const FKeshUInt64& UI64, int32 I32 )
	{
		return UI64.Value - I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 - uint64" )
	static FKeshUInt64 KeshUE4FTUInt32SubtractInt64( int32 I32, const FKeshUInt64& UI64 )
	{
		return I32 - UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 - uint32" )
	static FKeshUInt64 KeshUE4FTUInt64SubtractUInt32( const FKeshUInt64& UI64, const FKeshUInt32& UI32 )
	{
		return UI64.Value - UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 - uint64" )
	static FKeshUInt64 KeshUE4FTUUInt32SubtractInt64( const FKeshUInt32& UI32, const FKeshUInt64& UI64 )
	{
		return UI32.Value - UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 - int16" )
	static FKeshUInt64 KeshUE4FTUInt64SubtractInt16( const FKeshUInt64& UI64, const FKeshInt16& I16 )
	{
		return UI64.Value - I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 - uint64" )
	static FKeshUInt64 FKeshInt16SubtractUInt64( const FKeshInt16& I16, const FKeshUInt64& UI64 )
	{
		return I16.Value - UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 - uint16" )
	static FKeshUInt64 KeshUE4FTUInt64SubtractUInt16( const FKeshUInt64& UI64, const FKeshUInt16& UI16 )
	{
		return UI64.Value - UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 - uint64" )
	static FKeshUInt64 FKeshUInt16SubtractUInt64( const FKeshUInt16& UI16, const FKeshUInt64& UI64 )
	{
		return UI16.Value - UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 - int8" )
	static FKeshUInt64 KeshUE4FTUInt64SubtractInt8( const FKeshUInt64& UI64, const FKeshInt8& I8 )
	{
		return UI64.Value - I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 - uint64" )
	static FKeshUInt64 FKeshInt8SubtractUInt64( const FKeshInt8& I8, const FKeshUInt64& UI64 )
	{
		return I8.Value - UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 - uint8" )
	static FKeshUInt64 KeshUE4FTUInt64SubtractUInt8( const FKeshUInt64& UI64, uint8 UI8 )
	{
		return UI64.Value - UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 - uint64" )
	static FKeshUInt64 KeshUE4FTUInt8SubtractUInt64( uint8 UI8, const FKeshUInt64& UI64 )
	{
		return UI8 - UI64.Value;
	}

	/* Int 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 - uint32" )
	static int32 KeshUE4FTInt32SubtractUInt32( int32 I32, const FKeshUInt32& UI32 )
	{
		return I32 - UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 - int32" )
	static int32 FKeshUInt32SubtractInt32( const FKeshUInt32& UI32, int32 I32 )
	{
		return UI32.Value - I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 - int16" )
	static int32 KeshUE4FTInt32SubtractInt16( int32 I32, const FKeshInt16& I16 )
	{
		return I32 - I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 - int32" )
	static int32 FKeshInt16SubtractInt32( const FKeshInt16& I16, int32 I32 )
	{
		return I16.Value - I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 - uint16" )
	static int32 KeshUE4FTInt32SubtractUInt16( int32 I32, const FKeshUInt16& UI16 )
	{
		return I32 - UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 - int32" )
	static int32 FKeshUInt16SubtractInt32( const FKeshUInt16& UI16, int32 I32 )
	{
		return UI16.Value - I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 - int8" )
	static int32 KeshUE4FTInt32SubtractInt8( int32 I32, const FKeshInt8& I8 )
	{
		return I32 - I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 - int32" )
	static int32 FKeshInt8MinusInt32( const FKeshInt8& I8, int32 I32 )
	{
		return I8.Value - I32;
	}

	/* UInt 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 - uint32" )
	static FKeshUInt32 FKeshUInt32SubtractUInt32( const FKeshUInt32& UI321, const FKeshUInt32& UI322 )
	{
		return UI321.Value - UI322.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 - int16" )
	static FKeshUInt32 FKeshUInt32SubtractInt16( const FKeshUInt32& UI32, const FKeshInt16& I16 )
	{
		return UI32.Value - I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 - uint32" )
	static FKeshUInt32 FKeshInt16SubtractUInt32( const FKeshInt16& I16, const FKeshUInt32& UI32 )
	{
		return I16.Value - UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 - uint16" )
	static FKeshUInt32 FKeshUInt32SubtractUInt16( const FKeshUInt32& UI32, const FKeshUInt16& UI16 )
	{
		return UI32.Value - UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 - uint32" )
	static FKeshUInt32 FKeshUInt16SubtractUInt32( const FKeshUInt16& UI16, const FKeshUInt32& UI32 )
	{
		return UI16.Value - UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 - int8" )
	static FKeshUInt32 FKeshUInt32SubtractInt8( const FKeshUInt32& UI32, const FKeshInt8& I8 )
	{
		return UI32.Value - I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 - uint32" )
	static FKeshUInt32 FKeshInt8SubtractUInt32( const FKeshInt8& I8, const FKeshUInt32& UI32 )
	{
		return I8.Value - UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 - uint8" )
	static FKeshUInt32 FKeshUInt32SubtractUInt8( const FKeshUInt32& UI32, uint8 UI8 )
	{
		return UI32.Value - UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 - uint32" )
	static FKeshUInt32 KeshUE4FTUInt8SubtractUInt32( uint8 UI8, const FKeshUInt32& UI32 )
	{
		return UI8 - UI32.Value;
	}

	/* Int 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 - int16" )
	static FKeshInt16 FKeshInt16SubtractInt16( const FKeshInt16& I161, const FKeshInt16& I162 )
	{
		return I161.Value - I162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 - uint16" )
	static FKeshInt16 FKeshInt16SubtractUInt16( const FKeshInt16& I16, const FKeshUInt16& UI16 )
	{
		return I16.Value - UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 - int16" )
	static FKeshInt16 FKeshUInt16SubtractInt16( const FKeshUInt16& UI16, const FKeshInt16& I16 )
	{
		return UI16.Value - I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 - int8" )
	static FKeshInt16 FKeshInt16SubtractInt8( const FKeshInt16& I16, const FKeshInt8& I8 )
	{
		return I16.Value - I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 - int16" )
	static FKeshInt16 FKeshInt8SubtractInt16( const FKeshInt8& I8, const FKeshInt16& I16 )
	{
		return I8.Value - I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 - uint8" )
	static FKeshInt16 FKeshInt16SubtractUInt8( const FKeshInt16& I16, uint8 UI8 )
	{
		return I16.Value - UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 - int16" )
	static FKeshInt16 KeshUE4FTUInt8SubtractInt16( uint8 UI8, const FKeshInt16& I16 )
	{
		return UI8 - I16.Value;
	}

	/* UInt 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 - uint16" )
	static FKeshUInt16 FKeshUInt16SubtractUUInt16( const FKeshUInt16& UI161, const FKeshUInt16& UI162 )
	{
		return UI161.Value - UI162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 - int8" )
	static FKeshUInt16 FKeshUInt16SubtractInt8( const FKeshUInt16& UI16, const FKeshInt8& I8 )
	{
		return UI16.Value - I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 - uint16" )
	static FKeshUInt16 FKeshInt8SubtractUInt16( const FKeshInt8& I8, const FKeshUInt16& UI16 )
	{
		return I8.Value - UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 - uint8" )
	static FKeshUInt16 FKeshUInt16SubtractUInt8( const FKeshUInt16& UI16, uint8 UI8 )
	{
		return UI16.Value - UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 - uint16" )
	static FKeshUInt16 KeshUE4FTUInt8SubtractUInt16( uint8 UI8, const FKeshUInt16& UI16 )
	{
		return UI8 - UI16.Value;
	}

	/* Int 8 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 - int8" )
	static FKeshInt8 FKeshInt8SubtractInt8( const FKeshInt8& I81, const FKeshInt8& I82 )
	{
		return I81.Value - I82.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 - uint8" )
	static FKeshInt8 FKeshInt8SubtractUInt8( const FKeshInt8& I8, uint8 UI8 )
	{
		return I8.Value - UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 - int8" )
	static FKeshInt8 KeshUE4FTUInt8SubtractInt8( uint8 UI8, const FKeshInt8& I8 )
	{
		return UI8 - I8.Value;
	}


	/*********/
	/* Times */
	/*********/

	/* Double */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl * dbl" )
	static FKeshDouble KeshUE4FTDoubleTimesDouble( const FKeshDouble& D1, const FKeshDouble& D2 )
	{
		return D1.Value * D2.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl * flt" )
	static FKeshDouble KeshUE4FTDoubleTimesFloat( const FKeshDouble& D, float F )
	{
		return D.Value * F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt * dbl" )
	static FKeshDouble KeshUE4FTFloatTimesDouble( float F, const FKeshDouble& D )
	{
		return F * D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl * int64" )
	static FKeshDouble KeshUE4FTDoubleTimesInt64( const FKeshDouble& D, const FKeshInt64& I64 )
	{
		return D.Value * I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 * dbl" )
	static FKeshDouble FKeshInt64TimesDouble( const FKeshInt64& I64, const FKeshDouble& D )
	{
		return I64.Value * D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl * uint64" )
	static FKeshDouble KeshUE4FTDoubleTimesUInt64( const FKeshDouble& D, const FKeshUInt64& UI64 )
	{
		return D.Value * UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 * dbl" )
	static FKeshDouble KeshUE4FTUInt64TimesDouble( const FKeshUInt64& UI64, const FKeshDouble& D )
	{
		return UI64.Value * D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl * int32" )
	static FKeshDouble KeshUE4FTDoubleTimesInt32( const FKeshDouble& D, int32 I32 )
	{
		return D.Value * I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 * dbl" )
	static FKeshDouble KeshUE4FTInt32TimesDouble( int32 I32, const FKeshDouble& D )
	{
		return I32 * D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl * uint32" )
	static FKeshDouble KeshUE4FTDoubleTimesUInt32( const FKeshDouble& D, const FKeshUInt32& UI32 )
	{
		return D.Value * UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 * dbl" )
	static FKeshDouble FKeshUInt32TimesDouble( const FKeshUInt32& UI32, const FKeshDouble& D )
	{
		return UI32.Value * D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl * int16" )
	static FKeshDouble KeshUE4FTDoubleTimesInt16( const FKeshDouble& D, const FKeshInt16& I16 )
	{
		return D.Value * I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 * dbl" )
	static FKeshDouble FKeshInt16TimesDouble( const FKeshInt16& I16, const FKeshDouble& D )
	{
		return I16.Value * D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl * uint16" )
	static FKeshDouble KeshUE4FTDoubleTimesUInt16( const FKeshDouble& D, const FKeshUInt16& UI16 )
	{
		return D.Value * UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 * dbl" )
	static FKeshDouble FKeshUInt16TimesDouble( const FKeshUInt16& UI16, const FKeshDouble& D )
	{
		return UI16.Value * D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl * int8" )
	static FKeshDouble KeshUE4FTDoubleTimesInt8( const FKeshDouble& D, const FKeshInt8& I8 )
	{
		return D.Value * I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 * dbl" )
	static FKeshDouble FKeshInt8TimesDouble( const FKeshInt8& I8, const FKeshDouble& D )
	{
		return I8.Value * D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl * uint8" )
	static FKeshDouble KeshUE4FTDoubleTimesUInt8( const FKeshDouble& D, uint8 UI8 )
	{
		return D.Value * UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 * dbl" )
	static FKeshDouble KeshUE4FTUInt8TimesDouble( uint8 UI8, const FKeshDouble& D )
	{
		return UI8 * D.Value;
	}

	/* float */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt * int64" )
	static float KeshUE4FTFloatTimesInt64( float F, const FKeshInt64& I64 )
	{
		return F * I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 * flt" )
	static float FKeshInt64TimesFloat( const FKeshInt64& I64, float F )
	{
		return I64.Value * F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt * uint64" )
	static float KeshUE4FTFloatTimesUInt64( float F, const FKeshUInt64& UI64 )
	{
		return F * UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 * flt" )
	static float KeshUE4FTUInt64TimesFloat( const FKeshUInt64& UI64, float F )
	{
		return UI64.Value * F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt * uint32" )
	static float KeshUE4FTFloatTimesUInt32( float F, const FKeshUInt32& UI32 )
	{
		return F * UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 * flt" )
	static float FKeshUInt32TimesFloat( const FKeshUInt32& UI32, float F )
	{
		return UI32.Value * F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt * int16" )
	static float KeshUE4FTFloatTimesInt16( float F, const FKeshInt16& I16 )
	{
		return F * I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 * flt" )
	static float FKeshInt16TimesFloat( const FKeshInt16& I16, float F )
	{
		return I16.Value * F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt * uint16" )
	static float KeshUE4FTFloatTimesUInt16( float F, const FKeshUInt16& UI16 )
	{
		return F * UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 * flt" )
	static float FKeshUInt16TimesFloat( const FKeshUInt16& UI16, float F )
	{
		return UI16.Value * F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt * int8" )
	static float KeshUE4FTFloatTimesInt8( float F, const FKeshInt8& I8 )
	{
		return F * I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 * flt" )
	static float FKeshInt8TimesFloat( const FKeshInt8& I8, float F )
	{
		return I8.Value * F;
	}

	/* Int 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 * int64" )
	static FKeshInt64 FKeshInt64TimesInt64( const FKeshInt64& I641, const FKeshInt64& I642 )
	{
		return I641.Value * I642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 * uint64" )
	static FKeshInt64 FKeshInt64TimesUInt64( const FKeshInt64& I64, const FKeshUInt64& UI64 )
	{
		return I64.Value * UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 * int64" )
	static FKeshInt64 KeshUE4FTUInt64TimesInt64( const FKeshUInt64& UI64, const FKeshInt64& I64 )
	{
		return UI64.Value * I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 * int32" )
	static FKeshInt64 FKeshInt64TimesInt32( const FKeshInt64& I64, int32 I32 )
	{
		return I64.Value * I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 * int64" )
	static FKeshInt64 KeshUE4FTInt32TimesInt64( int32 I32, const FKeshInt64& I64 )
	{
		return I32 * I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 * uint32" )
	static FKeshInt64 FKeshInt64TimesUInt32( const FKeshInt64& I64, const FKeshUInt32& UI32 )
	{
		return I64.Value * UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 * int64" )
	static FKeshInt64 FKeshUInt32TimesInt64( const FKeshUInt32& UI32, const FKeshInt64& I64 )
	{
		return UI32.Value * I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 * int16" )
	static FKeshInt64 FKeshInt64TimesInt16( const FKeshInt64& I64, const FKeshInt16& I16 )
	{
		return I64.Value * I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 * int64" )
	static FKeshInt64 FKeshInt16TimesInt64( const FKeshInt16& I16, const FKeshInt64& I64 )
	{
		return I16.Value * I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 * uint16" )
	static FKeshInt64 FKeshInt64TimesUInt16( const FKeshInt64& I64, const FKeshUInt16& UI16 )
	{
		return I64.Value * UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 * int64" )
	static FKeshInt64 FKeshUInt16TimesInt64( const FKeshUInt16& UI16, const FKeshInt64& I64 )
	{
		return UI16.Value * I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 * int8" )
	static FKeshInt64 FKeshInt64TimesInt8( const FKeshInt64& I64, const FKeshInt8& I8 )
	{
		return I64.Value * I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 * int64" )
	static FKeshInt64 FKeshInt8TimesInt64( const FKeshInt8& I8, const FKeshInt64& I64 )
	{
		return I8.Value * I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 * uint8" )
	static FKeshInt64 FKeshInt64TimesUInt8( const FKeshInt64& I64, uint8 UI8 )
	{
		return I64.Value * UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 * int64" )
	static FKeshInt64 KeshUE4FTUInt8TimesInt64( uint8 UI8, const FKeshInt64& I64 )
	{
		return UI8 * I64.Value;
	}

	/* UInt 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 * uint64" )
	static FKeshUInt64 KeshUE4FTUInt64TimesUInt64( const FKeshUInt64& UI641, const FKeshUInt64& UI642 )
	{
		return UI641.Value * UI642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 * int32" )
	static FKeshUInt64 KeshUE4FTUInt64TimesInt32( const FKeshUInt64& UI64, int32 I32 )
	{
		return UI64.Value * I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 * uint64" )
	static FKeshUInt64 KeshUE4FTUInt32TimesInt64( int32 I32, const FKeshUInt64& UI64 )
	{
		return I32 * UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 * uint32" )
	static FKeshUInt64 KeshUE4FTUInt64TimesUInt32( const FKeshUInt64& UI64, const FKeshUInt32& UI32 )
	{
		return UI64.Value * UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 * uint64" )
	static FKeshUInt64 KeshUE4FTUUInt32TimesInt64( const FKeshUInt32& UI32, const FKeshUInt64& UI64 )
	{
		return UI32.Value * UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 * int16" )
	static FKeshUInt64 KeshUE4FTUInt64TimesInt16( const FKeshUInt64& UI64, const FKeshInt16& I16 )
	{
		return UI64.Value * I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 * uint64" )
	static FKeshUInt64 FKeshInt16TimesUInt64( const FKeshInt16& I16, const FKeshUInt64& UI64 )
	{
		return I16.Value * UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 * uint16" )
	static FKeshUInt64 KeshUE4FTUInt64TimesUInt16( const FKeshUInt64& UI64, const FKeshUInt16& UI16 )
	{
		return UI64.Value * UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 * uint64" )
	static FKeshUInt64 FKeshUInt16TimesUInt64( const FKeshUInt16& UI16, const FKeshUInt64& UI64 )
	{
		return UI16.Value * UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 * int8" )
	static FKeshUInt64 KeshUE4FTUInt64TimesInt8( const FKeshUInt64& UI64, const FKeshInt8& I8 )
	{
		return UI64.Value * I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 * uint64" )
	static FKeshUInt64 FKeshInt8TimesUInt64( const FKeshInt8& I8, const FKeshUInt64& UI64 )
	{
		return I8.Value * UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 * uint8" )
	static FKeshUInt64 KeshUE4FTUInt64TimesUInt8( const FKeshUInt64& UI64, uint8 UI8 )
	{
		return UI64.Value * UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 * uint64" )
	static FKeshUInt64 KeshUE4FTUInt8TimesUInt64( uint8 UI8, const FKeshUInt64& UI64 )
	{
		return UI8 * UI64.Value;
	}

	/* Int 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 * uint32" )
	static int32 KeshUE4FTInt32TimesUInt32( int32 I32, const FKeshUInt32& UI32 )
	{
		return I32 * UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 * int32" )
	static int32 FKeshUInt32TimesInt32( const FKeshUInt32& UI32, int32 I32 )
	{
		return UI32.Value * I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 * int16" )
	static int32 KeshUE4FTInt32TimesInt16( int32 I32, const FKeshInt16& I16 )
	{
		return I32 * I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 * int32" )
	static int32 FKeshInt16TimesInt32( const FKeshInt16& I16, int32 I32 )
	{
		return I16.Value * I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 * uint16" )
	static int32 KeshUE4FTInt32TimesUInt16( int32 I32, const FKeshUInt16& UI16 )
	{
		return I32 * UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 * int32" )
	static int32 FKeshUInt16TimesInt32( const FKeshUInt16& UI16, int32 I32 )
	{
		return UI16.Value * I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 * int8" )
	static int32 KeshUE4FTInt32TimesInt8( int32 I32, const FKeshInt8& I8 )
	{
		return I32 * I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 * int32" )
	static int32 FKeshInt8TimesInt32( const FKeshInt8& I8, int32 I32 )
	{
		return I8.Value * I32;
	}

	/* UInt 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 * uint32" )
	static FKeshUInt32 FKeshUInt32TimesUInt32( const FKeshUInt32& UI321, const FKeshUInt32& UI322 )
	{
		return UI321.Value * UI322.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 * int16" )
	static FKeshUInt32 FKeshUInt32TimesInt16( const FKeshUInt32& UI32, const FKeshInt16& I16 )
	{
		return UI32.Value * I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 * uint32" )
	static FKeshUInt32 FKeshInt16TimesUInt32( const FKeshInt16& I16, const FKeshUInt32& UI32 )
	{
		return I16.Value * UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 * uint16" )
	static FKeshUInt32 FKeshUInt32TimesUInt16( const FKeshUInt32& UI32, const FKeshUInt16& UI16 )
	{
		return UI32.Value * UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 * uint32" )
	static FKeshUInt32 FKeshUInt16TimesUInt32( const FKeshUInt16& UI16, const FKeshUInt32& UI32 )
	{
		return UI16.Value * UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 * int8" )
	static FKeshUInt32 FKeshUInt32TimesInt8( const FKeshUInt32& UI32, const FKeshInt8& I8 )
	{
		return UI32.Value * I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 * uint32" )
	static FKeshUInt32 FKeshInt8TimesUInt32( const FKeshInt8& I8, const FKeshUInt32& UI32 )
	{
		return I8.Value * UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 * uint8" )
	static FKeshUInt32 FKeshUInt32TimesUInt8( const FKeshUInt32& UI32, uint8 UI8 )
	{
		return UI32.Value * UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 * uint32" )
	static FKeshUInt32 KeshUE4FTUInt8TimesUInt32( uint8 UI8, const FKeshUInt32& UI32 )
	{
		return UI8 * UI32.Value;
	}

	/* Int 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 * int16" )
	static FKeshInt16 FKeshInt16TimesInt16( const FKeshInt16& I161, const FKeshInt16& I162 )
	{
		return I161.Value * I162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 * uint16" )
	static FKeshInt16 FKeshInt16TimesUInt16( const FKeshInt16& I16, const FKeshUInt16& UI16 )
	{
		return I16.Value * UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 * int16" )
	static FKeshInt16 FKeshUInt16TimesInt16( const FKeshUInt16& UI16, const FKeshInt16& I16 )
	{
		return UI16.Value * I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 * int8" )
	static FKeshInt16 FKeshInt16TimesInt8( const FKeshInt16& I16, const FKeshInt8& I8 )
	{
		return I16.Value * I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 * int16" )
	static FKeshInt16 FKeshInt8TimesInt16( const FKeshInt8& I8, const FKeshInt16& I16 )
	{
		return I8.Value * I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 * uint8" )
	static FKeshInt16 FKeshInt16TimesUInt8( const FKeshInt16& I16, uint8 UI8 )
	{
		return I16.Value * UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 * int16" )
	static FKeshInt16 KeshUE4FTUInt8TimesInt16( uint8 UI8, const FKeshInt16& I16 )
	{
		return UI8 * I16.Value;
	}

	/* UInt 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 * uint16" )
	static FKeshUInt16 FKeshUInt16TimesUUInt16( const FKeshUInt16& UI161, const FKeshUInt16& UI162 )
	{
		return UI161.Value * UI162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 * int8" )
	static FKeshUInt16 FKeshUInt16TimesInt8( const FKeshUInt16& UI16, const FKeshInt8& I8 )
	{
		return UI16.Value * I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 * uint16" )
	static FKeshUInt16 FKeshInt8TimesUInt16( const FKeshInt8& I8, const FKeshUInt16& UI16 )
	{
		return I8.Value * UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 * uint8" )
	static FKeshUInt16 FKeshUInt16TimesUInt8( const FKeshUInt16& UI16, uint8 UI8 )
	{
		return UI16.Value * UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 * uint16" )
	static FKeshUInt16 KeshUE4FTUInt8TimesUInt16( uint8 UI8, const FKeshUInt16& UI16 )
	{
		return UI8 * UI16.Value;
	}

	/* Int 8 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 * int8" )
	static FKeshInt8 FKeshInt8TimesInt8( const FKeshInt8& I81, const FKeshInt8& I82 )
	{
		return I81.Value * I82.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 * uint8" )
	static FKeshInt8 FKeshInt8TimesUInt8( const FKeshInt8& I8, uint8 UI8 )
	{
		return I8.Value * UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 * int8" )
	static FKeshInt8 KeshUE4FTUInt8TimesInt8( uint8 UI8, const FKeshInt8& I8 )
	{
		return UI8 * I8.Value;
	}


	/**********/
	/* Divide */
	/**********/

	/* Double */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl / dbl" )
	static FKeshDouble KeshUE4FTDoubleDivideDouble( const FKeshDouble& D1, const FKeshDouble& D2 )
	{
		return D1.Value / D2.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl / flt" )
	static FKeshDouble KeshUE4FTDoubleDivideFloat( const FKeshDouble& D, float F )
	{
		return D.Value / F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt / dbl" )
	static FKeshDouble KeshUE4FTFloatDivideDouble( float F, const FKeshDouble& D )
	{
		return F / D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl / int64" )
	static FKeshDouble KeshUE4FTDoubleDivideInt64( const FKeshDouble& D, const FKeshInt64& I64 )
	{
		return D.Value / I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 / dbl" )
	static FKeshDouble FKeshInt64DivideDouble( const FKeshInt64& I64, const FKeshDouble& D )
	{
		return I64.Value / D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl / uint64" )
	static FKeshDouble KeshUE4FTDoubleDivideUInt64( const FKeshDouble& D, const FKeshUInt64& UI64 )
	{
		return D.Value / UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 / dbl" )
	static FKeshDouble KeshUE4FTUInt64DivideDouble( const FKeshUInt64& UI64, const FKeshDouble& D )
	{
		return UI64.Value / D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl / int32" )
	static FKeshDouble KeshUE4FTDoubleDivideInt32( const FKeshDouble& D, int32 I32 )
	{
		return D.Value / I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 / dbl" )
	static FKeshDouble KeshUE4FTInt32DivideDouble( int32 I32, const FKeshDouble& D )
	{
		return I32 / D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl / uint32" )
	static FKeshDouble KeshUE4FTDoubleDivideUInt32( const FKeshDouble& D, const FKeshUInt32& UI32 )
	{
		return D.Value / UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 / dbl" )
	static FKeshDouble FKeshUInt32DivideDouble( const FKeshUInt32& UI32, const FKeshDouble& D )
	{
		return UI32.Value / D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl / int16" )
	static FKeshDouble KeshUE4FTDoubleDivideInt16( const FKeshDouble& D, const FKeshInt16& I16 )
	{
		return D.Value / I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 / dbl" )
	static FKeshDouble FKeshInt16DivideDouble( const FKeshInt16& I16, const FKeshDouble& D )
	{
		return I16.Value / D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl / uint16" )
	static FKeshDouble KeshUE4FTDoubleDivideUInt16( const FKeshDouble& D, const FKeshUInt16& UI16 )
	{
		return D.Value / UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 / dbl" )
	static FKeshDouble FKeshUInt16DivideDouble( const FKeshUInt16& UI16, const FKeshDouble& D )
	{
		return UI16.Value / D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl / int8" )
	static FKeshDouble KeshUE4FTDoubleDivideInt8( const FKeshDouble& D, const FKeshInt8& I8 )
	{
		return D.Value / I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 / dbl" )
	static FKeshDouble FKeshInt8DivideDouble( const FKeshInt8& I8, const FKeshDouble& D )
	{
		return I8.Value / D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl / uint8" )
	static FKeshDouble KeshUE4FTDoubleDivideUInt8( const FKeshDouble& D, uint8 UI8 )
	{
		return D.Value / UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 / dbl" )
	static FKeshDouble KeshUE4FTUInt8DivideDouble( uint8 UI8, const FKeshDouble& D )
	{
		return UI8 / D.Value;
	}

	/* float */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt / int64" )
	static float KeshUE4FTFloatDivideInt64( float F, const FKeshInt64& I64 )
	{
		return F / I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 / flt" )
	static float FKeshInt64DivideFloat( const FKeshInt64& I64, float F )
	{
		return I64.Value / F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt / uint64" )
	static float KeshUE4FTFloatDivideUInt64( float F, const FKeshUInt64& UI64 )
	{
		return F / UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 / flt" )
	static float KeshUE4FTUInt64DivideFloat( const FKeshUInt64& UI64, float F )
	{
		return UI64.Value / F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt / uint32" )
	static float KeshUE4FTFloatDivideUInt32( float F, const FKeshUInt32& UI32 )
	{
		return F / UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 / flt" )
	static float FKeshUInt32DivideFloat( const FKeshUInt32& UI32, float F )
	{
		return UI32.Value / F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt / int16" )
	static float KeshUE4FTFloatDivideInt16( float F, const FKeshInt16& I16 )
	{
		return F / I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 / flt" )
	static float FKeshInt16DivideFloat( const FKeshInt16& I16, float F )
	{
		return I16.Value / F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt / uint16" )
	static float KeshUE4FTFloatDivideUInt16( float F, const FKeshUInt16& UI16 )
	{
		return F / UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 / flt" )
	static float FKeshUInt16DivideFloat( const FKeshUInt16& UI16, float F )
	{
		return UI16.Value / F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt / int8" )
	static float KeshUE4FTFloatDivideInt8( float F, const FKeshInt8& I8 )
	{
		return F / I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 / flt" )
	static float FKeshInt8DivideFloat( const FKeshInt8& I8, float F )
	{
		return I8.Value / F;
	}

	/* Int 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 / int64" )
	static FKeshInt64 FKeshInt64DivideInt64( const FKeshInt64& I641, const FKeshInt64& I642 )
	{
		return I641.Value / I642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 / uint64" )
	static FKeshInt64 FKeshInt64DivideUInt64( const FKeshInt64& I64, const FKeshUInt64& UI64 )
	{
		return I64.Value / UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 / int64" )
	static FKeshInt64 KeshUE4FTUInt64DivideInt64( const FKeshUInt64& UI64, const FKeshInt64& I64 )
	{
		return UI64.Value / I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 / int32" )
	static FKeshInt64 FKeshInt64DivideInt32( const FKeshInt64& I64, int32 I32 )
	{
		return I64.Value / I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 / int64" )
	static FKeshInt64 KeshUE4FTInt32DivideInt64( int32 I32, const FKeshInt64& I64 )
	{
		return I32 / I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 / uint32" )
	static FKeshInt64 FKeshInt64DivideUInt32( const FKeshInt64& I64, const FKeshUInt32& UI32 )
	{
		return I64.Value / UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 / int64" )
	static FKeshInt64 FKeshUInt32DivideInt64( const FKeshUInt32& UI32, const FKeshInt64& I64 )
	{
		return UI32.Value / I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 / int16" )
	static FKeshInt64 FKeshInt64DivideInt16( const FKeshInt64& I64, const FKeshInt16& I16 )
	{
		return I64.Value / I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 / int64" )
	static FKeshInt64 FKeshInt16DivideInt64( const FKeshInt16& I16, const FKeshInt64& I64 )
	{
		return I16.Value / I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 / uint16" )
	static FKeshInt64 FKeshInt64DivideUInt16( const FKeshInt64& I64, const FKeshUInt16& UI16 )
	{
		return I64.Value / UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 / int64" )
	static FKeshInt64 FKeshUInt16DivideInt64( const FKeshUInt16& UI16, const FKeshInt64& I64 )
	{
		return UI16.Value / I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 / int8" )
	static FKeshInt64 FKeshInt64DivideInt8( const FKeshInt64& I64, const FKeshInt8& I8 )
	{
		return I64.Value / I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 / int64" )
	static FKeshInt64 FKeshInt8DivideInt64( const FKeshInt8& I8, const FKeshInt64& I64 )
	{
		return I8.Value / I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 / uint8" )
	static FKeshInt64 FKeshInt64DivideUInt8( const FKeshInt64& I64, uint8 UI8 )
	{
		return I64.Value / UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 / int64" )
	static FKeshInt64 KeshUE4FTUInt8DivideInt64( uint8 UI8, const FKeshInt64& I64 )
	{
		return UI8 / I64.Value;
	}

	/* UInt 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 / uint64" )
	static FKeshUInt64 KeshUE4FTUInt64DivideUInt64( const FKeshUInt64& UI641, const FKeshUInt64& UI642 )
	{
		return UI641.Value / UI642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 / int32" )
	static FKeshUInt64 KeshUE4FTUInt64DivideInt32( const FKeshUInt64& UI64, int32 I32 )
	{
		return UI64.Value / I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 / uint64" )
	static FKeshUInt64 KeshUE4FTUInt32DivideInt64( int32 I32, const FKeshUInt64& UI64 )
	{
		return I32 / UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 / uint32" )
	static FKeshUInt64 KeshUE4FTUInt64DivideUInt32( const FKeshUInt64& UI64, const FKeshUInt32& UI32 )
	{
		return UI64.Value / UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 / uint64" )
	static FKeshUInt64 KeshUE4FTUUInt32DivideInt64( const FKeshUInt32& UI32, const FKeshUInt64& UI64 )
	{
		return UI32.Value / UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 / int16" )
	static FKeshUInt64 KeshUE4FTUInt64DivideInt16( const FKeshUInt64& UI64, const FKeshInt16& I16 )
	{
		return UI64.Value / I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 / uint64" )
	static FKeshUInt64 FKeshInt16DivideUInt64( const FKeshInt16& I16, const FKeshUInt64& UI64 )
	{
		return I16.Value / UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 / uint16" )
	static FKeshUInt64 KeshUE4FTUInt64DivideUInt16( const FKeshUInt64& UI64, const FKeshUInt16& UI16 )
	{
		return UI64.Value / UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 / uint64" )
	static FKeshUInt64 FKeshUInt16DivideUInt64( const FKeshUInt16& UI16, const FKeshUInt64& UI64 )
	{
		return UI16.Value / UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 / int8" )
	static FKeshUInt64 KeshUE4FTUInt64DivideInt8( const FKeshUInt64& UI64, const FKeshInt8& I8 )
	{
		return UI64.Value / I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 / uint64" )
	static FKeshUInt64 FKeshInt8DivideUInt64( const FKeshInt8& I8, const FKeshUInt64& UI64 )
	{
		return I8.Value / UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 / uint8" )
	static FKeshUInt64 KeshUE4FTUInt64DivideUInt8( const FKeshUInt64& UI64, uint8 UI8 )
	{
		return UI64.Value / UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 / uint64" )
	static FKeshUInt64 KeshUE4FTUInt8DivideUInt64( uint8 UI8, const FKeshUInt64& UI64 )
	{
		return UI8 / UI64.Value;
	}

	/* Int 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 / uint32" )
	static int32 KeshUE4FTInt32DivideUInt32( int32 I32, const FKeshUInt32& UI32 )
	{
		return I32 / UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 / int32" )
	static int32 FKeshUInt32DivideInt32( const FKeshUInt32& UI32, int32 I32 )
	{
		return UI32.Value / I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 / int16" )
	static int32 KeshUE4FTInt32DivideInt16( int32 I32, const FKeshInt16& I16 )
	{
		return I32 / I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 / int32" )
	static int32 FKeshInt16DivideInt32( const FKeshInt16& I16, int32 I32 )
	{
		return I16.Value / I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 / uint16" )
	static int32 KeshUE4FTInt32DivideUInt16( int32 I32, const FKeshUInt16& UI16 )
	{
		return I32 / UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 / int32" )
	static int32 FKeshUInt16DivideInt32( const FKeshUInt16& UI16, int32 I32 )
	{
		return UI16.Value / I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 / int8" )
	static int32 KeshUE4FTInt32DivideInt8( int32 I32, const FKeshInt8& I8 )
	{
		return I32 / I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 / int32" )
	static int32 FKeshInt8DivideInt32( const FKeshInt8& I8, int32 I32 )
	{
		return I8.Value / I32;
	}

	/* UInt 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 / uint32" )
	static FKeshUInt32 FKeshUInt32DivideUInt32( const FKeshUInt32& UI321, const FKeshUInt32& UI322 )
	{
		return UI321.Value / UI322.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 / int16" )
	static FKeshUInt32 FKeshUInt32DivideInt16( const FKeshUInt32& UI32, const FKeshInt16& I16 )
	{
		return UI32.Value / I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 / uint32" )
	static FKeshUInt32 FKeshInt16DivideUInt32( const FKeshInt16& I16, const FKeshUInt32& UI32 )
	{
		return I16.Value / UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 / uint16" )
	static FKeshUInt32 FKeshUInt32DivideUInt16( const FKeshUInt32& UI32, const FKeshUInt16& UI16 )
	{
		return UI32.Value / UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 / uint32" )
	static FKeshUInt32 FKeshUInt16DivideUInt32( const FKeshUInt16& UI16, const FKeshUInt32& UI32 )
	{
		return UI16.Value / UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 / int8" )
	static FKeshUInt32 FKeshUInt32DivideInt8( const FKeshUInt32& UI32, const FKeshInt8& I8 )
	{
		return UI32.Value / I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 / uint32" )
	static FKeshUInt32 FKeshInt8DivideUInt32( const FKeshInt8& I8, const FKeshUInt32& UI32 )
	{
		return I8.Value / UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 / uint8" )
	static FKeshUInt32 FKeshUInt32DivideUInt8( const FKeshUInt32& UI32, uint8 UI8 )
	{
		return UI32.Value / UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 / uint32" )
	static FKeshUInt32 KeshUE4FTUInt8DivideUInt32( uint8 UI8, const FKeshUInt32& UI32 )
	{
		return UI8 / UI32.Value;
	}

	/* Int 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 / int16" )
	static FKeshInt16 FKeshInt16DivideInt16( const FKeshInt16& I161, const FKeshInt16& I162 )
	{
		return I161.Value / I162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 / uint16" )
	static FKeshInt16 FKeshInt16DivideUInt16( const FKeshInt16& I16, const FKeshUInt16& UI16 )
	{
		return I16.Value / UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 / int16" )
	static FKeshInt16 FKeshUInt16DivideInt16( const FKeshUInt16& UI16, const FKeshInt16& I16 )
	{
		return UI16.Value / I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 / int8" )
	static FKeshInt16 FKeshInt16DivideInt8( const FKeshInt16& I16, const FKeshInt8& I8 )
	{
		return I16.Value / I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 / int16" )
	static FKeshInt16 FKeshInt8DivideInt16( const FKeshInt8& I8, const FKeshInt16& I16 )
	{
		return I8.Value / I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 / uint8" )
	static FKeshInt16 FKeshInt16DivideUInt8( const FKeshInt16& I16, uint8 UI8 )
	{
		return I16.Value / UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 / int16" )
	static FKeshInt16 KeshUE4FTUInt8DivideInt16( uint8 UI8, const FKeshInt16& I16 )
	{
		return UI8 / I16.Value;
	}

	/* UInt 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 / uint16" )
	static FKeshUInt16 FKeshUInt16DivideUUInt16( const FKeshUInt16& UI161, const FKeshUInt16& UI162 )
	{
		return UI161.Value / UI162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 / int8" )
	static FKeshUInt16 FKeshUInt16DivideInt8( const FKeshUInt16& UI16, const FKeshInt8& I8 )
	{
		return UI16.Value / I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 / uint16" )
	static FKeshUInt16 FKeshInt8DivideUInt16( const FKeshInt8& I8, const FKeshUInt16& UI16 )
	{
		return I8.Value / UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 / uint8" )
	static FKeshUInt16 FKeshUInt16DivideUInt8( const FKeshUInt16& UI16, uint8 UI8 )
	{
		return UI16.Value / UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 / uint16" )
	static FKeshUInt16 KeshUE4FTUInt8DivideUInt16( uint8 UI8, const FKeshUInt16& UI16 )
	{
		return UI8 / UI16.Value;
	}

	/* Int 8 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 / int8" )
	static FKeshInt8 FKeshInt8DivideInt8( const FKeshInt8& I81, const FKeshInt8& I82 )
	{
		return I81.Value / I82.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 / uint8" )
	static FKeshInt8 FKeshInt8DivideUInt8( const FKeshInt8& I8, uint8 UI8 )
	{
		return I8.Value / UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 / int8" )
	static FKeshInt8 KeshUE4FTUInt8DivideInt8( uint8 UI8, const FKeshInt8& I8 )
	{
		return UI8 / I8.Value;
	}


	/**********/
	/* Equals */
	/**********/

	/* Double */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl == dbl" )
	static bool KeshUE4FTDoubleEqualsDouble( const FKeshDouble& D1, const FKeshDouble& D2 )
	{
		return D1.Value == D2.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl == flt" )
	static bool KeshUE4FTDoubleEqualsFloat( const FKeshDouble& D, float F )
	{
		return D.Value == F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt == dbl" )
	static bool KeshUE4FTFloatEqualsDouble( float F, const FKeshDouble& D )
	{
		return F == D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl == int64" )
	static bool KeshUE4FTDoubleEqualsInt64( const FKeshDouble& D, const FKeshInt64& I64 )
	{
		return D.Value == I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 == dbl" )
	static bool FKeshInt64EqualsDouble( const FKeshInt64& I64, const FKeshDouble& D )
	{
		return I64.Value == D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl == uint64" )
	static bool KeshUE4FTDoubleEqualsUInt64( const FKeshDouble& D, const FKeshUInt64& UI64 )
	{
		return D.Value == UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 == dbl" )
	static bool KeshUE4FTUInt64EqualsDouble( const FKeshUInt64& UI64, const FKeshDouble& D )
	{
		return UI64.Value == D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl == int32" )
	static bool KeshUE4FTDoubleEqualsInt32( const FKeshDouble& D, int32 I32 )
	{
		return D.Value == I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 == dbl" )
	static bool KeshUE4FTInt32EqualsDouble( int32 I32, const FKeshDouble& D )
	{
		return I32 == D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl == uint32" )
	static bool KeshUE4FTDoubleEqualsUInt32( const FKeshDouble& D, const FKeshUInt32& UI32 )
	{
		return D.Value == UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 == dbl" )
	static bool FKeshUInt32EqualsDouble( const FKeshUInt32& UI32, const FKeshDouble& D )
	{
		return UI32.Value == D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl == int16" )
	static bool KeshUE4FTDoubleEqualsInt16( const FKeshDouble& D, const FKeshInt16& I16 )
	{
		return D.Value == I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 == dbl" )
	static bool FKeshInt16EqualsDouble( const FKeshInt16& I16, const FKeshDouble& D )
	{
		return I16.Value == D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl == uint16" )
	static bool KeshUE4FTDoubleEqualsUInt16( const FKeshDouble& D, const FKeshUInt16& UI16 )
	{
		return D.Value == UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 == dbl" )
	static bool FKeshUInt16EqualsDouble( const FKeshUInt16& UI16, const FKeshDouble& D )
	{
		return UI16.Value == D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl == int8" )
	static bool KeshUE4FTDoubleEqualsInt8( const FKeshDouble& D, const FKeshInt8& I8 )
	{
		return D.Value == I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 == dbl" )
	static bool FKeshInt8EqualsDouble( const FKeshInt8& I8, const FKeshDouble& D )
	{
		return I8.Value == D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl == uint8" )
	static bool KeshUE4FTDoubleEqualsUInt8( const FKeshDouble& D, uint8 UI8 )
	{
		return D.Value == UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 == dbl" )
	static bool KeshUE4FTUInt8EqualsDouble( uint8 UI8, const FKeshDouble& D )
	{
		return UI8 == D.Value;
	}

	/* float */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt == int64" )
	static bool KeshUE4FTFloatEqualsInt64( float F, const FKeshInt64& I64 )
	{
		return F == I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 == flt" )
	static bool FKeshInt64EqualsFloat( const FKeshInt64& I64, float F )
	{
		return I64.Value == F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt == uint64" )
	static bool KeshUE4FTFloatEqualsUInt64( float F, const FKeshUInt64& UI64 )
	{
		return F == UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 == flt" )
	static bool KeshUE4FTUInt64EqualsFloat( const FKeshUInt64& UI64, float F )
	{
		return UI64.Value == F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt == uint32" )
	static bool KeshUE4FTFloatEqualsUInt32( float F, const FKeshUInt32& UI32 )
	{
		return F == UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 == flt" )
	static bool FKeshUInt32EqualsFloat( const FKeshUInt32& UI32, float F )
	{
		return UI32.Value == F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt == int16" )
	static bool KeshUE4FTFloatEqualsInt16( float F, const FKeshInt16& I16 )
	{
		return F == I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 == flt" )
	static bool FKeshInt16EqualsFloat( const FKeshInt16& I16, float F )
	{
		return I16.Value == F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt == uint16" )
	static bool KeshUE4FTFloatEqualsUInt16( float F, const FKeshUInt16& UI16 )
	{
		return F == UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 == flt" )
	static bool FKeshUInt16EqualsFloat( const FKeshUInt16& UI16, float F )
	{
		return UI16.Value == F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt == int8" )
	static bool KeshUE4FTFloatEqualsInt8( float F, const FKeshInt8& I8 )
	{
		return F == I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 == flt" )
	static bool FKeshInt8EqualsFloat( const FKeshInt8& I8, float F )
	{
		return I8.Value == F;
	}

	/* Int 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 == int64" )
	static bool FKeshInt64EqualsInt64( const FKeshInt64& I641, const FKeshInt64& I642 )
	{
		return I641.Value == I642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 == uint64" )
	static bool FKeshInt64EqualsUInt64( const FKeshInt64& I64, const FKeshUInt64& UI64 )
	{
		return I64.Value == UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 == int64" )
	static bool KeshUE4FTUInt64EqualsInt64( const FKeshUInt64& UI64, const FKeshInt64& I64 )
	{
		return UI64.Value == I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 == int32" )
	static bool FKeshInt64EqualsInt32( const FKeshInt64& I64, int32 I32 )
	{
		return I64.Value == I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 == int64" )
	static bool KeshUE4FTInt32EqualsInt64( int32 I32, const FKeshInt64& I64 )
	{
		return I32 == I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 == uint32" )
	static bool FKeshInt64EqualsUInt32( const FKeshInt64& I64, const FKeshUInt32& UI32 )
	{
		return I64.Value == UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 == int64" )
	static bool FKeshUInt32EqualsInt64( const FKeshUInt32& UI32, const FKeshInt64& I64 )
	{
		return UI32.Value == I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 == int16" )
	static bool FKeshInt64EqualsInt16( const FKeshInt64& I64, const FKeshInt16& I16 )
	{
		return I64.Value == I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 == int64" )
	static bool FKeshInt16EqualsInt64( const FKeshInt16& I16, const FKeshInt64& I64 )
	{
		return I16.Value == I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 == uint16" )
	static bool FKeshInt64EqualsUInt16( const FKeshInt64& I64, const FKeshUInt16& UI16 )
	{
		return I64.Value == UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 == int64" )
	static bool FKeshUInt16EqualsInt64( const FKeshUInt16& UI16, const FKeshInt64& I64 )
	{
		return UI16.Value == I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 == int8" )
	static bool FKeshInt64EqualsInt8( const FKeshInt64& I64, const FKeshInt8& I8 )
	{
		return I64.Value == I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 == int64" )
	static bool FKeshInt8EqualsInt64( const FKeshInt8& I8, const FKeshInt64& I64 )
	{
		return I8.Value == I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 == uint8" )
	static bool FKeshInt64EqualsUInt8( const FKeshInt64& I64, uint8 UI8 )
	{
		return I64.Value == UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 == int64" )
	static bool KeshUE4FTUInt8EqualsInt64( uint8 UI8, const FKeshInt64& I64 )
	{
		return UI8 == I64.Value;
	}

	/* UInt 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 == uint64" )
	static bool KeshUE4FTUInt64EqualsUInt64( const FKeshUInt64& UI641, const FKeshUInt64& UI642 )
	{
		return UI641.Value == UI642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 == int32" )
	static bool KeshUE4FTUInt64EqualsInt32( const FKeshUInt64& UI64, int32 I32 )
	{
		return UI64.Value == I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 == uint64" )
	static bool KeshUE4FTUInt32EqualsInt64( int32 I32, const FKeshUInt64& UI64 )
	{
		return I32 == UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 == uint32" )
	static bool KeshUE4FTUInt64EqualsUInt32( const FKeshUInt64& UI64, const FKeshUInt32& UI32 )
	{
		return UI64.Value == UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 == uint64" )
	static bool KeshUE4FTUUInt32EqualsInt64( const FKeshUInt32& UI32, const FKeshUInt64& UI64 )
	{
		return UI32.Value == UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 == int16" )
	static bool KeshUE4FTUInt64EqualsInt16( const FKeshUInt64& UI64, const FKeshInt16& I16 )
	{
		return UI64.Value == I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 == uint64" )
	static bool FKeshInt16EqualsUInt64( const FKeshInt16& I16, const FKeshUInt64& UI64 )
	{
		return I16.Value == UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 == uint16" )
	static bool KeshUE4FTUInt64EqualsUInt16( const FKeshUInt64& UI64, const FKeshUInt16& UI16 )
	{
		return UI64.Value == UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 == uint64" )
	static bool FKeshUInt16EqualsUInt64( const FKeshUInt16& UI16, const FKeshUInt64& UI64 )
	{
		return UI16.Value == UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 == int8" )
	static bool KeshUE4FTUInt64EqualsInt8( const FKeshUInt64& UI64, const FKeshInt8& I8 )
	{
		return UI64.Value == I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 == uint64" )
	static bool FKeshInt8EqualsUInt64( const FKeshInt8& I8, const FKeshUInt64& UI64 )
	{
		return I8.Value == UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 == uint8" )
	static bool KeshUE4FTUInt64EqualsUInt8( const FKeshUInt64& UI64, uint8 UI8 )
	{
		return UI64.Value == UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 == uint64" )
	static bool KeshUE4FTUInt8EqualsUInt64( uint8 UI8, const FKeshUInt64& UI64 )
	{
		return UI8 == UI64.Value;
	}

	/* Int 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 == uint32" )
	static bool KeshUE4FTInt32EqualsUInt32( int32 I32, const FKeshUInt32& UI32 )
	{
		return I32 == UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 == int32" )
	static bool FKeshUInt32EqualsInt32( const FKeshUInt32& UI32, int32 I32 )
	{
		return UI32.Value == I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 == int16" )
	static bool KeshUE4FTInt32EqualsInt16( int32 I32, const FKeshInt16& I16 )
	{
		return I32 == I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 == int32" )
	static bool FKeshInt16EqualsInt32( const FKeshInt16& I16, int32 I32 )
	{
		return I16.Value == I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 == uint16" )
	static bool KeshUE4FTInt32EqualsUInt16( int32 I32, const FKeshUInt16& UI16 )
	{
		return I32 == UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 == int32" )
	static bool FKeshUInt16EqualsInt32( const FKeshUInt16& UI16, int32 I32 )
	{
		return UI16.Value == I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 == int8" )
	static bool KeshUE4FTInt32EqualsInt8( int32 I32, const FKeshInt8& I8 )
	{
		return I32 == I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 == int32" )
	static bool FKeshInt8EqualsInt32( const FKeshInt8& I8, int32 I32 )
	{
		return I8.Value == I32;
	}

	/* UInt 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 == uint32" )
	static bool FKeshUInt32EqualsUInt32( const FKeshUInt32& UI321, const FKeshUInt32& UI322 )
	{
		return UI321.Value == UI322.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 == int16" )
	static bool FKeshUInt32EqualsInt16( const FKeshUInt32& UI32, const FKeshInt16& I16 )
	{
		return UI32.Value == I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 == uint32" )
	static bool FKeshInt16EqualsUInt32( const FKeshInt16& I16, const FKeshUInt32& UI32 )
	{
		return I16.Value == UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 == uint16" )
	static bool FKeshUInt32EqualsUInt16( const FKeshUInt32& UI32, const FKeshUInt16& UI16 )
	{
		return UI32.Value == UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 == uint32" )
	static bool FKeshUInt16EqualsUInt32( const FKeshUInt16& UI16, const FKeshUInt32& UI32 )
	{
		return UI16.Value == UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 == int8" )
	static bool FKeshUInt32EqualsInt8( const FKeshUInt32& UI32, const FKeshInt8& I8 )
	{
		return UI32.Value == I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 == uint32" )
	static bool FKeshInt8EqualsUInt32( const FKeshInt8& I8, const FKeshUInt32& UI32 )
	{
		return I8.Value == UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 == uint8" )
	static bool FKeshUInt32EqualsUInt8( const FKeshUInt32& UI32, uint8 UI8 )
	{
		return UI32.Value == UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 == uint32" )
	static bool KeshUE4FTUInt8EqualsUInt32( uint8 UI8, const FKeshUInt32& UI32 )
	{
		return UI8 == UI32.Value;
	}

	/* Int 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 == int16" )
	static bool FKeshInt16EqualsInt16( const FKeshInt16& I161, const FKeshInt16& I162 )
	{
		return I161.Value == I162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 == uint16" )
	static bool FKeshInt16EqualsUInt16( const FKeshInt16& I16, const FKeshUInt16& UI16 )
	{
		return I16.Value == UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 == int16" )
	static bool FKeshUInt16EqualsInt16( const FKeshUInt16& UI16, const FKeshInt16& I16 )
	{
		return UI16.Value == I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 == int8" )
	static bool FKeshInt16EqualsInt8( const FKeshInt16& I16, const FKeshInt8& I8 )
	{
		return I16.Value == I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 == int16" )
	static bool FKeshInt8EqualsInt16( const FKeshInt8& I8, const FKeshInt16& I16 )
	{
		return I8.Value == I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 == uint8" )
	static bool FKeshInt16EqualsUInt8( const FKeshInt16& I16, uint8 UI8 )
	{
		return I16.Value == UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 == int16" )
	static bool KeshUE4FTUInt8EqualsInt16( uint8 UI8, const FKeshInt16& I16 )
	{
		return UI8 == I16.Value;
	}

	/* UInt 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 == uint16" )
	static bool FKeshUInt16EqualsUUInt16( const FKeshUInt16& UI161, const FKeshUInt16& UI162 )
	{
		return UI161.Value == UI162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 == int8" )
	static bool FKeshUInt16EqualsInt8( const FKeshUInt16& UI16, const FKeshInt8& I8 )
	{
		return UI16.Value == I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 == uint16" )
	static bool FKeshInt8EqualsUInt16( const FKeshInt8& I8, const FKeshUInt16& UI16 )
	{
		return I8.Value == UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 == uint8" )
	static bool FKeshUInt16EqualsUInt8( const FKeshUInt16& UI16, uint8 UI8 )
	{
		return UI16.Value == UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 == uint16" )
	static bool KeshUE4FTUInt8EqualsUInt16( uint8 UI8, const FKeshUInt16& UI16 )
	{
		return UI8 == UI16.Value;
	}

	/* Int 8 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 == int8" )
	static bool FKeshInt8EqualsInt8( const FKeshInt8& I81, const FKeshInt8& I82 )
	{
		return I81.Value == I82.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 == uint8" )
	static bool FKeshInt8EqualsUInt8( const FKeshInt8& I8, uint8 UI8 )
	{
		return I8.Value == UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 == int8" )
	static bool KeshUE4FTUInt8EqualsInt8( uint8 UI8, const FKeshInt8& I8 )
	{
		return UI8 == I8.Value;
	}


	/*************/
	/* NotEquals */
	/*************/

	/* Double */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl != dbl" )
	static bool KeshUE4FTDoubleNotEqualsDouble( const FKeshDouble& D1, const FKeshDouble& D2 )
	{
		return D1.Value != D2.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl != flt" )
	static bool KeshUE4FTDoubleNotEqualsFloat( const FKeshDouble& D, float F )
	{
		return D.Value != F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt != dbl" )
	static bool KeshUE4FTFloatNotEqualsDouble( float F, const FKeshDouble& D )
	{
		return F != D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl != int64" )
	static bool KeshUE4FTDoubleNotEqualsInt64( const FKeshDouble& D, const FKeshInt64& I64 )
	{
		return D.Value != I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 != dbl" )
	static bool FKeshInt64NotEqualsDouble( const FKeshInt64& I64, const FKeshDouble& D )
	{
		return I64.Value != D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl != uint64" )
	static bool KeshUE4FTDoubleNotEqualsUInt64( const FKeshDouble& D, const FKeshUInt64& UI64 )
	{
		return D.Value != UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 != dbl" )
	static bool KeshUE4FTUInt64NotEqualsDouble( const FKeshUInt64& UI64, const FKeshDouble& D )
	{
		return UI64.Value != D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl != int32" )
	static bool KeshUE4FTDoubleNotEqualsInt32( const FKeshDouble& D, int32 I32 )
	{
		return D.Value != I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 != dbl" )
	static bool KeshUE4FTInt32NotEqualsDouble( int32 I32, const FKeshDouble& D )
	{
		return I32 != D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl != uint32" )
	static bool KeshUE4FTDoubleNotEqualsUInt32( const FKeshDouble& D, const FKeshUInt32& UI32 )
	{
		return D.Value != UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 != dbl" )
	static bool FKeshUInt32NotEqualsDouble( const FKeshUInt32& UI32, const FKeshDouble& D )
	{
		return UI32.Value != D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl != int16" )
	static bool KeshUE4FTDoubleNotEqualsInt16( const FKeshDouble& D, const FKeshInt16& I16 )
	{
		return D.Value != I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 != dbl" )
	static bool FKeshInt16NotEqualsDouble( const FKeshInt16& I16, const FKeshDouble& D )
	{
		return I16.Value != D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl != uint16" )
	static bool KeshUE4FTDoubleNotEqualsUInt16( const FKeshDouble& D, const FKeshUInt16& UI16 )
	{
		return D.Value != UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 != dbl" )
	static bool FKeshUInt16NotEqualsDouble( const FKeshUInt16& UI16, const FKeshDouble& D )
	{
		return UI16.Value != D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl != int8" )
	static bool KeshUE4FTDoubleNotEqualsInt8( const FKeshDouble& D, const FKeshInt8& I8 )
	{
		return D.Value != I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 != dbl" )
	static bool FKeshInt8NotEqualsDouble( const FKeshInt8& I8, const FKeshDouble& D )
	{
		return I8.Value != D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl != uint8" )
	static bool KeshUE4FTDoubleNotEqualsUInt8( const FKeshDouble& D, uint8 UI8 )
	{
		return D.Value != UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 != dbl" )
	static bool KeshUE4FTUInt8NotEqualsDouble( uint8 UI8, const FKeshDouble& D )
	{
		return UI8 != D.Value;
	}

	/* float */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt != int64" )
	static bool KeshUE4FTFloatNotEqualsInt64( float F, const FKeshInt64& I64 )
	{
		return F != I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 != flt" )
	static bool FKeshInt64NotEqualsFloat( const FKeshInt64& I64, float F )
	{
		return I64.Value != F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt != uint64" )
	static bool KeshUE4FTFloatNotEqualsUInt64( float F, const FKeshUInt64& UI64 )
	{
		return F != UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 != flt" )
	static bool KeshUE4FTUInt64NotEqualsFloat( const FKeshUInt64& UI64, float F )
	{
		return UI64.Value != F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt != uint32" )
	static bool KeshUE4FTFloatNotEqualsUInt32( float F, const FKeshUInt32& UI32 )
	{
		return F != UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 != flt" )
	static bool FKeshUInt32NotEqualsFloat( const FKeshUInt32& UI32, float F )
	{
		return UI32.Value != F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt != int16" )
	static bool KeshUE4FTFloatNotEqualsInt16( float F, const FKeshInt16& I16 )
	{
		return F != I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 != flt" )
	static bool FKeshInt16NotEqualsFloat( const FKeshInt16& I16, float F )
	{
		return I16.Value != F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt != uint16" )
	static bool KeshUE4FTFloatNotEqualsUInt16( float F, const FKeshUInt16& UI16 )
	{
		return F != UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 != flt" )
	static bool FKeshUInt16NotEqualsFloat( const FKeshUInt16& UI16, float F )
	{
		return UI16.Value != F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt != int8" )
	static bool KeshUE4FTFloatNotEqualsInt8( float F, const FKeshInt8& I8 )
	{
		return F != I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 != flt" )
	static bool FKeshInt8NotEqualsFloat( const FKeshInt8& I8, float F )
	{
		return I8.Value != F;
	}

	/* Int 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 != int64" )
	static bool FKeshInt64NotEqualsInt64( const FKeshInt64& I641, const FKeshInt64& I642 )
	{
		return I641.Value != I642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 != uint64" )
	static bool FKeshInt64NotEqualsUInt64( const FKeshInt64& I64, const FKeshUInt64& UI64 )
	{
		return I64.Value != UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 != int64" )
	static bool KeshUE4FTUInt64NotEqualsInt64( const FKeshUInt64& UI64, const FKeshInt64& I64 )
	{
		return UI64.Value != I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 != int32" )
	static bool FKeshInt64NotEqualsInt32( const FKeshInt64& I64, int32 I32 )
	{
		return I64.Value != I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 != int64" )
	static bool KeshUE4FTInt32NotEqualsInt64( int32 I32, const FKeshInt64& I64 )
	{
		return I32 != I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 != uint32" )
	static bool FKeshInt64NotEqualsUInt32( const FKeshInt64& I64, const FKeshUInt32& UI32 )
	{
		return I64.Value != UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 != int64" )
	static bool FKeshUInt32NotEqualsInt64( const FKeshUInt32& UI32, const FKeshInt64& I64 )
	{
		return UI32.Value != I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 != int16" )
	static bool FKeshInt64NotEqualsInt16( const FKeshInt64& I64, const FKeshInt16& I16 )
	{
		return I64.Value != I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 != int64" )
	static bool FKeshInt16NotEqualsInt64( const FKeshInt16& I16, const FKeshInt64& I64 )
	{
		return I16.Value != I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 != uint16" )
	static bool FKeshInt64NotEqualsUInt16( const FKeshInt64& I64, const FKeshUInt16& UI16 )
	{
		return I64.Value != UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 != int64" )
	static bool FKeshUInt16NotEqualsInt64( const FKeshUInt16& UI16, const FKeshInt64& I64 )
	{
		return UI16.Value != I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 != int8" )
	static bool FKeshInt64NotEqualsInt8( const FKeshInt64& I64, const FKeshInt8& I8 )
	{
		return I64.Value != I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 != int64" )
	static bool FKeshInt8NotEqualsInt64( const FKeshInt8& I8, const FKeshInt64& I64 )
	{
		return I8.Value != I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 != uint8" )
	static bool FKeshInt64NotEqualsUInt8( const FKeshInt64& I64, uint8 UI8 )
	{
		return I64.Value != UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 != int64" )
	static bool KeshUE4FTUInt8NotEqualsInt64( uint8 UI8, const FKeshInt64& I64 )
	{
		return UI8 != I64.Value;
	}

	/* UInt 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 != uint64" )
	static bool KeshUE4FTUInt64NotEqualsUInt64( const FKeshUInt64& UI641, const FKeshUInt64& UI642 )
	{
		return UI641.Value != UI642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 != int32" )
	static bool KeshUE4FTUInt64NotEqualsInt32( const FKeshUInt64& UI64, int32 I32 )
	{
		return UI64.Value != I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 != uint64" )
	static bool KeshUE4FTUInt32NotEqualsInt64( int32 I32, const FKeshUInt64& UI64 )
	{
		return I32 != UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 != uint32" )
	static bool KeshUE4FTUInt64NotEqualsUInt32( const FKeshUInt64& UI64, const FKeshUInt32& UI32 )
	{
		return UI64.Value != UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 != uint64" )
	static bool KeshUE4FTUUInt32NotEqualsInt64( const FKeshUInt32& UI32, const FKeshUInt64& UI64 )
	{
		return UI32.Value != UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 != int16" )
	static bool KeshUE4FTUInt64NotEqualsInt16( const FKeshUInt64& UI64, const FKeshInt16& I16 )
	{
		return UI64.Value != I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 != uint64" )
	static bool FKeshInt16NotEqualsUInt64( const FKeshInt16& I16, const FKeshUInt64& UI64 )
	{
		return I16.Value != UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 != uint16" )
	static bool KeshUE4FTUInt64NotEqualsUInt16( const FKeshUInt64& UI64, const FKeshUInt16& UI16 )
	{
		return UI64.Value != UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 != uint64" )
	static bool FKeshUInt16NotEqualsUInt64( const FKeshUInt16& UI16, const FKeshUInt64& UI64 )
	{
		return UI16.Value != UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 != int8" )
	static bool KeshUE4FTUInt64NotEqualsInt8( const FKeshUInt64& UI64, const FKeshInt8& I8 )
	{
		return UI64.Value != I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 != uint64" )
	static bool FKeshInt8NotEqualsUInt64( const FKeshInt8& I8, const FKeshUInt64& UI64 )
	{
		return I8.Value != UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 != uint8" )
	static bool KeshUE4FTUInt64NotEqualsUInt8( const FKeshUInt64& UI64, uint8 UI8 )
	{
		return UI64.Value != UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 != uint64" )
	static bool KeshUE4FTUInt8NotEqualsUInt64( uint8 UI8, const FKeshUInt64& UI64 )
	{
		return UI8 != UI64.Value;
	}

	/* Int 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 != uint32" )
	static bool KeshUE4FTInt32NotEqualsUInt32( int32 I32, const FKeshUInt32& UI32 )
	{
		return I32 != UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 != int32" )
	static bool FKeshUInt32NotEqualsInt32( const FKeshUInt32& UI32, int32 I32 )
	{
		return UI32.Value != I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 != int16" )
	static bool KeshUE4FTInt32NotEqualsInt16( int32 I32, const FKeshInt16& I16 )
	{
		return I32 != I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 != int32" )
	static bool FKeshInt16NotEqualsInt32( const FKeshInt16& I16, int32 I32 )
	{
		return I16.Value != I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 != uint16" )
	static bool KeshUE4FTInt32NotEqualsUInt16( int32 I32, const FKeshUInt16& UI16 )
	{
		return I32 != UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 != int32" )
	static bool FKeshUInt16NotEqualsInt32( const FKeshUInt16& UI16, int32 I32 )
	{
		return UI16.Value != I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 != int8" )
	static bool KeshUE4FTInt32NotEqualsInt8( int32 I32, const FKeshInt8& I8 )
	{
		return I32 != I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 != int32" )
	static bool FKeshInt8NotEqualsInt32( const FKeshInt8& I8, int32 I32 )
	{
		return I8.Value != I32;
	}

	/* UInt 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 != uint32" )
	static bool FKeshUInt32NotEqualsUInt32( const FKeshUInt32& UI321, const FKeshUInt32& UI322 )
	{
		return UI321.Value != UI322.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 != int16" )
	static bool FKeshUInt32NotEqualsInt16( const FKeshUInt32& UI32, const FKeshInt16& I16 )
	{
		return UI32.Value != I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 != uint32" )
	static bool FKeshInt16NotEqualsUInt32( const FKeshInt16& I16, const FKeshUInt32& UI32 )
	{
		return I16.Value != UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 != uint16" )
	static bool FKeshUInt32NotEqualsUInt16( const FKeshUInt32& UI32, const FKeshUInt16& UI16 )
	{
		return UI32.Value != UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 != uint32" )
	static bool FKeshUInt16NotEqualsUInt32( const FKeshUInt16& UI16, const FKeshUInt32& UI32 )
	{
		return UI16.Value != UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 != int8" )
	static bool FKeshUInt32NotEqualsInt8( const FKeshUInt32& UI32, const FKeshInt8& I8 )
	{
		return UI32.Value != I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 != uint32" )
	static bool FKeshInt8NotEqualsUInt32( const FKeshInt8& I8, const FKeshUInt32& UI32 )
	{
		return I8.Value != UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 != uint8" )
	static bool FKeshUInt32NotEqualsUInt8( const FKeshUInt32& UI32, uint8 UI8 )
	{
		return UI32.Value != UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 != uint32" )
	static bool KeshUE4FTUInt8NotEqualsUInt32( uint8 UI8, const FKeshUInt32& UI32 )
	{
		return UI8 != UI32.Value;
	}

	/* Int 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 != int16" )
	static bool FKeshInt16NotEqualsInt16( const FKeshInt16& I161, const FKeshInt16& I162 )
	{
		return I161.Value != I162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 != uint16" )
	static bool FKeshInt16NotEqualsUInt16( const FKeshInt16& I16, const FKeshUInt16& UI16 )
	{
		return I16.Value != UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 != int16" )
	static bool FKeshUInt16NotEqualsInt16( const FKeshUInt16& UI16, const FKeshInt16& I16 )
	{
		return UI16.Value != I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 != int8" )
	static bool FKeshInt16NotEqualsInt8( const FKeshInt16& I16, const FKeshInt8& I8 )
	{
		return I16.Value != I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 != int16" )
	static bool FKeshInt8NotEqualsInt16( const FKeshInt8& I8, const FKeshInt16& I16 )
	{
		return I8.Value != I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 != uint8" )
	static bool FKeshInt16NotEqualsUInt8( const FKeshInt16& I16, uint8 UI8 )
	{
		return I16.Value != UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 != int16" )
	static bool KeshUE4FTUInt8NotEqualsInt16( uint8 UI8, const FKeshInt16& I16 )
	{
		return UI8 != I16.Value;
	}

	/* UInt 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 != uint16" )
	static bool FKeshUInt16NotEqualsUUInt16( const FKeshUInt16& UI161, const FKeshUInt16& UI162 )
	{
		return UI161.Value != UI162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 != int8" )
	static bool FKeshUInt16NotEqualsInt8( const FKeshUInt16& UI16, const FKeshInt8& I8 )
	{
		return UI16.Value != I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 != uint16" )
	static bool FKeshInt8NotEqualsUInt16( const FKeshInt8& I8, const FKeshUInt16& UI16 )
	{
		return I8.Value != UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 != uint8" )
	static bool FKeshUInt16NotEqualsUInt8( const FKeshUInt16& UI16, uint8 UI8 )
	{
		return UI16.Value != UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 != uint16" )
	static bool KeshUE4FTUInt8NotEqualsUInt16( uint8 UI8, const FKeshUInt16& UI16 )
	{
		return UI8 != UI16.Value;
	}

	/* Int 8 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 != int8" )
	static bool FKeshInt8NotEqualsInt8( const FKeshInt8& I81, const FKeshInt8& I82 )
	{
		return I81.Value != I82.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 != uint8" )
	static bool FKeshInt8NotEqualsUInt8( const FKeshInt8& I8, uint8 UI8 )
	{
		return I8.Value != UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 != int8" )
	static bool KeshUE4FTUInt8NotEqualsInt8( uint8 UI8, const FKeshInt8& I8 )
	{
		return UI8 != I8.Value;
	}


	/***************/
	/* GreaterThan */
	/***************/

	/* Double */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl > dbl" )
	static bool KeshUE4FTDoubleGreaterThanDouble( const FKeshDouble& D1, const FKeshDouble& D2 )
	{
		return D1.Value > D2.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl > flt" )
	static bool KeshUE4FTDoubleGreaterThanFloat( const FKeshDouble& D, float F )
	{
		return D.Value > F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt > dbl" )
	static bool KeshUE4FTFloatGreaterThanDouble( float F, const FKeshDouble& D )
	{
		return F > D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl > int64" )
	static bool KeshUE4FTDoubleGreaterThanInt64( const FKeshDouble& D, const FKeshInt64& I64 )
	{
		return D.Value > I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 > dbl" )
	static bool FKeshInt64GreaterThanDouble( const FKeshInt64& I64, const FKeshDouble& D )
	{
		return I64.Value > D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl > uint64" )
	static bool KeshUE4FTDoubleGreaterThanUInt64( const FKeshDouble& D, const FKeshUInt64& UI64 )
	{
		return D.Value > UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 > dbl" )
	static bool KeshUE4FTUInt64GreaterThanDouble( const FKeshUInt64& UI64, const FKeshDouble& D )
	{
		return UI64.Value > D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl > int32" )
	static bool KeshUE4FTDoubleGreaterThanInt32( const FKeshDouble& D, int32 I32 )
	{
		return D.Value > I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 > dbl" )
	static bool KeshUE4FTInt32GreaterThanDouble( int32 I32, const FKeshDouble& D )
	{
		return I32 > D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl > uint32" )
	static bool KeshUE4FTDoubleGreaterThanUInt32( const FKeshDouble& D, const FKeshUInt32& UI32 )
	{
		return D.Value > UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 > dbl" )
	static bool FKeshUInt32GreaterThanDouble( const FKeshUInt32& UI32, const FKeshDouble& D )
	{
		return UI32.Value > D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl > int16" )
	static bool KeshUE4FTDoubleGreaterThanInt16( const FKeshDouble& D, const FKeshInt16& I16 )
	{
		return D.Value > I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 > dbl" )
	static bool FKeshInt16GreaterThanDouble( const FKeshInt16& I16, const FKeshDouble& D )
	{
		return I16.Value > D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl > uint16" )
	static bool KeshUE4FTDoubleGreaterThanUInt16( const FKeshDouble& D, const FKeshUInt16& UI16 )
	{
		return D.Value > UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 > dbl" )
	static bool FKeshUInt16GreaterThanDouble( const FKeshUInt16& UI16, const FKeshDouble& D )
	{
		return UI16.Value > D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl > int8" )
	static bool KeshUE4FTDoubleGreaterThanInt8( const FKeshDouble& D, const FKeshInt8& I8 )
	{
		return D.Value > I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 > dbl" )
	static bool FKeshInt8GreaterThanDouble( const FKeshInt8& I8, const FKeshDouble& D )
	{
		return I8.Value > D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl > uint8" )
	static bool KeshUE4FTDoubleGreaterThanUInt8( const FKeshDouble& D, uint8 UI8 )
	{
		return D.Value > UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 > dbl" )
	static bool KeshUE4FTUInt8GreaterThanDouble( uint8 UI8, const FKeshDouble& D )
	{
		return UI8 > D.Value;
	}

	/* float */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt > int64" )
	static bool KeshUE4FTFloatGreaterThanInt64( float F, const FKeshInt64& I64 )
	{
		return F > I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 > flt" )
	static bool FKeshInt64GreaterThanFloat( const FKeshInt64& I64, float F )
	{
		return I64.Value > F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt > uint64" )
	static bool KeshUE4FTFloatGreaterThanUInt64( float F, const FKeshUInt64& UI64 )
	{
		return F > UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 > flt" )
	static bool KeshUE4FTUInt64GreaterThanFloat( const FKeshUInt64& UI64, float F )
	{
		return UI64.Value > F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt > uint32" )
	static bool KeshUE4FTFloatGreaterThanUInt32( float F, const FKeshUInt32& UI32 )
	{
		return F > UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 > flt" )
	static bool FKeshUInt32GreaterThanFloat( const FKeshUInt32& UI32, float F )
	{
		return UI32.Value > F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt > int16" )
	static bool KeshUE4FTFloatGreaterThanInt16( float F, const FKeshInt16& I16 )
	{
		return F > I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 > flt" )
	static bool FKeshInt16GreaterThanFloat( const FKeshInt16& I16, float F )
	{
		return I16.Value > F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt > uint16" )
	static bool KeshUE4FTFloatGreaterThanUInt16( float F, const FKeshUInt16& UI16 )
	{
		return F > UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 > flt" )
	static bool FKeshUInt16GreaterThanFloat( const FKeshUInt16& UI16, float F )
	{
		return UI16.Value > F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt > int8" )
	static bool KeshUE4FTFloatGreaterThanInt8( float F, const FKeshInt8& I8 )
	{
		return F > I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 > flt" )
	static bool FKeshInt8GreaterThanFloat( const FKeshInt8& I8, float F )
	{
		return I8.Value > F;
	}

	/* Int 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 > int64" )
	static bool FKeshInt64GreaterThanInt64( const FKeshInt64& I641, const FKeshInt64& I642 )
	{
		return I641.Value > I642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 > uint64" )
	static bool FKeshInt64GreaterThanUInt64( const FKeshInt64& I64, const FKeshUInt64& UI64 )
	{
		if ( I64.Value < 0 )
			return false;

		return static_cast< uint64 >( I64.Value ) > UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 > int64" )
	static bool KeshUE4FTUInt64GreaterThanInt64( const FKeshUInt64& UI64, const FKeshInt64& I64 )
	{
		if ( I64.Value < 0 )
			return true;

		return UI64.Value > static_cast< uint64 >( I64.Value );
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 > int32" )
	static bool FKeshInt64GreaterThanInt32( const FKeshInt64& I64, int32 I32 )
	{
		return I64.Value > I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 > int64" )
	static bool KeshUE4FTInt32GreaterThanInt64( int32 I32, const FKeshInt64& I64 )
	{
		return I32 > I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 > uint32" )
	static bool FKeshInt64GreaterThanUInt32( const FKeshInt64& I64, const FKeshUInt32& UI32 )
	{
		return I64.Value > UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 > int64" )
	static bool FKeshUInt32GreaterThanInt64( const FKeshUInt32& UI32, const FKeshInt64& I64 )
	{
		return UI32.Value > I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 > int16" )
	static bool FKeshInt64GreaterThanInt16( const FKeshInt64& I64, const FKeshInt16& I16 )
	{
		return I64.Value > I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 > int64" )
	static bool FKeshInt16GreaterThanInt64( const FKeshInt16& I16, const FKeshInt64& I64 )
	{
		return I16.Value > I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 > uint16" )
	static bool FKeshInt64GreaterThanUInt16( const FKeshInt64& I64, const FKeshUInt16& UI16 )
	{
		return I64.Value > UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 > int64" )
	static bool FKeshUInt16GreaterThanInt64( const FKeshUInt16& UI16, const FKeshInt64& I64 )
	{
		return UI16.Value > I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 > int8" )
	static bool FKeshInt64GreaterThanInt8( const FKeshInt64& I64, const FKeshInt8& I8 )
	{
		return I64.Value > I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 > int64" )
	static bool FKeshInt8GreaterThanInt64( const FKeshInt8& I8, const FKeshInt64& I64 )
	{
		return I8.Value > I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 > uint8" )
	static bool FKeshInt64GreaterThanUInt8( const FKeshInt64& I64, uint8 UI8 )
	{
		return I64.Value > UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 > int64" )
	static bool KeshUE4FTUInt8GreaterThanInt64( uint8 UI8, const FKeshInt64& I64 )
	{
		return UI8 > I64.Value;
	}

	/* UInt 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 > uint64" )
	static bool KeshUE4FTUInt64GreaterThanUInt64( const FKeshUInt64& UI641, const FKeshUInt64& UI642 )
	{
		return UI641.Value > UI642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 > int32" )
	static bool KeshUE4FTUInt64GreaterThanInt32( const FKeshUInt64& UI64, int32 I32 )
	{
		return UI64.Value > I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 > uint64" )
	static bool KeshUE4FTUInt32GreaterThanInt64( int32 I32, const FKeshUInt64& UI64 )
	{
		return I32 > UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 > uint32" )
	static bool KeshUE4FTUInt64GreaterThanUInt32( const FKeshUInt64& UI64, const FKeshUInt32& UI32 )
	{
		return UI64.Value > UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 > uint64" )
	static bool KeshUE4FTUUInt32GreaterThanInt64( const FKeshUInt32& UI32, const FKeshUInt64& UI64 )
	{
		return UI32.Value > UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 > int16" )
	static bool KeshUE4FTUInt64GreaterThanInt16( const FKeshUInt64& UI64, const FKeshInt16& I16 )
	{
		return UI64.Value > I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 > uint64" )
	static bool FKeshInt16GreaterThanUInt64( const FKeshInt16& I16, const FKeshUInt64& UI64 )
	{
		return I16.Value > UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 > uint16" )
	static bool KeshUE4FTUInt64GreaterThanUInt16( const FKeshUInt64& UI64, const FKeshUInt16& UI16 )
	{
		return UI64.Value > UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 > uint64" )
	static bool FKeshUInt16GreaterThanUInt64( const FKeshUInt16& UI16, const FKeshUInt64& UI64 )
	{
		return UI16.Value > UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 > int8" )
	static bool KeshUE4FTUInt64GreaterThanInt8( const FKeshUInt64& UI64, const FKeshInt8& I8 )
	{
		return UI64.Value > I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 > uint64" )
	static bool FKeshInt8GreaterThanUInt64( const FKeshInt8& I8, const FKeshUInt64& UI64 )
	{
		return I8.Value > UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 > uint8" )
	static bool KeshUE4FTUInt64GreaterThanUInt8( const FKeshUInt64& UI64, uint8 UI8 )
	{
		return UI64.Value > UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 > uint64" )
	static bool KeshUE4FTUInt8GreaterThanUInt64( uint8 UI8, const FKeshUInt64& UI64 )
	{
		return UI8 > UI64.Value;
	}

	/* Int 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 > uint32" )
	static bool KeshUE4FTInt32GreaterThanUInt32( int32 I32, const FKeshUInt32& UI32 )
	{
		return I32 > UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 > int32" )
	static bool FKeshUInt32GreaterThanInt32( const FKeshUInt32& UI32, int32 I32 )
	{
		return UI32.Value > I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 > int16" )
	static bool KeshUE4FTInt32GreaterThanInt16( int32 I32, const FKeshInt16& I16 )
	{
		return I32 > I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 > int32" )
	static bool FKeshInt16GreaterThanInt32( const FKeshInt16& I16, int32 I32 )
	{
		return I16.Value > I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 > uint16" )
	static bool KeshUE4FTInt32GreaterThanUInt16( int32 I32, const FKeshUInt16& UI16 )
	{
		return I32 > UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 > int32" )
	static bool FKeshUInt16GreaterThanInt32( const FKeshUInt16& UI16, int32 I32 )
	{
		return UI16.Value > I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 > int8" )
	static bool KeshUE4FTInt32GreaterThanInt8( int32 I32, const FKeshInt8& I8 )
	{
		return I32 > I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 > int32" )
	static bool FKeshInt8GreaterThannt32( const FKeshInt8& I8, int32 I32 )
	{
		return I8.Value > I32;
	}

	/* UInt 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 > uint32" )
	static bool FKeshUInt32GreaterThanUInt32( const FKeshUInt32& UI321, const FKeshUInt32& UI322 )
	{
		return UI321.Value > UI322.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 > int16" )
	static bool FKeshUInt32GreaterThanInt16( const FKeshUInt32& UI32, const FKeshInt16& I16 )
	{
		return UI32.Value > I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 > uint32" )
	static bool FKeshInt16GreaterThanUInt32( const FKeshInt16& I16, const FKeshUInt32& UI32 )
	{
		return I16.Value > UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 > uint16" )
	static bool FKeshUInt32GreaterThanUInt16( const FKeshUInt32& UI32, const FKeshUInt16& UI16 )
	{
		return UI32.Value > UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 > uint32" )
	static bool FKeshUInt16GreaterThanUInt32( const FKeshUInt16& UI16, const FKeshUInt32& UI32 )
	{
		return UI16.Value > UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 > int8" )
	static bool FKeshUInt32GreaterThanInt8( const FKeshUInt32& UI32, const FKeshInt8& I8 )
	{
		return UI32.Value > I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 > uint32" )
	static bool FKeshInt8GreaterThanUInt32( const FKeshInt8& I8, const FKeshUInt32& UI32 )
	{
		return I8.Value > UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 > uint8" )
	static bool FKeshUInt32GreaterThanUInt8( const FKeshUInt32& UI32, uint8 UI8 )
	{
		return UI32.Value > UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 > uint32" )
	static bool KeshUE4FTUInt8GreaterThanUInt32( uint8 UI8, const FKeshUInt32& UI32 )
	{
		return UI8 > UI32.Value;
	}

	/* Int 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 > int16" )
	static bool FKeshInt16GreaterThanInt16( const FKeshInt16& I161, const FKeshInt16& I162 )
	{
		return I161.Value > I162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 > uint16" )
	static bool FKeshInt16GreaterThanUInt16( const FKeshInt16& I16, const FKeshUInt16& UI16 )
	{
		return I16.Value > UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 > int16" )
	static bool FKeshUInt16GreaterThanInt16( const FKeshUInt16& UI16, const FKeshInt16& I16 )
	{
		return UI16.Value > I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 > int8" )
	static bool FKeshInt16GreaterThanInt8( const FKeshInt16& I16, const FKeshInt8& I8 )
	{
		return I16.Value > I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 > int16" )
	static bool FKeshInt8GreaterThanInt16( const FKeshInt8& I8, const FKeshInt16& I16 )
	{
		return I8.Value > I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 > uint8" )
	static bool FKeshInt16GreaterThanUInt8( const FKeshInt16& I16, uint8 UI8 )
	{
		return I16.Value > UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 > int16" )
	static bool KeshUE4FTUInt8GreaterThanInt16( uint8 UI8, const FKeshInt16& I16 )
	{
		return UI8 > I16.Value;
	}

	/* UInt 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 > uint16" )
	static bool FKeshUInt16GreaterThanUUInt16( const FKeshUInt16& UI161, const FKeshUInt16& UI162 )
	{
		return UI161.Value > UI162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 > int8" )
	static bool FKeshUInt16GreaterThanInt8( const FKeshUInt16& UI16, const FKeshInt8& I8 )
	{
		return UI16.Value > I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 > uint16" )
	static bool FKeshInt8GreaterThanUInt16( const FKeshInt8& I8, const FKeshUInt16& UI16 )
	{
		return I8.Value > UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 > uint8" )
	static bool FKeshUInt16GreaterThanUInt8( const FKeshUInt16& UI16, uint8 UI8 )
	{
		return UI16.Value > UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 > uint16" )
	static bool KeshUE4FTUInt8GreaterThanUInt16( uint8 UI8, const FKeshUInt16& UI16 )
	{
		return UI8 > UI16.Value;
	}

	/* Int 8 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 > int8" )
	static bool FKeshInt8GreaterThanInt8( const FKeshInt8& I81, const FKeshInt8& I82 )
	{
		return I81.Value > I82.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 > uint8" )
	static bool FKeshInt8GreaterThanUInt8( const FKeshInt8& I8, uint8 UI8 )
	{
		return I8.Value > UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 > int8" )
	static bool KeshUE4FTUInt8GreaterThanInt8( uint8 UI8, const FKeshInt8& I8 )
	{
		return UI8 > I8.Value;
	}


	/************/
	/* LessThan */
	/***********/

	/* Double */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl < dbl" )
	static bool KeshUE4FTDoubleLessThanDouble( const FKeshDouble& D1, const FKeshDouble& D2 )
	{
		return D1.Value < D2.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl < flt" )
	static bool KeshUE4FTDoubleLessThanFloat( const FKeshDouble& D, float F )
	{
		return D.Value < F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt < dbl" )
	static bool KeshUE4FTFloatLessThanDouble( float F, const FKeshDouble& D )
	{
		return F < D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl < int64" )
	static bool KeshUE4FTDoubleLessThanInt64( const FKeshDouble& D, const FKeshInt64& I64 )
	{
		return D.Value < I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 < dbl" )
	static bool FKeshInt64LessThanDouble( const FKeshInt64& I64, const FKeshDouble& D )
	{
		return I64.Value < D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl < uint64" )
	static bool KeshUE4FTDoubleLessThanUInt64( const FKeshDouble& D, const FKeshUInt64& UI64 )
	{
		return D.Value < UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 < dbl" )
	static bool KeshUE4FTUInt64LessThanDouble( const FKeshUInt64& UI64, const FKeshDouble& D )
	{
		return UI64.Value < D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl < int32" )
	static bool KeshUE4FTDoubleLessThanInt32( const FKeshDouble& D, int32 I32 )
	{
		return D.Value < I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 < dbl" )
	static bool KeshUE4FTInt32LessThanDouble( int32 I32, const FKeshDouble& D )
	{
		return I32 < D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl < uint32" )
	static bool KeshUE4FTDoubleLessThanUInt32( const FKeshDouble& D, const FKeshUInt32& UI32 )
	{
		return D.Value < UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 < dbl" )
	static bool FKeshUInt32LessThanDouble( const FKeshUInt32& UI32, const FKeshDouble& D )
	{
		return UI32.Value < D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl < int16" )
	static bool KeshUE4FTDoubleLessThanInt16( const FKeshDouble& D, const FKeshInt16& I16 )
	{
		return D.Value < I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 < dbl" )
	static bool FKeshInt16LessThanDouble( const FKeshInt16& I16, const FKeshDouble& D )
	{
		return I16.Value < D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl < uint16" )
	static bool KeshUE4FTDoubleLessThanUInt16( const FKeshDouble& D, const FKeshUInt16& UI16 )
	{
		return D.Value < UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 < dbl" )
	static bool FKeshUInt16LessThanDouble( const FKeshUInt16& UI16, const FKeshDouble& D )
	{
		return UI16.Value < D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl < int8" )
	static bool KeshUE4FTDoubleLessThanInt8( const FKeshDouble& D, const FKeshInt8& I8 )
	{
		return D.Value < I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 < dbl" )
	static bool FKeshInt8LessThanDouble( const FKeshInt8& I8, const FKeshDouble& D )
	{
		return I8.Value < D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl < uint8" )
	static bool KeshUE4FTDoubleLessThanUInt8( const FKeshDouble& D, uint8 UI8 )
	{
		return D.Value < UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 < dbl" )
	static bool KeshUE4FTUInt8LessThanDouble( uint8 UI8, const FKeshDouble& D )
	{
		return UI8 < D.Value;
	}

	/* float */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt < int64" )
	static bool KeshUE4FTFloatLessThanInt64( float F, const FKeshInt64& I64 )
	{
		return F < I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 < flt" )
	static bool FKeshInt64LessThanFloat( const FKeshInt64& I64, float F )
	{
		return I64.Value < F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt < uint64" )
	static bool KeshUE4FTFloatLessThanUInt64( float F, const FKeshUInt64& UI64 )
	{
		return F < UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 < flt" )
	static bool KeshUE4FTUInt64LessThanFloat( const FKeshUInt64& UI64, float F )
	{
		return UI64.Value < F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt < uint32" )
	static bool KeshUE4FTFloatLessThanUInt32( float F, const FKeshUInt32& UI32 )
	{
		return F < UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 < flt" )
	static bool FKeshUInt32LessThanFloat( const FKeshUInt32& UI32, float F )
	{
		return UI32.Value < F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt < int16" )
	static bool KeshUE4FTFloatLessThanInt16( float F, const FKeshInt16& I16 )
	{
		return F < I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 < flt" )
	static bool FKeshInt16LessThanFloat( const FKeshInt16& I16, float F )
	{
		return I16.Value < F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt < uint16" )
	static bool KeshUE4FTFloatLessThanUInt16( float F, const FKeshUInt16& UI16 )
	{
		return F < UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 < flt" )
	static bool FKeshUInt16LessThanFloat( const FKeshUInt16& UI16, float F )
	{
		return UI16.Value < F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt < int8" )
	static bool KeshUE4FTFloatLessThanInt8( float F, const FKeshInt8& I8 )
	{
		return F < I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 < flt" )
	static bool FKeshInt8LessThanFloat( const FKeshInt8& I8, float F )
	{
		return I8.Value < F;
	}

	/* Int 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 < int64" )
	static bool FKeshInt64LessThanInt64( const FKeshInt64& I641, const FKeshInt64& I642 )
	{
		return I641.Value < I642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 < uint64" )
	static bool FKeshInt64LessThanUInt64( const FKeshInt64& I64, const FKeshUInt64& UI64 )
	{
		if ( ( UI64 >> 63 ) > 0 )
			return true;

		return I64.Value < static_cast< int64 >( UI64.Value );
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 < int64" )
	static bool KeshUE4FTUInt64LessThanInt64( const FKeshUInt64& UI64, const FKeshInt64& I64 )
	{
		if ( ( UI64 >> 63 ) > 0 )
			return false;

		return static_cast< int64 >( UI64.Value ) < I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 < int32" )
	static bool FKeshInt64LessThanInt32( const FKeshInt64& I64, int32 I32 )
	{
		return I64.Value < I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 < int64" )
	static bool KeshUE4FTInt32LessThanInt64( int32 I32, const FKeshInt64& I64 )
	{
		return I32 < I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 < uint32" )
	static bool FKeshInt64LessThanUInt32( const FKeshInt64& I64, const FKeshUInt32& UI32 )
	{
		return I64.Value < UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 < int64" )
	static bool FKeshUInt32LessThanInt64( const FKeshUInt32& UI32, const FKeshInt64& I64 )
	{
		return UI32.Value < I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 < int16" )
	static bool FKeshInt64LessThanInt16( const FKeshInt64& I64, const FKeshInt16& I16 )
	{
		return I64.Value < I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 < int64" )
	static bool FKeshInt16LessThanInt64( const FKeshInt16& I16, const FKeshInt64& I64 )
	{
		return I16.Value < I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 < uint16" )
	static bool FKeshInt64LessThanUInt16( const FKeshInt64& I64, const FKeshUInt16& UI16 )
	{
		return I64.Value < UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 < int64" )
	static bool FKeshUInt16LessThanInt64( const FKeshUInt16& UI16, const FKeshInt64& I64 )
	{
		return UI16.Value < I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 < int8" )
	static bool FKeshInt64LessThanInt8( const FKeshInt64& I64, const FKeshInt8& I8 )
	{
		return I64.Value < I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 < int64" )
	static bool FKeshInt8LessThanInt64( const FKeshInt8& I8, const FKeshInt64& I64 )
	{
		return I8.Value < I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 < uint8" )
	static bool FKeshInt64LessThanUInt8( const FKeshInt64& I64, uint8 UI8 )
	{
		return I64.Value < UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 < int64" )
	static bool KeshUE4FTUInt8LessThanInt64( uint8 UI8, const FKeshInt64& I64 )
	{
		return UI8 < I64.Value;
	}

	/* UInt 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 < uint64" )
	static bool KeshUE4FTUInt64LessThanUInt64( const FKeshUInt64& UI641, const FKeshUInt64& UI642 )
	{
		return UI641.Value < UI642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 < int32" )
	static bool KeshUE4FTUInt64LessThanInt32( const FKeshUInt64& UI64, int32 I32 )
	{
		return UI64.Value < I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 < uint64" )
	static bool KeshUE4FTUInt32LessThanInt64( int32 I32, const FKeshUInt64& UI64 )
	{
		return I32 < UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 < uint32" )
	static bool KeshUE4FTUInt64LessThanUInt32( const FKeshUInt64& UI64, const FKeshUInt32& UI32 )
	{
		return UI64.Value < UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 < uint64" )
	static bool KeshUE4FTUUInt32LessThanInt64( const FKeshUInt32& UI32, const FKeshUInt64& UI64 )
	{
		return UI32.Value < UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 < int16" )
	static bool KeshUE4FTUInt64LessThanInt16( const FKeshUInt64& UI64, const FKeshInt16& I16 )
	{
		return UI64.Value < I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 < uint64" )
	static bool FKeshInt16LessThanUInt64( const FKeshInt16& I16, const FKeshUInt64& UI64 )
	{
		return I16.Value < UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 < uint16" )
	static bool KeshUE4FTUInt64LessThanUInt16( const FKeshUInt64& UI64, const FKeshUInt16& UI16 )
	{
		return UI64.Value < UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 < uint64" )
	static bool FKeshUInt16LessThanUInt64( const FKeshUInt16& UI16, const FKeshUInt64& UI64 )
	{
		return UI16.Value < UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 < int8" )
	static bool KeshUE4FTUInt64LessThanInt8( const FKeshUInt64& UI64, const FKeshInt8& I8 )
	{
		return UI64.Value < I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 < uint64" )
	static bool FKeshInt8LessThanUInt64( const FKeshInt8& I8, const FKeshUInt64& UI64 )
	{
		return I8.Value < UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 < uint8" )
	static bool KeshUE4FTUInt64LessThanUInt8( const FKeshUInt64& UI64, uint8 UI8 )
	{
		return UI64.Value < UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 < uint64" )
	static bool KeshUE4FTUInt8LessThanUInt64( uint8 UI8, const FKeshUInt64& UI64 )
	{
		return UI8 < UI64.Value;
	}

	/* Int 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 < uint32" )
	static bool KeshUE4FTInt32LessThanUInt32( int32 I32, const FKeshUInt32& UI32 )
	{
		return I32 < UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 < int32" )
	static bool FKeshUInt32LessThanInt32( const FKeshUInt32& UI32, int32 I32 )
	{
		return UI32.Value < I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 < int16" )
	static bool KeshUE4FTInt32LessThanInt16( int32 I32, const FKeshInt16& I16 )
	{
		return I32 < I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 < int32" )
	static bool FKeshInt16LessThanInt32( const FKeshInt16& I16, int32 I32 )
	{
		return I16.Value < I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 < uint16" )
	static bool KeshUE4FTInt32LessThanUInt16( int32 I32, const FKeshUInt16& UI16 )
	{
		return I32 < UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 < int32" )
	static bool FKeshUInt16LessThanInt32( const FKeshUInt16& UI16, int32 I32 )
	{
		return UI16.Value < I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 < int8" )
	static bool KeshUE4FTInt32LessThanInt8( int32 I32, const FKeshInt8& I8 )
	{
		return I32 < I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 < int32" )
	static bool FKeshInt8LessThanInt32( const FKeshInt8& I8, int32 I32 )
	{
		return I8.Value < I32;
	}

	/* UInt 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 < uint32" )
	static bool FKeshUInt32LessThanUInt32( const FKeshUInt32& UI321, const FKeshUInt32& UI322 )
	{
		return UI321.Value < UI322.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 < int16" )
	static bool FKeshUInt32LessThanInt16( const FKeshUInt32& UI32, const FKeshInt16& I16 )
	{
		return UI32.Value < I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 < uint32" )
	static bool FKeshInt16LessThanUInt32( const FKeshInt16& I16, const FKeshUInt32& UI32 )
	{
		return I16.Value < UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 < uint16" )
	static bool FKeshUInt32LessThanUInt16( const FKeshUInt32& UI32, const FKeshUInt16& UI16 )
	{
		return UI32.Value < UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 < uint32" )
	static bool FKeshUInt16LessThanUInt32( const FKeshUInt16& UI16, const FKeshUInt32& UI32 )
	{
		return UI16.Value < UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 < int8" )
	static bool FKeshUInt32LessThanInt8( const FKeshUInt32& UI32, const FKeshInt8& I8 )
	{
		return UI32.Value < I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 < uint32" )
	static bool FKeshInt8LessThanUInt32( const FKeshInt8& I8, const FKeshUInt32& UI32 )
	{
		return I8.Value < UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 < uint8" )
	static bool FKeshUInt32LessThanUInt8( const FKeshUInt32& UI32, uint8 UI8 )
	{
		return UI32.Value < UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 < uint32" )
	static bool KeshUE4FTUInt8LessThanUInt32( uint8 UI8, const FKeshUInt32& UI32 )
	{
		return UI8 < UI32.Value;
	}

	/* Int 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 < int16" )
	static bool FKeshInt16LessThanInt16( const FKeshInt16& I161, const FKeshInt16& I162 )
	{
		return I161.Value < I162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 < uint16" )
	static bool FKeshInt16LessThanUInt16( const FKeshInt16& I16, const FKeshUInt16& UI16 )
	{
		return I16.Value < UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 < int16" )
	static bool FKeshUInt16LessThanInt16( const FKeshUInt16& UI16, const FKeshInt16& I16 )
	{
		return UI16.Value < I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 < int8" )
	static bool FKeshInt16LessThanInt8( const FKeshInt16& I16, const FKeshInt8& I8 )
	{
		return I16.Value < I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 < int16" )
	static bool FKeshInt8LessThanInt16( const FKeshInt8& I8, const FKeshInt16& I16 )
	{
		return I8.Value < I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 < uint8" )
	static bool FKeshInt16LessThanUInt8( const FKeshInt16& I16, uint8 UI8 )
	{
		return I16.Value < UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 < int16" )
	static bool KeshUE4FTUInt8LessThanInt16( uint8 UI8, const FKeshInt16& I16 )
	{
		return UI8 < I16.Value;
	}

	/* UInt 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 < uint16" )
	static bool FKeshUInt16LessThanUUInt16( const FKeshUInt16& UI161, const FKeshUInt16& UI162 )
	{
		return UI161.Value < UI162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 < int8" )
	static bool FKeshUInt16LessThanInt8( const FKeshUInt16& UI16, const FKeshInt8& I8 )
	{
		return UI16.Value < I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 < uint16" )
	static bool FKeshInt8LessThanUInt16( const FKeshInt8& I8, const FKeshUInt16& UI16 )
	{
		return I8.Value < UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 < uint8" )
	static bool FKeshUInt16LessThanUInt8( const FKeshUInt16& UI16, uint8 UI8 )
	{
		return UI16.Value < UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 < uint16" )
	static bool KeshUE4FTUInt8LessThanUInt16( uint8 UI8, const FKeshUInt16& UI16 )
	{
		return UI8 < UI16.Value;
	}

	/* Int 8 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 < int8" )
	static bool FKeshInt8LessThanInt8( const FKeshInt8& I81, const FKeshInt8& I82 )
	{
		return I81.Value < I82.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 < uint8" )
	static bool FKeshInt8LessThanUInt8( const FKeshInt8& I8, uint8 UI8 )
	{
		return I8.Value < UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 < int8" )
	static bool KeshUE4FTUInt8LessThanInt8( uint8 UI8, const FKeshInt8& I8 )
	{
		return UI8 < I8.Value;
	}


	/************************/
	/* GreaterThanOrEqualTo */
	/************************/

	/* Double */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl >= dbl" )
	static bool KeshUE4FTDoubleGreaterThanOrEqualToDouble( const FKeshDouble& D1, const FKeshDouble& D2 )
	{
		return D1.Value >= D2.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl >= flt" )
	static bool KeshUE4FTDoubleGreaterThanOrEqualToFloat( const FKeshDouble& D, float F )
	{
		return D.Value >= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt >= dbl" )
	static bool KeshUE4FTFloatGreaterThanOrEqualToDouble( float F, const FKeshDouble& D )
	{
		return F >= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl >= int64" )
	static bool KeshUE4FTDoubleGreaterThanOrEqualToInt64( const FKeshDouble& D, const FKeshInt64& I64 )
	{
		return D.Value >= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 >= dbl" )
	static bool FKeshInt64GreaterThanOrEqualToDouble( const FKeshInt64& I64, const FKeshDouble& D )
	{
		return I64.Value >= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl >= uint64" )
	static bool KeshUE4FTDoubleGreaterThanOrEqualToUInt64( const FKeshDouble& D, const FKeshUInt64& UI64 )
	{
		return D.Value >= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 >= dbl" )
	static bool KeshUE4FTUInt64GreaterThanOrEqualToDouble( const FKeshUInt64& UI64, const FKeshDouble& D )
	{
		return UI64.Value >= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl >= int32" )
	static bool KeshUE4FTDoubleGreaterThanOrEqualToInt32( const FKeshDouble& D, int32 I32 )
	{
		return D.Value >= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 >= dbl" )
	static bool KeshUE4FTInt32GreaterThanOrEqualToDouble( int32 I32, const FKeshDouble& D )
	{
		return I32 >= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl >= uint32" )
	static bool KeshUE4FTDoubleGreaterThanOrEqualToUInt32( const FKeshDouble& D, const FKeshUInt32& UI32 )
	{
		return D.Value >= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 >= dbl" )
	static bool FKeshUInt32GreaterThanOrEqualToDouble( const FKeshUInt32& UI32, const FKeshDouble& D )
	{
		return UI32.Value >= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl >= int16" )
	static bool KeshUE4FTDoubleGreaterThanOrEqualToInt16( const FKeshDouble& D, const FKeshInt16& I16 )
	{
		return D.Value >= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 >= dbl" )
	static bool FKeshInt16GreaterThanOrEqualToDouble( const FKeshInt16& I16, const FKeshDouble& D )
	{
		return I16.Value >= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl >= uint16" )
	static bool KeshUE4FTDoubleGreaterThanOrEqualToUInt16( const FKeshDouble& D, const FKeshUInt16& UI16 )
	{
		return D.Value >= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 >= dbl" )
	static bool FKeshUInt16GreaterThanOrEqualToDouble( const FKeshUInt16& UI16, const FKeshDouble& D )
	{
		return UI16.Value >= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl >= int8" )
	static bool KeshUE4FTDoubleGreaterThanOrEqualToInt8( const FKeshDouble& D, const FKeshInt8& I8 )
	{
		return D.Value >= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 >= dbl" )
	static bool FKeshInt8GreaterThanOrEqualToDouble( const FKeshInt8& I8, const FKeshDouble& D )
	{
		return I8.Value >= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl >= uint8" )
	static bool KeshUE4FTDoubleGreaterThanOrEqualToUInt8( const FKeshDouble& D, uint8 UI8 )
	{
		return D.Value >= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 >= dbl" )
	static bool KeshUE4FTUInt8GreaterThanOrEqualToDouble( uint8 UI8, const FKeshDouble& D )
	{
		return UI8 >= D.Value;
	}

	/* float */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt >= int64" )
	static bool KeshUE4FTFloatGreaterThanOrEqualToInt64( float F, const FKeshInt64& I64 )
	{
		return F >= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 >= flt" )
	static bool FKeshInt64GreaterThanOrEqualToFloat( const FKeshInt64& I64, float F )
	{
		return I64.Value >= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt >= uint64" )
	static bool KeshUE4FTFloatGreaterThanOrEqualToUInt64( float F, const FKeshUInt64& UI64 )
	{
		return F >= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 >= flt" )
	static bool KeshUE4FTUInt64GreaterThanOrEqualToFloat( const FKeshUInt64& UI64, float F )
	{
		return UI64.Value >= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt >= uint32" )
	static bool KeshUE4FTFloatGreaterThanOrEqualToUInt32( float F, const FKeshUInt32& UI32 )
	{
		return F >= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 >= flt" )
	static bool FKeshUInt32GreaterThanOrEqualToFloat( const FKeshUInt32& UI32, float F )
	{
		return UI32.Value >= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt >= int16" )
	static bool KeshUE4FTFloatGreaterThanOrEqualToInt16( float F, const FKeshInt16& I16 )
	{
		return F >= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 >= flt" )
	static bool FKeshInt16GreaterThanOrEqualToFloat( const FKeshInt16& I16, float F )
	{
		return I16.Value >= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt >= uint16" )
	static bool KeshUE4FTFloatGreaterThanOrEqualToUInt16( float F, const FKeshUInt16& UI16 )
	{
		return F >= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 >= flt" )
	static bool FKeshUInt16GreaterThanOrEqualToFloat( const FKeshUInt16& UI16, float F )
	{
		return UI16.Value >= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt >= int8" )
	static bool KeshUE4FTFloatGreaterThanOrEqualToInt8( float F, const FKeshInt8& I8 )
	{
		return F >= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 >= flt" )
	static bool FKeshInt8GreaterThanOrEqualToFloat( const FKeshInt8& I8, float F )
	{
		return I8.Value >= F;
	}

	/* Int 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 >= int64" )
	static bool FKeshInt64GreaterThanOrEqualToInt64( const FKeshInt64& I641, const FKeshInt64& I642 )
	{
		return I641.Value >= I642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 >= uint64" )
	static bool FKeshInt64GreaterThanOrEqualToUInt64( const FKeshInt64& I64, const FKeshUInt64& UI64 )
	{
		if ( I64 < 0 )
			return false;

		return static_cast< uint64 >( I64.Value ) >= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 >= int64" )
	static bool KeshUE4FTUInt64GreaterThanOrEqualToInt64( const FKeshUInt64& UI64, const FKeshInt64& I64 )
	{
		if ( I64 < 0 )
			return true;

		return UI64.Value >= static_cast< uint64 >( I64.Value );
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 >= int32" )
	static bool FKeshInt64GreaterThanOrEqualToInt32( const FKeshInt64& I64, int32 I32 )
	{
		return I64.Value >= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 >= int64" )
	static bool KeshUE4FTInt32GreaterThanOrEqualToInt64( int32 I32, const FKeshInt64& I64 )
	{
		return I32 >= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 >= uint32" )
	static bool FKeshInt64GreaterThanOrEqualToUInt32( const FKeshInt64& I64, const FKeshUInt32& UI32 )
	{
		return I64.Value >= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 >= int64" )
	static bool FKeshUInt32GreaterThanOrEqualToInt64( const FKeshUInt32& UI32, const FKeshInt64& I64 )
	{
		return UI32.Value >= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 >= int16" )
	static bool FKeshInt64GreaterThanOrEqualToInt16( const FKeshInt64& I64, const FKeshInt16& I16 )
	{
		return I64.Value >= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 >= int64" )
	static bool FKeshInt16GreaterThanOrEqualToInt64( const FKeshInt16& I16, const FKeshInt64& I64 )
	{
		return I16.Value >= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 >= uint16" )
	static bool FKeshInt64GreaterThanOrEqualToUInt16( const FKeshInt64& I64, const FKeshUInt16& UI16 )
	{
		return I64.Value >= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 >= int64" )
	static bool FKeshUInt16GreaterThanOrEqualToInt64( const FKeshUInt16& UI16, const FKeshInt64& I64 )
	{
		return UI16.Value >= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 >= int8" )
	static bool FKeshInt64GreaterThanOrEqualToInt8( const FKeshInt64& I64, const FKeshInt8& I8 )
	{
		return I64.Value >= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 >= int64" )
	static bool FKeshInt8GreaterThanOrEqualToInt64( const FKeshInt8& I8, const FKeshInt64& I64 )
	{
		return I8.Value >= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 >= uint8" )
	static bool FKeshInt64GreaterThanOrEqualToUInt8( const FKeshInt64& I64, uint8 UI8 )
	{
		return I64.Value >= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 >= int64" )
	static bool KeshUE4FTUInt8GreaterThanOrEqualToInt64( uint8 UI8, const FKeshInt64& I64 )
	{
		return UI8 >= I64.Value;
	}

	/* UInt 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 >= uint64" )
	static bool KeshUE4FTUInt64GreaterThanOrEqualToUInt64( const FKeshUInt64& UI641, const FKeshUInt64& UI642 )
	{
		return UI641.Value >= UI642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 >= int32" )
	static bool KeshUE4FTUInt64GreaterThanOrEqualToInt32( const FKeshUInt64& UI64, int32 I32 )
	{
		return UI64.Value >= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 >= uint64" )
	static bool KeshUE4FTUInt32GreaterThanOrEqualToInt64( int32 I32, const FKeshUInt64& UI64 )
	{
		return I32 >= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 >= uint32" )
	static bool KeshUE4FTUInt64GreaterThanOrEqualToUInt32( const FKeshUInt64& UI64, const FKeshUInt32& UI32 )
	{
		return UI64.Value >= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 >= uint64" )
	static bool KeshUE4FTUUInt32GreaterThanOrEqualToInt64( const FKeshUInt32& UI32, const FKeshUInt64& UI64 )
	{
		return UI32.Value >= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 >= int16" )
	static bool KeshUE4FTUInt64GreaterThanOrEqualToInt16( const FKeshUInt64& UI64, const FKeshInt16& I16 )
	{
		return UI64.Value >= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 >= uint64" )
	static bool FKeshInt16GreaterThanOrEqualToUInt64( const FKeshInt16& I16, const FKeshUInt64& UI64 )
	{
		return I16.Value >= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 >= uint16" )
	static bool KeshUE4FTUInt64GreaterThanOrEqualToUInt16( const FKeshUInt64& UI64, const FKeshUInt16& UI16 )
	{
		return UI64.Value >= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 >= uint64" )
	static bool FKeshUInt16GreaterThanOrEqualToUInt64( const FKeshUInt16& UI16, const FKeshUInt64& UI64 )
	{
		return UI16.Value >= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 >= int8" )
	static bool KeshUE4FTUInt64GreaterThanOrEqualToInt8( const FKeshUInt64& UI64, const FKeshInt8& I8 )
	{
		return UI64.Value >= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 >= uint64" )
	static bool FKeshInt8GreaterThanOrEqualToUInt64( const FKeshInt8& I8, const FKeshUInt64& UI64 )
	{
		return I8.Value >= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 >= uint8" )
	static bool KeshUE4FTUInt64GreaterThanOrEqualToUInt8( const FKeshUInt64& UI64, uint8 UI8 )
	{
		return UI64.Value >= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 >= uint64" )
	static bool KeshUE4FTUInt8GreaterThanOrEqualToUInt64( uint8 UI8, const FKeshUInt64& UI64 )
	{
		return UI8 >= UI64.Value;
	}

	/* Int 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 >= uint32" )
	static bool KeshUE4FTInt32GreaterThanOrEqualToUInt32( int32 I32, const FKeshUInt32& UI32 )
	{
		return I32 >= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 >= int32" )
	static bool FKeshUInt32GreaterThanOrEqualToInt32( const FKeshUInt32& UI32, int32 I32 )
	{
		return UI32.Value >= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 >= int16" )
	static bool KeshUE4FTInt32GreaterThanOrEqualToInt16( int32 I32, const FKeshInt16& I16 )
	{
		return I32 >= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 >= int32" )
	static bool FKeshInt16GreaterThanOrEqualToInt32( const FKeshInt16& I16, int32 I32 )
	{
		return I16.Value >= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 >= uint16" )
	static bool KeshUE4FTInt32GreaterThanOrEqualToUInt16( int32 I32, const FKeshUInt16& UI16 )
	{
		return I32 >= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 >= int32" )
	static bool FKeshUInt16GreaterThanOrEqualToInt32( const FKeshUInt16& UI16, int32 I32 )
	{
		return UI16.Value >= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 >= int8" )
	static bool KeshUE4FTInt32GreaterThanOrEqualToInt8( int32 I32, const FKeshInt8& I8 )
	{
		return I32 >= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 >= int32" )
	static bool FKeshInt8GreaterThanOrEqualToInt32( const FKeshInt8& I8, int32 I32 )
	{
		return I8.Value >= I32;
	}

	/* UInt 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 >= uint32" )
	static bool FKeshUInt32GreaterThanOrEqualToUInt32( const FKeshUInt32& UI321, const FKeshUInt32& UI322 )
	{
		return UI321.Value >= UI322.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 >= int16" )
	static bool FKeshUInt32GreaterThanOrEqualToInt16( const FKeshUInt32& UI32, const FKeshInt16& I16 )
	{
		return UI32.Value >= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 >= uint32" )
	static bool FKeshInt16GreaterThanOrEqualToUInt32( const FKeshInt16& I16, const FKeshUInt32& UI32 )
	{
		return I16.Value >= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 >= uint16" )
	static bool FKeshUInt32GreaterThanOrEqualToUInt16( const FKeshUInt32& UI32, const FKeshUInt16& UI16 )
	{
		return UI32.Value >= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 >= uint32" )
	static bool FKeshUInt16GreaterThanOrEqualToUInt32( const FKeshUInt16& UI16, const FKeshUInt32& UI32 )
	{
		return UI16.Value >= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 >= int8" )
	static bool FKeshUInt32GreaterThanOrEqualToInt8( const FKeshUInt32& UI32, const FKeshInt8& I8 )
	{
		return UI32.Value >= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 >= uint32" )
	static bool FKeshInt8GreaterThanOrEqualToUInt32( const FKeshInt8& I8, const FKeshUInt32& UI32 )
	{
		return I8.Value >= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 >= uint8" )
	static bool FKeshUInt32GreaterThanOrEqualToUInt8( const FKeshUInt32& UI32, uint8 UI8 )
	{
		return UI32.Value >= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 >= uint32" )
	static bool KeshUE4FTUInt8GreaterThanOrEqualToUInt32( uint8 UI8, const FKeshUInt32& UI32 )
	{
		return UI8 >= UI32.Value;
	}

	/* Int 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 >= int16" )
	static bool FKeshInt16GreaterThanOrEqualToInt16( const FKeshInt16& I161, const FKeshInt16& I162 )
	{
		return I161.Value >= I162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 >= uint16" )
	static bool FKeshInt16GreaterThanOrEqualToUInt16( const FKeshInt16& I16, const FKeshUInt16& UI16 )
	{
		return I16.Value >= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 >= int16" )
	static bool FKeshUInt16GreaterThanOrEqualToInt16( const FKeshUInt16& UI16, const FKeshInt16& I16 )
	{
		return UI16.Value >= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 >= int8" )
	static bool FKeshInt16GreaterThanOrEqualToInt8( const FKeshInt16& I16, const FKeshInt8& I8 )
	{
		return I16.Value >= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 >= int16" )
	static bool FKeshInt8GreaterThanOrEqualToInt16( const FKeshInt8& I8, const FKeshInt16& I16 )
	{
		return I8.Value >= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 >= uint8" )
	static bool FKeshInt16GreaterThanOrEqualToUInt8( const FKeshInt16& I16, uint8 UI8 )
	{
		return I16.Value >= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 >= int16" )
	static bool KeshUE4FTUInt8GreaterThanOrEqualToInt16( uint8 UI8, const FKeshInt16& I16 )
	{
		return UI8 >= I16.Value;
	}

	/* UInt 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 >= uint16" )
	static bool FKeshUInt16GreaterThanOrEqualToUUInt16( const FKeshUInt16& UI161, const FKeshUInt16& UI162 )
	{
		return UI161.Value >= UI162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 >= int8" )
	static bool FKeshUInt16GreaterThanOrEqualToInt8( const FKeshUInt16& UI16, const FKeshInt8& I8 )
	{
		return UI16.Value >= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 >= uint16" )
	static bool FKeshInt8GreaterThanOrEqualToUInt16( const FKeshInt8& I8, const FKeshUInt16& UI16 )
	{
		return I8.Value >= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 >= uint8" )
	static bool FKeshUInt16GreaterThanOrEqualToUInt8( const FKeshUInt16& UI16, uint8 UI8 )
	{
		return UI16.Value >= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 >= uint16" )
	static bool KeshUE4FTUInt8GreaterThanOrEqualToUInt16( uint8 UI8, const FKeshUInt16& UI16 )
	{
		return UI8 >= UI16.Value;
	}

	/* Int 8 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 >= int8" )
	static bool FKeshInt8GreaterThanOrEqualToInt8( const FKeshInt8& I81, const FKeshInt8& I82 )
	{
		return I81.Value >= I82.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 >= uint8" )
	static bool FKeshInt8GreaterThanOrEqualToUInt8( const FKeshInt8& I8, uint8 UI8 )
	{
		return I8.Value >= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 >= int8" )
	static bool KeshUE4FTUInt8GreaterThanOrEqualToInt8( uint8 UI8, const FKeshInt8& I8 )
	{
		return UI8 >= I8.Value;
	}


	/*********************/
	/* LessThanOrEqualTo */
	/*********************/

	/* Double */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl <= dbl" )
	static bool KeshUE4FTDoubleLessThanOrEqualToDouble( const FKeshDouble& D1, const FKeshDouble& D2 )
	{
		return D1.Value <= D2.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl <= flt" )
	static bool KeshUE4FTDoubleLessThanOrEqualToFloat( const FKeshDouble& D, float F )
	{
		return D.Value <= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt <= dbl" )
	static bool KeshUE4FTFloatLessThanOrEqualToDouble( float F, const FKeshDouble& D )
	{
		return F <= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl <= int64" )
	static bool KeshUE4FTDoubleLessThanOrEqualToInt64( const FKeshDouble& D, const FKeshInt64& I64 )
	{
		return D.Value <= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 <= dbl" )
	static bool FKeshInt64LessThanOrEqualToDouble( const FKeshInt64& I64, const FKeshDouble& D )
	{
		return I64.Value <= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl <= uint64" )
	static bool KeshUE4FTDoubleLessThanOrEqualToUInt64( const FKeshDouble& D, const FKeshUInt64& UI64 )
	{
		return D.Value <= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 <= dbl" )
	static bool KeshUE4FTUInt64LessThanOrEqualToDouble( const FKeshUInt64& UI64, const FKeshDouble& D )
	{
		return UI64.Value <= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl <= int32" )
	static bool KeshUE4FTDoubleLessThanOrEqualToInt32( const FKeshDouble& D, int32 I32 )
	{
		return D.Value <= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 <= dbl" )
	static bool KeshUE4FTInt32LessThanOrEqualToDouble( int32 I32, const FKeshDouble& D )
	{
		return I32 <= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl <= uint32" )
	static bool KeshUE4FTDoubleLessThanOrEqualToUInt32( const FKeshDouble& D, const FKeshUInt32& UI32 )
	{
		return D.Value <= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 <= dbl" )
	static bool FKeshUInt32LessThanOrEqualToDouble( const FKeshUInt32& UI32, const FKeshDouble& D )
	{
		return UI32.Value <= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl <= int16" )
	static bool KeshUE4FTDoubleLessThanOrEqualToInt16( const FKeshDouble& D, const FKeshInt16& I16 )
	{
		return D.Value <= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 <= dbl" )
	static bool FKeshInt16LessThanOrEqualToDouble( const FKeshInt16& I16, const FKeshDouble& D )
	{
		return I16.Value <= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl <= uint16" )
	static bool KeshUE4FTDoubleLessThanOrEqualToUInt16( const FKeshDouble& D, const FKeshUInt16& UI16 )
	{
		return D.Value <= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 <= dbl" )
	static bool FKeshUInt16LessThanOrEqualToDouble( const FKeshUInt16& UI16, const FKeshDouble& D )
	{
		return UI16.Value <= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl <= int8" )
	static bool KeshUE4FTDoubleLessThanOrEqualToInt8( const FKeshDouble& D, const FKeshInt8& I8 )
	{
		return D.Value <= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 <= dbl" )
	static bool FKeshInt8LessThanOrEqualToDouble( const FKeshInt8& I8, const FKeshDouble& D )
	{
		return I8.Value <= D.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "dbl <= uint8" )
	static bool KeshUE4FTDoubleLessThanOrEqualToUInt8( const FKeshDouble& D, uint8 UI8 )
	{
		return D.Value <= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 <= dbl" )
	static bool KeshUE4FTUInt8LessThanOrEqualToDouble( uint8 UI8, const FKeshDouble& D )
	{
		return UI8 <= D.Value;
	}

	/* float */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt <= int64" )
	static bool KeshUE4FTFloatLessThanOrEqualToInt64( float F, const FKeshInt64& I64 )
	{
		return F <= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 <= flt" )
	static bool FKeshInt64LessThanOrEqualToFloat( const FKeshInt64& I64, float F )
	{
		return I64.Value <= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt <= uint64" )
	static bool KeshUE4FTFloatLessThanOrEqualToUInt64( float F, const FKeshUInt64& UI64 )
	{
		return F <= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 <= flt" )
	static bool KeshUE4FTUInt64LessThanOrEqualToFloat( const FKeshUInt64& UI64, float F )
	{
		return UI64.Value <= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt <= uint32" )
	static bool KeshUE4FTFloatLessThanOrEqualToUInt32( float F, const FKeshUInt32& UI32 )
	{
		return F <= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 <= flt" )
	static bool FKeshUInt32LessThanOrEqualToFloat( const FKeshUInt32& UI32, float F )
	{
		return UI32.Value <= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt <= int16" )
	static bool KeshUE4FTFloatLessThanOrEqualToInt16( float F, const FKeshInt16& I16 )
	{
		return F <= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 <= flt" )
	static bool FKeshInt16LessThanOrEqualToFloat( const FKeshInt16& I16, float F )
	{
		return I16.Value <= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt <= uint16" )
	static bool KeshUE4FTFloatLessThanOrEqualToUInt16( float F, const FKeshUInt16& UI16 )
	{
		return F <= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 <= flt" )
	static bool FKeshUInt16LessThanOrEqualToFloat( const FKeshUInt16& UI16, float F )
	{
		return UI16.Value <= F;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "flt <= int8" )
	static bool KeshUE4FTFloatLessThanOrEqualToInt8( float F, const FKeshInt8& I8 )
	{
		return F <= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 <= flt" )
	static bool FKeshInt8LessThanOrEqualToFloat( const FKeshInt8& I8, float F )
	{
		return I8.Value <= F;
	}

	/* Int 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 <= int64" )
	static bool FKeshInt64LessThanOrEqualToInt64( const FKeshInt64& I641, const FKeshInt64& I642 )
	{
		return I641.Value <= I642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 <= uint64" )
	static bool FKeshInt64LessThanOrEqualToUInt64( const FKeshInt64& I64, const FKeshUInt64& UI64 )
	{
		if ( I64 < 0 )
			return true;

		return static_cast< uint64 >( I64.Value ) <= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 <= int64" )
	static bool KeshUE4FTUInt64LessThanOrEqualToInt64( const FKeshUInt64& UI64, const FKeshInt64& I64 )
	{
		if ( I64 < 0 )
			return false;

		return UI64.Value <= static_cast< uint64 >( I64.Value );
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 <= int32" )
	static bool FKeshInt64LessThanOrEqualToInt32( const FKeshInt64& I64, int32 I32 )
	{
		return I64.Value <= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 <= int64" )
	static bool KeshUE4FTInt32LessThanOrEqualToInt64( int32 I32, const FKeshInt64& I64 )
	{
		return I32 <= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 <= uint32" )
	static bool FKeshInt64LessThanOrEqualToUInt32( const FKeshInt64& I64, const FKeshUInt32& UI32 )
	{
		return I64.Value <= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 <= int64" )
	static bool FKeshUInt32LessThanOrEqualToInt64( const FKeshUInt32& UI32, const FKeshInt64& I64 )
	{
		return UI32.Value <= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 <= int16" )
	static bool FKeshInt64LessThanOrEqualToInt16( const FKeshInt64& I64, const FKeshInt16& I16 )
	{
		return I64.Value <= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 <= int64" )
	static bool FKeshInt16LessThanOrEqualToInt64( const FKeshInt16& I16, const FKeshInt64& I64 )
	{
		return I16.Value <= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 <= uint16" )
	static bool FKeshInt64LessThanOrEqualToUInt16( const FKeshInt64& I64, const FKeshUInt16& UI16 )
	{
		return I64.Value <= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 <= int64" )
	static bool FKeshUInt16LessThanOrEqualToInt64( const FKeshUInt16& UI16, const FKeshInt64& I64 )
	{
		return UI16.Value <= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 <= int8" )
	static bool FKeshInt64LessThanOrEqualToInt8( const FKeshInt64& I64, const FKeshInt8& I8 )
	{
		return I64.Value <= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 <= int64" )
	static bool FKeshInt8LessThanOrEqualToInt64( const FKeshInt8& I8, const FKeshInt64& I64 )
	{
		return I8.Value <= I64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int64 <= uint8" )
	static bool FKeshInt64LessThanOrEqualToUInt8( const FKeshInt64& I64, uint8 UI8 )
	{
		return I64.Value <= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 <= int64" )
	static bool KeshUE4FTUInt8LessThanOrEqualToInt64( uint8 UI8, const FKeshInt64& I64 )
	{
		return UI8 <= I64.Value;
	}

	/* UInt 64 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 <= uint64" )
	static bool KeshUE4FTUInt64LessThanOrEqualToUInt64( const FKeshUInt64& UI641, const FKeshUInt64& UI642 )
	{
		return UI641.Value <= UI642.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 <= int32" )
	static bool KeshUE4FTUInt64LessThanOrEqualToInt32( const FKeshUInt64& UI64, int32 I32 )
	{
		return UI64.Value <= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 <= uint64" )
	static bool KeshUE4FTUInt32LessThanOrEqualToInt64( int32 I32, const FKeshUInt64& UI64 )
	{
		return I32 <= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 <= uint32" )
	static bool KeshUE4FTUInt64LessThanOrEqualToUInt32( const FKeshUInt64& UI64, const FKeshUInt32& UI32 )
	{
		return UI64.Value <= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 <= uint64" )
	static bool KeshUE4FTUUInt32LessThanOrEqualToInt64( const FKeshUInt32& UI32, const FKeshUInt64& UI64 )
	{
		return UI32.Value <= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 <= int16" )
	static bool KeshUE4FTUInt64LessThanOrEqualToInt16( const FKeshUInt64& UI64, const FKeshInt16& I16 )
	{
		return UI64.Value <= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 <= uint64" )
	static bool FKeshInt16LessThanOrEqualToUInt64( const FKeshInt16& I16, const FKeshUInt64& UI64 )
	{
		return I16.Value <= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 <= uint16" )
	static bool KeshUE4FTUInt64LessThanOrEqualToUInt16( const FKeshUInt64& UI64, const FKeshUInt16& UI16 )
	{
		return UI64.Value <= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 <= uint64" )
	static bool FKeshUInt16LessThanOrEqualToUInt64( const FKeshUInt16& UI16, const FKeshUInt64& UI64 )
	{
		return UI16.Value <= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 <= int8" )
	static bool KeshUE4FTUInt64LessThanOrEqualToInt8( const FKeshUInt64& UI64, const FKeshInt8& I8 )
	{
		return UI64.Value <= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 <= uint64" )
	static bool FKeshInt8LessThanOrEqualToUInt64( const FKeshInt8& I8, const FKeshUInt64& UI64 )
	{
		return I8.Value <= UI64.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint64 <= uint8" )
	static bool KeshUE4FTUInt64LessThanOrEqualToUInt8( const FKeshUInt64& UI64, uint8 UI8 )
	{
		return UI64.Value <= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 <= uint64" )
	static bool KeshUE4FTUInt8LessThanOrEqualToUInt64( uint8 UI8, const FKeshUInt64& UI64 )
	{
		return UI8 <= UI64.Value;
	}

	/* Int 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 <= uint32" )
	static bool KeshUE4FTInt32LessThanOrEqualToUInt32( int32 I32, const FKeshUInt32& UI32 )
	{
		return I32 <= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 <= int32" )
	static bool FKeshUInt32LessThanOrEqualToInt32( const FKeshUInt32& UI32, int32 I32 )
	{
		return UI32.Value <= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 <= int16" )
	static bool KeshUE4FTInt32LessThanOrEqualToInt16( int32 I32, const FKeshInt16& I16 )
	{
		return I32 <= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 <= int32" )
	static bool FKeshInt16LessThanOrEqualToInt32( const FKeshInt16& I16, int32 I32 )
	{
		return I16.Value <= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 <= uint16" )
	static bool KeshUE4FTInt32LessThanOrEqualToUInt16( int32 I32, const FKeshUInt16& UI16 )
	{
		return I32 <= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 <= int32" )
	static bool FKeshUInt16LessThanOrEqualToInt32( const FKeshUInt16& UI16, int32 I32 )
	{
		return UI16.Value <= I32;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int32 <= int8" )
	static bool KeshUE4FTInt32LessThanOrEqualToInt8( int32 I32, const FKeshInt8& I8 )
	{
		return I32 <= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 <= int32" )
	static bool FKeshInt8LessThanOrEqualToInt32( const FKeshInt8& I8, int32 I32 )
	{
		return I8.Value <= I32;
	}

	/* UInt 32 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 <= uint32" )
	static bool FKeshUInt32LessThanOrEqualToUInt32( const FKeshUInt32& UI321, const FKeshUInt32& UI322 )
	{
		return UI321.Value <= UI322.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 <= int16" )
	static bool FKeshUInt32LessThanOrEqualToInt16( const FKeshUInt32& UI32, const FKeshInt16& I16 )
	{
		return UI32.Value <= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 <= uint32" )
	static bool FKeshInt16LessThanOrEqualToUInt32( const FKeshInt16& I16, const FKeshUInt32& UI32 )
	{
		return I16.Value <= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 <= uint16" )
	static bool FKeshUInt32LessThanOrEqualToUInt16( const FKeshUInt32& UI32, const FKeshUInt16& UI16 )
	{
		return UI32.Value <= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 <= uint32" )
	static bool FKeshUInt16LessThanOrEqualToUInt32( const FKeshUInt16& UI16, const FKeshUInt32& UI32 )
	{
		return UI16.Value <= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 <= int8" )
	static bool FKeshUInt32LessThanOrEqualToInt8( const FKeshUInt32& UI32, const FKeshInt8& I8 )
	{
		return UI32.Value <= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 <= uint32" )
	static bool FKeshInt8LessThanOrEqualToUInt32( const FKeshInt8& I8, const FKeshUInt32& UI32 )
	{
		return I8.Value <= UI32.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint32 <= uint8" )
	static bool FKeshUInt32LessThanOrEqualToUInt8( const FKeshUInt32& UI32, uint8 UI8 )
	{
		return UI32.Value <= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 <= uint32" )
	static bool KeshUE4FTUInt8LessThanOrEqualToUInt32( uint8 UI8, const FKeshUInt32& UI32 )
	{
		return UI8 <= UI32.Value;
	}

	/* Int 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 <= int16" )
	static bool FKeshInt16LessThanOrEqualToInt16( const FKeshInt16& I161, const FKeshInt16& I162 )
	{
		return I161.Value <= I162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 <= uint16" )
	static bool FKeshInt16LessThanOrEqualToUInt16( const FKeshInt16& I16, const FKeshUInt16& UI16 )
	{
		return I16.Value <= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 <= int16" )
	static bool FKeshUInt16LessThanOrEqualToInt16( const FKeshUInt16& UI16, const FKeshInt16& I16 )
	{
		return UI16.Value <= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 <= int8" )
	static bool FKeshInt16LessThanOrEqualToInt8( const FKeshInt16& I16, const FKeshInt8& I8 )
	{
		return I16.Value <= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 <= int16" )
	static bool FKeshInt8LessThanOrEqualToInt16( const FKeshInt8& I8, const FKeshInt16& I16 )
	{
		return I8.Value <= I16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int16 <= uint8" )
	static bool FKeshInt16LessThanOrEqualToUInt8( const FKeshInt16& I16, uint8 UI8 )
	{
		return I16.Value <= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 <= int16" )
	static bool KeshUE4FTUInt8LessThanOrEqualToInt16( uint8 UI8, const FKeshInt16& I16 )
	{
		return UI8 <= I16.Value;
	}

	/* UInt 16 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 <= uint16" )
	static bool FKeshUInt16LessThanOrEqualToUUInt16( const FKeshUInt16& UI161, const FKeshUInt16& UI162 )
	{
		return UI161.Value <= UI162.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 <= int8" )
	static bool FKeshUInt16LessThanOrEqualToInt8( const FKeshUInt16& UI16, const FKeshInt8& I8 )
	{
		return UI16.Value <= I8.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 <= uint16" )
	static bool FKeshInt8LessThanOrEqualToUInt16( const FKeshInt8& I8, const FKeshUInt16& UI16 )
	{
		return I8.Value <= UI16.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint16 <= uint8" )
	static bool FKeshUInt16LessThanOrEqualToUInt8( const FKeshUInt16& UI16, uint8 UI8 )
	{
		return UI16.Value <= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 <= uint16" )
	static bool KeshUE4FTUInt8LessThanOrEqualToUInt16( uint8 UI8, const FKeshUInt16& UI16 )
	{
		return UI8 <= UI16.Value;
	}

	/* Int 8 */

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 <= int8" )
	static bool FKeshInt8LessThanOrEqualToInt8( const FKeshInt8& I81, const FKeshInt8& I82 )
	{
		return I81.Value <= I82.Value;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "int8 <= uint8" )
	static bool FKeshInt8LessThanOrEqualToUInt8( const FKeshInt8& I8, uint8 UI8 )
	{
		return I8.Value <= UI8;
	}

	UFUNCTION( Category = "Kesh|UE4 Fundamental Types|Math", BlueprintPure, DisplayName = "uint8 <= int8" )
	static bool KeshUE4FTUInt8LessThanOrEqualToInt8( uint8 UI8, const FKeshInt8& I8 )
	{
		return UI8 <= I8.Value;
	}

	
	/*************/
	/* Utilities */
	/*************/
	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Utilities", BlueprintPure, DisplayName = "As Currency (int64)")
		static FText KeshUE4FTInt64ToText(FKeshInt64 Data, FString CurrencyCode)
	{
		FNumberFormattingOptions* Options = new FNumberFormattingOptions();
		Options->SetMaximumFractionalDigits(0);

		return FText::AsCurrency(Data.Value, CurrencyCode, Options);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Utilities", BlueprintPure, DisplayName = "As Currency (UInt64)")
		static FText KeshUE4FTUInt64ToText(FKeshUInt64 Data, FString CurrencyCode)
	{
		FNumberFormattingOptions* Options = new FNumberFormattingOptions();
		Options->SetMaximumFractionalDigits(0);

		return FText::AsCurrency(Data.Value, CurrencyCode, Options);
	}

	UFUNCTION(Category = "Kesh|UE4 Fundamental Types|Utilities", BlueprintPure, DisplayName = "As Currency (Double)")
		static FText KeshUE4FTDoubleToText(FKeshDouble Data, FString CurrencyCode)
	{
		return FText::AsCurrency(Data.Value, CurrencyCode);
	}
};
