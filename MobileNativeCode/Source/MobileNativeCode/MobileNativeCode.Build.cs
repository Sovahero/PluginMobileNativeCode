using System.IO;
using UnrealBuildTool;
using System.Collections.Generic;
using Tools.DotNETCommon;

public class MobileNativeCode : ModuleRules
{
    //=======Path===================================================================
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

    private void AddFrameworks(string[] frameworks)
    {
        for (int i = 0; i < frameworks.Length; i+=2){
            if ((i % 2) == 0){
                if (frameworks[i + 1] == ""){
                    PublicAdditionalFrameworks.Add(
                        new Framework(
                        frameworks[i],
                        Path.Combine(PathThirdPartyIOS, "frameworks", frameworks[i] + ".embeddedframework.zip")
                        )
                    );
                }
                else{
                    PublicAdditionalFrameworks.Add(
                        new Framework(
                        frameworks[i],
                        Path.Combine(PathThirdPartyIOS, "frameworks", frameworks[i] + ".embeddedframework.zip"),
                        Path.Combine(frameworks[i] + ".framework/" + frameworks[i+1] + ".bundle")
                        )
                    );
                }
            }
        }
    }

    private void AddBundles(string[] bundles)
    {
        foreach (string thisBundle in bundles)
        {
            BundleResource newBundle = new BundleResource(Path.Combine(PathThirdPartyIOS, "bundle", thisBundle + ".bundle"));
            AdditionalBundleResources.Add(newBundle);
        }
    }

    //=======Main==================================================================
    public MobileNativeCode(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Public") });        
        PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private") });

        PublicDependencyModuleNames.AddRange(new string[]
            {
                "Engine",
                "Core",
                "CoreUObject",
                "InputCore",                
            }
        );

        PrivateDependencyModuleNames.AddRange(new string[]
            {
                "RenderCore",
                "Slate",
                "SlateCore"
            }
        );

        //-- Additional build steps
        LoadLib(Target);
    }

    //=====Enable libraries depending on the platform================
    public void LoadLib(ReadOnlyTargetRules Target)
    {
        //== If the Windows platform
        if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32)
        {
            //Add Include path
            PublicIncludePaths.Add(Path.Combine(PathThirdPartyWindows, "include"));

            string[] Libs = {
                /*"example.lib",
                    "example2.lib"*/
            };

            string[] DLLs = {
                /*"example.dll",
                   "example2.dll"*/
            };

            //Add Static Libraries Win
            foreach (string Lib in Libs)
            {
                PublicAdditionalLibraries.Add(Path.Combine(PathThirdPartyWindows, "lib", Lib));
            }

            //Add Dynamic Libraries Win
            foreach (string DLL in DLLs)
            {
                PublicDelayLoadDLLs.Add(Path.Combine(PathThirdPartyWindows, "lib", DLL));
            }
        }

        //== If the Android platform
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            string ArchArmV7a = "armeabi-v7a";
            string ArchArmV8a = "arm64-v8a";

            //for JNI
            PrivateDependencyModuleNames.AddRange(new string[]
                {
                    "Launch"
                }
            );

            //------ .h--------------------
            PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private", "Android") });

            //----- .so ------------------
            // To connect .so dynamic libraries also need to be added to .xml file

            // libc++_shared.so already added, but if you use the engine version 4.24 or less, you can uncomment these lines and in xml
            string[] Libs = {
				//"libc++_shared.so", 
            };

            foreach (string Lib in Libs)
            {
                PublicAdditionalLibraries.Add(Path.Combine(PathThirdPartyAndroid, ArchArmV7a, "lib", Lib));
                PublicAdditionalLibraries.Add(Path.Combine(PathThirdPartyAndroid, ArchArmV8a, "lib", Lib));
            }

            //-------XML---------------------------------------
            {/* Additional steps for building on Android. Basically, all the basic information is specified in xml.
             * The xml file is located on the path: "Plugins\MobileNativeCode\Source\MobileNativeCode\MobileNativeCode_UPL_Android.xml"
             */}

            AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(ModuleDirectory, "MobileNativeCode_UPL_Android.xml"));
        }

        //== If the IOS platform
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PrivateDependencyModuleNames.AddRange(new string[]
                {
                    "Launch"
                }
            );
            //----------------- p-list ------------------
            {/* The xml file specifies additional lines for Info.plist
              * The xml file is located on the path: "Plugins\MobileNativeCode\Source\MobileNativeCode\MobileNativeCode_UPL_iOS.xml"
              */}
            
            AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(ModuleDirectory, "MobileNativeCode_UPL_iOS.xml"));

            //------------------- .h--------------------
            PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private", "IOS") });
            
            //------------------- Public framework------------------------------------
            {/* A list of public frameworks from Apple that you need to use when building.
               * You can view the entire list here: https://developer.apple.com/documentation/technologies
               */}
            
            PublicFrameworks.AddRange(
                    new string[]
                    {
                        "EventKit",
                        "GLKit",
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
                        "CoreFoundation",
                        "AdSupport",
                        "MessageUI",
                        "AppTrackingTransparency",
                        "WebKit",
                        "AVFoundation",
                        "Accelerate",
                        "LocalAuthentication",
                        "SafariServices",
                        "AuthenticationServices",
                        "UserNotifications",
                    }
             );

            //------------------- Private framework---------------------------------------
            {/* Third-party libraries are called frameworks and are connected in this line.
             * 
             * To get the framework and use it in the UE4 build system. It should have the following folder structure:
             *  MyNameFramework.embeddedframework.zip            <== Pack in *.zip can be used in WinRar
             *       -MyNameFramework.embeddedframework
             *           - MyNameFramework.framework                       <== The source framework that is built using xcode
             * 
             * List the names of your frameworks here, separated by commas.
             * If the framework contains its own package, 
             * then the next line with the location in the framework of this package is added to the array after the name of the framework. 
             * If the framework does not contain a package, an empty string is added after the name.
             * 
             * For example on the path: "Plugins\MobileNativeCode\Source\MobileNativeCode\ThirdParty\IOS\frameworks"
             * PersonalizedAdConsent.the framework contains the PersonalizedAdConsent.bundle 
             * in the root of the framework, so you need to specify "PersonalizedAdConsent" twice in the array.
             * 
             *  If *.framework does not contain a*. bundle, then the second line in the array would be empty.
             */}
            
            string[] frameworks = {
             // "PersonalizedAdConsent", "PersonalizedAdConsent",
             // "GoogleMobileAdsMediationTestSuite", "Resources/GoogleMobileAdsMediationTestSuite", // <== The second line indicates the location of the *.bundle in the *.framework
             // "ExamleMyFramework", "", // <== without *.bundle
            };

            AddFrameworks(frameworks);

            //------------------- Private Bundle ---------------------------------------
            {/* Bundle is used to package your own resources in *.ipa file
             * 
             * Along the path is a test image: "Plugins\MobileNativeCode\Source\MobileNativeCode\ThirdParty\IOS\bundle\IosDrawable.bundle"
             * that can be used as follows in ObjC:
             *
             *   NSString* bundlePath = [[NSBundle mainBundle] pathForResource: @"IosDrawable" ofType: @"bundle"];
             *   NSBundle* bundle = [NSBundle bundleWithPath: bundlePath];
             *   NSString* resource = [bundle pathForResource: @"my_test_icon" ofType: @"png"];
             *   NSURL* imageUrl = [NSURL fileURLWithPath: resource];
             */}

            string[] bundles = {
                     "IosDrawable",
                  // "ExampleMyBundle", 
            };

            AddBundles(bundles);
        }
    }
    //=============================================================================
}
