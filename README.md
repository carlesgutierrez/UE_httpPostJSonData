# UE_httpPostJSonData

1 -  Modify XXXXXXX_API for your onw NAME_API

2 - Add "Http", "Json", "JsonUtilities" to your XXXX.Build.cs

	PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","Http", "Json", "JsonUtilities" });

3  - Add a Local Json File in Content folder like that: 

	"Content/sharedFolderJson/ARContent.json"