#pragma once

#include "Modules/ModuleManager.h"

class FMobileNativeCodeModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	 * Init
	 */
	void Initialization();

	/**
	 * Can the mobile platform call functions
	 */
	static bool IsSupported();
};
