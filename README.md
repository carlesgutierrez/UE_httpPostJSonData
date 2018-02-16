# UE_httpPostJSonData

1 -  Modify XXXXXXX_API for your onw NAME_API

2 - Add "Http", "Json", "JsonUtilities" to your XXXX.Build.cs

	PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","Http", "Json", "JsonUtilities" });

3  - Set Local sharedFolderJson at desired place: 

	if ( bJsonLocalOutSiteMainProject == true ): Copy "sharedFolderJson" outside Main project Folder. --> "../../sharedFolderJson/ARContent.json"

	else:  Copy "sharedFolderJson" at Content folder.