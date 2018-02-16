# UE_httpPostJSonData

1 -  Modify XXXXXXX_API for your onw NAME_API

2 - Add "Http", "Json", "JsonUtilities" to your XXXX.Build.cs

	PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","Http", "Json", "JsonUtilities" });

3  - Set Local sharedFolderJson outside Main project Folder. For default local content is located at /Content/, then copy sharedFolderJson at --> "../../sharedFolderJson/ARContent.json"