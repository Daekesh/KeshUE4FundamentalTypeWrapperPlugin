// Copyright 2015 Matthew Chapman, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN( LogKeshUE4FundamentalTypeWrapperPlugin, Log, All );

/**
 * The public interface to this module.  In most cases, this interface is only public to sibling modules 
 * within this plugin.
 */
class IKeshUE4FundamentalTypeWrapperPlugin : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline IKeshUE4FundamentalTypeWrapperPlugin& Get()
    {
        return FModuleManager::LoadModuleChecked<IKeshUE4FundamentalTypeWrapperPlugin>( "KeshUE4FundamentalTypeWrapperPlugin" );
    }

    /**
     * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
     *
     * @return True if the module is loaded and ready to use
     */
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded( "KeshUE4FundamentalTypeWrapperPlugin" );
    }
};

