![Logo](screenshot/Logo2.png)

# Mobile Native Code Plugin for Unreal Engine 4
**(*Rus*)**
При разработке мобильного приложения на базе Unreal engine 4 рано или поздно случается , что нужно получить доступ к функционалу которого нет в C++/Blueprint. Например:
* Получить абсолютные пути к временным папкам для сохранения собственных файлов.
* Считать информацию с датчиков (Акселерометр, Барометр и т.д.).
* Получить информацию о телефоне.
* Взаимодействовать с другими приложениями.
* И т.д.

 **Mobile Native Code Plugin** - служит основой для собственного мобильного плагина в Unreal Engine 4 для платформ Android и IOS. В нём реализован удобный вызов нативного кода Java(JNI) и Objective-c, а также примеры подключения статических и динамических библиотек в систему сборки. Просто переименуйте все названия *PLUGIN_NAME* во всех папках и файлах на собственные и получите нужный вам плагин.

* **Требуется Unreal Engine 4.21 или выше.**

**(*Eng*)**
When developing a mobile application based on Unreal engine 4, sooner or later it happens that you need to get access to functionality that is not available in C++/Blueprint. For example:
* Get absolute paths to temporary folders to save your own files.
* Read information from sensors (Accelerometer, Barometer, etc.).
* Get information about your phone.
* Interact with other apps.
* Etc.

 **Mobile Native Code Plugin** - serves as the basis for the native mobile plugin in Unreal Engine 4 for Android and IOS platforms. It provides a convenient call to native Java code(JNI) and Objective-c, as well as examples of connecting static and dynamic libraries to the build system. Just rename all the *PLUGIN_NAME* names in all folders and files to your own and get the plugin you need.

* **Requires Unreal Engine 4.21 or higher.**



## Особенности / Features
![Java](screenshot/CallJava2.png)
![ObjC](screenshot/Call_IOS1.png)
**(*Rus*)**
* Собирается на ndk-14 и ndk-21 для Android
* Вызов нативного кода Java одной функцией из C++
* Примеры функций, как взаимодействовать с нативным кодом
Находятся по пути: 

> **Blueprint\C++** - PLUGIN_NAME\Source\PLUGIN_NAME\Private\PLUGIN_NAMEBPLibrary.cpp
> **Android** - PLUGIN_NAME\Source\PLUGIN_NAME\Private\Android\Java\TestJavaClass.java
> **IOS** - PLUGIN_NAME\Source\PLUGIN_NAME\Private\IOS\ObjC\TestIosClass.mm
* Visual Studio/(Если IOS - Xcode) нужен для сборки плагина
* Протестировано на 2 версия Unreal Engine 4 (4.24/4.25) и 3 телефонах
* Весь код разбит на блоки для более удобного понимания
> // #~~~~~~~~~ begin 1 ~~~~~~~~~~
> // ~~~~~~~~~~~ end 1 ~~~~~~~~~~

**(*Eng*)**
* Builds on ndk-14 and ndk-21 for Android
* Calling native Java code with a single function from C++
* Examples of functions for interacting with native code
Located on the path:
> **Blueprint\C++** - PLUGIN_NAME\Source\PLUGIN_NAME\Private\PLUGIN_NAMEBPLibrary.cpp
> **Android** - PLUGIN_NAME\Source\PLUGIN_NAME\Private\Android\Java\TestJavaClass.java
> **IOS** - PLUGIN_NAME\Source\PLUGIN_NAME\Private\IOS\ObjC\TestIosClass.mm
* Visual Studio/(If IOS - Xcode) is needed to build the plugin
* Tested on 2 versions of Unreal Engine 4 (4.24/4.25) and 3 phones
* The entire code is divided into blocks for easier understanding
> // #~~~~~~~~~ begin 1 ~~~~~~~~~~
> // ~~~~~~~~~~~ end 1 ~~~~~~~~~~

## Установка / Setup
### **(*Rus*)**
1) Скопируйте *PLUGIN_NAME* в папку *Plugins*, расположенную в главном пути вашего проекта (Если её нет, то создайте).

![PathPlugin](screenshot/PathPlugin.png)

2) Включите *PLUGIN_NAME* в *Edit -> Plugins -> Installed -> Mobile-> PLUGIN_NAME*.

![EnablePlugin](screenshot/EnablePlugin.png)

3) В LevelBlueprint уровня создайте схему.

![LevelBlueprint](screenshot/LevelBlueprint1.png)

 4) **Запустите на вашем мобильном устройстве.**
 
### **(*Eng*)**
1) Copy the *PLUGIN_NAME* folder *Plugins* are located in the main path of your project (If not, then create).

![PathPlugin](screenshot/PathPlugin.png)

2) Turn on the *PLUGIN_NAME* is *Edit -> Plugins -> Installed -> Mobile-> PLUGIN_NAME*.

![EnablePlugin](screenshot/EnablePlugin.png)

3) in the LevelBlueprint level, create a diagram.

![LevelBlueprint](screenshot/LevelBlueprint1.png)

4) **Run on your mobile device.**
# Тестирование / Testing

* *Unreal Engine 4.24* - **Nexus 5** - *OpenGL ES2* - *armeabi-v7a* - **ndk-r14b**

![Nexus5](screenshot/Nexus5_1.png)

* *Unreal Engine 4.25* - **Honor Play** - *OpenGL ES3.1* - *arm64-v8a* - **ndk-r21b**

![HonorPlay](screenshot/HonorPlay_1.png)

* *Unreal Engine 4.25* - **iPhone 7** - *Xcode 12.1* - *macOS Catalina 10.15.6*

![iPhone7](screenshot/iPhone7_1.png)

# Дополнительная информация / Additional information

## (RUS) Для Android
Для вызова собственного Java класса:

* Добавьте свой Java класс в папку *PLUGIN_NAME\Source\PLUGIN_NAME\Private\Android\Java*
		
* Измените *package* на: **package com.epicgames.ue4;**
 
* Класс должен быть публичным (*public class*), а его функции статичными (*public static void*)

* Перед классом и функциями добавьте *@Keep*

* Перейдите в *\PLUGIN_NAME\Source\PLUGIN_NAME\Private* и откройте *PLUGIN_NAMEBPLibrary.cpp*.
  В данном файле продемонстрированы 5 функции для вызова Java кода.

* Java код вызывается с помощью **AndroidUtils::CallNativeAndroid< ReturnType >("com/epicgames/ue4/YourClass", "YourFunction", false, "arg1","arg2","arg3")**, если функция что-то возвращает.

   В случае если Java функция ничего не возвращает (Void) то вызывается **AndroidUtils::CallNativeAndroidVoid("com/epicgames/ue4/YourClass", "YourFunction", false, "arg1","arg2","arg3")**

* *ReturnType* указывается в зависимости от возвращаемого типа. *1 аргумент* это package+название вашего класса, *2 аргумент* название вашей функции, *3 аргумент* указывает - нужно ли передать Activity данного сеанса. Далее кол-во аргументов может быть передано сколько угодно, в зависимости от того, что принимает ваша функция.

* Если ваша Java функция принимает специфичный тип (напр. *jobject*), то перед вызовом функции **CallNativeAndroid** нужно вашу C++ переменную предварительно конвертировать в *jobject*. Больше информации о конвертации можно найти в файле *PLUGIN_NAME\Source\PLUGIN_NAME\Private\Android\Utils\JavaConvert.cpp*

* Асинхронный вызов Java происходит посредствам диспетчеров - код Java вызывает функцию C++, которая в свою очередь активирует его.

* (**Не рекомендуется**) Вы можете указывать свой *package* для Java классов. 
Перейдите в *PLUGIN_NAME\Source\PLUGIN_NAME\ThirdParty\Android* и в файлах *AndroidV24.xml* (*Если UE4.21-UE4.24*) и *AndroidV25.xml* (*Если UE4.25 и Выше*) укажите новый путь копирования и объявление своего класса.


* При добавлении нового Java класса или изменении текущего - удаляйте папку **Intermediate** в папке вашего проекта.

## (ENG) for Android
To call your own Java class:

* Add your Java class to the folder *PLUGIN_NAME\Source\PLUGIN_NAME\Private\Android\Java*

* Change the value of *package* at: **package com.epicgames.ue4;**

* The class must be public (*public class*) and its functions must be static (*public static void*)

* before the class and functions, add ***@Keep***

* Go to *PLUGIN_NAME\Source\PLUGIN_NAME\Private* and open *PLUGIN_NAMEBPLibrary.cpp*.
This file demonstrates 5 functions for calling Java code.

* Java code is called using **AndroidUtils:: CallNativeAndroid< ReturnType >("com/epicgames/ue4/YourClass", "YourFunction", false, "arg1","arg2", "arg3")** if the function returns something.

  If the Java function returns nothing (Void) then called **AndroidUtils:: CallNativeAndroidVoid ("com/epicgames/ue4/YourClass", "YourFunction", false, "arg1", "arg2", " arg3")**

* *ReturnType* is specified depending on the return type. *1 argument* is package+the name of your class, *2 argument* the name of your function, *3 argument* indicates whether to pass the activity of this session. Further, the number of arguments can be passed as many as you want, depending on what your function accepts.

* If your Java function accepts a specific type (e.g. *jobject*), then before calling the **CallNativeAndroid function** you need to convert your C++ variable to *jobject* first. More information about conversion can be found in the file *PLUGIN_NAME\Source\PLUGIN_NAME\Private\Android\Utils\JavaConvert.cpp*

* Asynchronous Java invocation occurs through dispatchers UE4 - Java code calls a C++ function, which in turn activates it.

* (**Not recommend**) You can set the value of *package* for Java classes.
Go to *PLUGIN_NAME\Source\PLUGIN_NAME\Third Party\Android* and in files *AndroidV24.xml* (*If UE4. 21-UE4. 24*) and *AndroidV25.xml* (*If UE4. 25 and Higher*) specify the new copy path and your class Declaration.

* When adding a new Java class or changing the current one, delete the **Intermediate** folder in your project folder.


## (RUS) Для IOS
Для вызова Objective-C кода 

* Добавьте свой ObjC класс в папку *PLUGIN_NAME\Source\PLUGIN_NAME\Private\IOS\ObjC*
* Подключите его в *PLUGIN_NAME\Source\PLUGIN_NAME\Private\PLUGIN_NAMEBPLibrary.cpp*
* Язык Objective-C можно писать в **.cpp* файлах, но лучше использовать **.mm*
Он очень похож на C++, лишь синтаксис другой.
 Для лучше понимания прочитайте: [Objective-C](https://ru.qaz.wiki/wiki/Objective-C)
 * Некоторый код требует ключ и разрешение (Или по другому Description). Весь список можно увидеть по ссылкам:
 [Description Apple](https://developer.apple.com/documentation/bundleresources/information_property_list/protected_resources)
 [Key Apple](https://developer.apple.com/library/archive/documentation/General/Reference/InfoPlistKeyReference/Articles/iPhoneOSKeys.html#//apple_ref/doc/uid/TP40009252-SW3)
 * Эти разрешения можно добавлять в самом Unreal engine 4 в секции IOS, но предлагаю для этого использовать файл *plist.xml* по пути *PLUGIN_NAME\Source\PLUGIN_NAME\Private\IOS*
В закомментированных строках пример, как добавляется информация в p-list
* Список подключенных публичных Framework вы можете увидеть в файле *PLUGIN_NAME\Source\PLUGIN_NAME\PLUGIN_NAME.Build.cs*
![build](screenshot/IOS_framework.png)
Если нужного вам Framework нет, то добавьте его самостоятельно, просто продолжив список.
[Узнать больше о Framework IOS](https://developer.apple.com/documentation/technologies)
(Возможно некоторых Framework нет в системе сборки UE4)
* В файле *TestIosClass.mm* продемонстрированы, как *static* функции, так и паттерн одиночка.

## (ENG) For iOS
To call Objective-C code

* Add your ObjC class to the *PLUGIN_NAME\Source\PLUGIN_NAME\Private\IOS\ObjC folder*
* Connect it to *PLUGIN_NAME\Source\PLUGIN_NAME\Private\PLUGIN_NAMEBPLibrary.cpp*
* The Objective-C language can be written in **. cpp* files, but it is better to use **. mm*
It is very similar to C++, but the syntax is different.
* For some code, you need the key and the resolution (or another Description). The entire list can be seen at the links:
[Description Apple](https://developer.apple.com/documentation/bundleresources/information_property_list/protected_resources)
[Key Apple](https://developer.apple.com/library/archive/documentation/General/Reference/InfoPlistKeyReference/Articles/iPhoneOSKeys.html#//apple_ref/doc/uid/TP40009252-SW3)
* These permissions can be added in Unreal engine 4 itself in the IOS section, but I suggest using the file *plist.xml* by path *PLUGIN_NAME\Source\PLUGIN_NAME\Private\IOS*
In the commented lines, there is an example of how information is added to the p-list
* You can see the list of connected public libraries in the file *PLUGIN_NAME\Source\PLUGIN_NAME\PLUGIN_NAME.Build.cs*
![build](screenshot/IOS_framework.png)
If you don't have the Framework you need, add it yourself by simply continuing the list.
[Learn more about the IOS Framework](https://developer.apple.com/documentation/technologies)
(Some Framework may not be present in the UE4 build system)
* In the file *TestIosClass.mm* both *static* functions and the single-player pattern are demonstrated.