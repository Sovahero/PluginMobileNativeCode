#include "PLUGIN_NAME.h"

#define LOCTEXT_NAMESPACE "FPLUGIN_NAMEModule"

void FPLUGIN_NAMEModule::StartupModule()
{
	// Этот код будет выполнен после загрузки вашего модуля в память; точное время указано в файле .plugin для каждого модуля
	
}

void FPLUGIN_NAMEModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	// Эта функция может быть вызвана во время выключения для очистки вашего модуля. Для модулей, поддерживающих динамическую перезагрузку,
	// мы вызываем эту функцию перед выгрузкой модуля.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPLUGIN_NAMEModule, PLUGIN_NAME)