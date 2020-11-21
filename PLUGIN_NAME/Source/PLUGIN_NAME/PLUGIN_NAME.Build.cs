using System.IO;
using UnrealBuildTool;

public class PLUGIN_NAME : ModuleRules
{
    //=======Path/Пути===================================================================
    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "ThirdParty/")); }
    }

    private string PathThirdPartyAndroid
    {
        get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "Android/")); }
    }

    private string PathThirdPartyIOS
    {
        get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "IOS/")); }
    }

    private string PathThirdPartyWindows
    {
        get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "Windows/")); }
    }

    //=======Main/Главный==================================================================
    public PLUGIN_NAME(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Public") });
        PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private") });

        PublicDependencyModuleNames.AddRange(new string[]
            {
                "Engine",
                "Core",
                "CoreUObject"
            }
        );

        PrivateDependencyModuleNames.AddRange(new string[]
            {
                "Slate",
                "SlateCore",
            }
        );

        //~~~~~~~~Подключить статические или динамические библиотеки/Enable static or dynamic libraries~~~~~~~~~~~~~~
        LoadLib(Target);
    }

    //=====Подключить библиотеки в зависимости от платформы/Enable libraries depending on the platform================
    public void LoadLib(ReadOnlyTargetRules Target)
    {
        //----------Если платформа Windows/If the Windows platform-----------------------------------------------------------------------------------
        if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32)
        {
            //Add Include path /Добавить видиомсть папки include
            PublicIncludePaths.Add(Path.Combine(PathThirdPartyWindows, "include"));

            string[] Libs = {
                /*"example.lib",
                    "example2.lib"*/
            };

            string[] DLLs = {
                /*"example.dll",
                   "example2.dll"*/
            };

            //Add Static Libraries/Добавление Статических Библиотек
            foreach (string Lib in Libs)
            {
                PublicAdditionalLibraries.Add(Path.Combine(PathThirdPartyWindows, "lib", Lib));
            }

            //Add Dynamic Libraries/Добавление Динамических Библиоте
            foreach (string DLL in DLLs)
            {
                PublicDelayLoadDLLs.Add(Path.Combine(PathThirdPartyWindows, "lib", DLL));
            }
        }

        //----------Если платформа Android/If the Android platform-------------------------------------------------------------------------------------
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            string ArchArmV7a = "armeabi-v7a";
            string ArchArmV8a = "arm64-v8a";

            PrivateDependencyModuleNames.AddRange(new string[]
                {
                    "Launch"
                }
            );

            //------------------- .h--------------------
            PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private", "Android") });
            //-------------------- .so ------------------
            string[] Libs = {
				#if UE_4_25_OR_LATER
				#else
				"libc++_shared.so" ,
				#endif
				//"Example.so",
                //"Example2.so"
            };

            foreach (string Lib in Libs)
            {
                PublicAdditionalLibraries.Add(Path.Combine(PathThirdPartyAndroid, ArchArmV7a, "lib", Lib));
                PublicAdditionalLibraries.Add(Path.Combine(PathThirdPartyAndroid, ArchArmV8a, "lib", Lib));
            }
            //----------------------------XML---------------------------------------
#if UE_4_25_OR_LATER
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PathThirdPartyAndroid, "AndroidV25.xml"));
#else
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PathThirdPartyAndroid, "AndroidV24.xml"));
#endif
        }

        //----------Если платформа IOS/If the IOS platform-------------------------------------------------------------------------------------------
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PrivateDependencyModuleNames.AddRange(new string[]
                {
                    "Launch"
                }
            );
            //----------------- p-list ------------------            
            AdditionalPropertiesForReceipt.Add( "IOSPlugin", Path.Combine(ModuleDirectory, "Private", "IOS", "plist.xml") );
            //------------------- .h--------------------
            PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private", "IOS") });
            PublicIncludePaths.Add(Path.Combine(PathThirdPartyIOS, "include"));
            //------------------- Public framework------------------------------------
            PublicFrameworks.AddRange(
                    new string[]
                    {
                        "CoreTelephony",
                        "SystemConfiguration",
                        "UIKit",
                        "Foundation",
                        "CoreGraphics",
                        "MobileCoreServices",
                        "StoreKit",
                        "CFNetwork",
                        "CoreData",
                        "Security",
                        "CoreLocation",
                        "WatchConnectivity",
                        "MediaPlayer",
                        "CoreFoundation"
                    }
             );
            //------------------- Private framework---------------------------------------
            string[] frameworks = {
                /*"example", //example.framework
                    "example2" //example2.framework*/
            };

            foreach (string l_Framework in frameworks)
            {
                PublicAdditionalFrameworks.Add(
                    new Framework(l_Framework,
                    Path.Combine(PathThirdPartyIOS, "frameworks", "example.framework.zip"), "" //example.framework.zip
                    )
                );
            }
        }
        //----------Неподдерживаемая платформа/Unsupported platform--------------------------
        else
        {
            string Err = string.Format("{0} dedicated server is made to depend on {1}. We want to avoid this, please correct module dependencies.", Target.Platform.ToString(), this.ToString()); System.Console.WriteLine(Err);
        }
    }
    //=============================================================================
}
