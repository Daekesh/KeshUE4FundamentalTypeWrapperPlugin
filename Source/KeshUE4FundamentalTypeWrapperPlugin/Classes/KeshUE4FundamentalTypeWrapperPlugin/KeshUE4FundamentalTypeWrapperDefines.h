// Copyright 2014-2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma once

#undef NULL
#define NULL nullptr
#define KCPPPWPLog( Level, Text ) UE_LOG( LogKeshUE4FundamentalTypeWrapperPlugin, Level, TEXT( Text ) )
#define KCPPPWPLogF( Level, Format, ... ) UE_LOG( LogKeshUE4FundamentalTypeWrapperPlugin, Level, TEXT( Format ), __VA_ARGS__ )
