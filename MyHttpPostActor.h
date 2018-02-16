// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"

//Dir 
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"

//#include "Json.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"
#include "Runtime/Json/Public/Serialization/JsonSerializer.h"
#include "Engine/Engine.h"

//#include "JsonUtilities.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

//last include
#include "MyHttpPostActor.generated.h"

////TODO SET THIS OUTSIDE LATER
USTRUCT()
struct FRequest_Order {
	GENERATED_BODY()
		UPROPERTY() FString language_text;
	UPROPERTY() FString language_value;
	UPROPERTY() FString orderId_text;
	UPROPERTY() FString orderId_value;

	FRequest_Order() {}
};

USTRUCT()
struct FResponse_Order {
	GENERATED_BODY()

		UPROPERTY() FString firstParameter;

	FResponse_Order() {}
};

////Struct available to consult Last data readed
//If you want this to appear in BP, make sure to use this instead
//USTRUCT(BlueprintReadWrite, VisibleAnywhere)
//USTRUCT()
USTRUCT(BlueprintType)
struct FResponse_LastOrder {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, VisibleAnywhere) FString wine_img;
	UPROPERTY() FString wine_name;
	UPROPERTY() FString color_img; //This might be Id
	UPROPERTY() FString color_name; //not necesary its at general id info

	UPROPERTY() FString subcolor_id; //Receiving NULL
	UPROPERTY() FString hint_id;
	UPROPERTY() FString drinking_temp;

	UPROPERTY() FString flavor_one_img;
	UPROPERTY() FString flavor_one_name;
	UPROPERTY() FString flavor_two_img;
	UPROPERTY() FString flavor_two_name;
	UPROPERTY() FString taste_img;
	UPROPERTY() FString taste_name;
	UPROPERTY() FString occasion_img;
	UPROPERTY() FString occasion_name;
	UPROPERTY() FString dish1_img;
	UPROPERTY() FString dish1_name;
	UPROPERTY() FString dish2_img;
	UPROPERTY() FString dish2_name;


	FResponse_LastOrder() {}
};

UCLASS()
class EASYBACCHUSAR_API AMyHttpPostActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyHttpPostActor();

	// Sets default values for this actor's properties
	AMyHttpPostActor(const class FObjectInitializer& ObjectInitializer);

	////////////////////////
	/* HTTP Functions */
	TSharedRef<IHttpRequest> PostRequest(/*FString Subroute, */FString ContentJsonString);
	FString HACK_SetContentJson(TSharedRef<IHttpRequest>& Request, FString ContentJsonString);
	FString HACK_SetContentBody(TSharedRef<IHttpRequest>& Request);
	FString HACK_SetContentAsString(TSharedRef<IHttpRequest>& Request);
	void Send(TSharedRef<IHttpRequest>& Request);

	template <typename StructType>
	void GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput);
	template <typename StructType>
	void GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput);

	/*Assign this function to call when the GET request processes sucessfully*/
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void saveMyArParams(TSharedRef<TJsonReader<>> Reader);
	FString PercentEncode(const FString & Source);

	//Last Saved Info.
	//USTRUCT(BlueprintType)
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		FResponse_LastOrder myLastJsonRequestResult;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FString getMyJsonSharedFolder();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintType)
	UFUNCTION(BlueprintCallable)
		void MyLocalJsonFileCall();

	UFUNCTION()
		//UFUNCTION(BlueprintCallable)
		void MyHttpCall();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bDebugMode = true;

private:
	FHttpModule* Http;
	FString ApiBaseUrl = "http://easybacchus.ccube9projects.com/app/User/get_ar_contents";
	FString myLocalJsonPath = "C:/Users/carles/Documents/develop/Unreal/mookan/MyJson149/Content/sharedFolderJson/ARContent.json";
};

