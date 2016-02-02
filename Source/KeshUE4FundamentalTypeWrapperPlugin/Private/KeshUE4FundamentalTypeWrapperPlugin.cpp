// Copyright 2015 Matthew Chapman, Inc. All Rights Reserved.

#include "KeshUE4FundamentalTypeWrapperPluginPrivatePCH.h"
#include "KeshUE4FundamentalTypeWrapperPlugin.h"

IMPLEMENT_MODULE( FKeshUE4FundamentalTypeWrapperPlugin, KeshUE4FundamentalTypeWrapperPlugin )
DEFINE_LOG_CATEGORY( LogKeshUE4FundamentalTypeWrapperPlugin );

void FKeshUE4FundamentalTypeWrapperPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FKeshUE4FundamentalTypeWrapperPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}
