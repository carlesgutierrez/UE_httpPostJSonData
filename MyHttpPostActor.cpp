// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHttpPostActor.h"


// Sets default values
AMyHttpPostActor::AMyHttpPostActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Sets default values
AMyHttpPostActor::AMyHttpPostActor(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//When the object is constructed, Get the HTTP module
	Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AMyHttpPostActor::BeginPlay()
{
	if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("BeginPlay HttpPostActor"));

	if (bOnlineMode) {
		if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("--> HttpJsonCall"));
		MyHttpCall();
	}
	else {
		if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("--> LocalJsonCall"));
		MyLocalJsonFileCall();
	}

	Super::BeginPlay();
}

// Called every frame
void AMyHttpPostActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (IsInputKeyDown(EKeys::A))

	////#if !UE_BUILD_SHIPPING
	//FVector drawPos(0.0f);
	//FColor drawColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f).ToFColor(true);
	//float drawDuration = 0.0f;
	//bool drawShadow = true;
	//DrawDebugString(GEngine->GetWorldFromContextObjectChecked(this), drawPos, *FString::Printf(TEXT("%s[%d]"), TEXT("test"), 12345), NULL, drawColor, drawDuration, drawShadow);
	////#endif //!UE_BUILD_SHIPPING
	//UE_LOG(LogTemp, Warning, TEXT("Hell"));

}

FString AMyHttpPostActor::getMyJsonSharedFolder() {

	FString filePath;
	FString filePathAbsolute;

	if (true) {
		//Will not easy work on Android or IOS -- >https://answers.unrealengine.com/questions/120796/adding-custom-files-to-the-android-content.html?sort=oldest
		filePath = FPaths::ProjectContentDir(); //Decrepated  FPaths::GameContentDir();
		//filePath += "sharedFolderJson/ARContent.json";
		filePath += "../../sharedFolderJson/ARContent.json";

		filePathAbsolute = FPaths::ConvertRelativePathToFull(filePath);
		filePath = filePathAbsolute;
		if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("looking at filePath %s"), *filePath);
	}
	else {//Static Path
		filePath = FString(myLocalJsonPath);
	}

	return filePath;
}

//-------------------------------------------
void AMyHttpPostActor::MyLocalJsonFileCall() {

	FString fileContent = "";
	FString filePath = getMyJsonSharedFolder();

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	//FString PlatformFileName = PlatformFile.GetName();
	//if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("PlatformFileName %s"), *PlatformFileName); --> PhysicalFile

	if (PlatformFile.FileExists(*filePath))
	{
		if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("File found"));
		FFileHelper::LoadFileToString(fileContent, *filePath);

		//Create a reader pointer to read the json data
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(fileContent);
		saveMyArParams(Reader);

	}
	else
	{
		//if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("File not found");
		if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("File not found. Folder used was [%s]"), *filePath);
	}

}

///*Http calls*/
//This is really just some semantics for cleaner code as well.
void AMyHttpPostActor::Send(TSharedRef<IHttpRequest>& Request) {
	Request->ProcessRequest();
}
//POST REQUEST
TSharedRef<IHttpRequest> AMyHttpPostActor::PostRequest(/*FString Subroute, */FString ContentJsonString) {
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();// = RequestWithRoute(Subroute);

	Request->SetURL(ApiBaseUrl);
	Request->SetVerb("POST");
	//Others alternatives
	FString urlParams;
	if (true) { //Now working... Not sure if because is adding parameters to the call request.
				//urlParams = HACK_SetContentAsString(Request);
				//urlParams = HACK_SetContentBody(Request);
		urlParams = HACK_SetContentJson(Request, ContentJsonString);
		Request->SetContentAsString(urlParams);
	}
	else {
		//Json Contend From Structs
		Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
		Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded")); //Required
		Request->SetHeader(TEXT("Accepts"), TEXT("application/json")); //TODO check 
		Request->SetContentAsString(ContentJsonString);
	}

	//Resulting Request
	if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("ContentJsonString: %s %s %s"), *Request->GetVerb(), *Request->GetURL(), *ContentJsonString);
	////////////////////////////////////////////////////////////

	return Request;
}

//--------------------------------------------------------
FString AMyHttpPostActor::HACK_SetContentJson(TSharedRef<IHttpRequest>& Request, FString ContentJsonString) {

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded")); //Required
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	//// Serialize data to json string
	FString OutputString = ContentJsonString;
	//TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	//FJsonSerializer::Serialize(RequestJsonObj->GetRootObject().ToSharedRef(), Writer);

	////if(bDebugMode)UE_LOG(LogVaRest, Log, TEXT("Request (json): %s %s %sJSON(%s%s%s)JSON"), *HttpRequest->GetVerb(), *HttpRequest->GetURL(), LINE_TERMINATOR, LINE_TERMINATOR, *OutputString, LINE_TERMINATOR);

	return OutputString;
}
//--------------------------------------------------------
FString AMyHttpPostActor::HACK_SetContentBody(TSharedRef<IHttpRequest>& Request) {
	//TODO THIS IS NOT BODYCONTENT. ITs equal than HACK_SetContentAsString

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded")); //Required


	FString UrlParams = "";
	uint16 ParamIdx = 0;

	// Loop through all the values and prepare additional url part
	for (int i = 0; i < 2; i++)
	{
		FString Key;
		FString Value;

		if (i == 0) {
			Key = "message";
			Value = "1";
		}
		else if (i == 1) {
			Key = "qr_code";
			Value = "1";
		}
		else {
			Key = "";
			Value = "";
		}
		if (!Key.IsEmpty() && !Value.IsEmpty())
		{
			UrlParams += ParamIdx == 0 ? "" : "&";
			UrlParams += PercentEncode(Key) + "=" + PercentEncode(Value);
		}

		ParamIdx++;
	}

	if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("Request (url body): %s"), *UrlParams);

	return UrlParams;
}

//---------------------------------------------------
FString AMyHttpPostActor::HACK_SetContentAsString(TSharedRef<IHttpRequest>& Request) {

	Request->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

	FString UrlParams = "";
	uint16 ParamIdx = 0;

	// Loop through all the values and prepare additional url part
	if (true) {
		for (int i = 0; i < 2; i++)
		{
			FString Key;// = RequestIt.Key();
			FString Value;// = RequestIt.Value().Get()->AsString();

			if (i == 0) {
				Key = "message";
				Value = "1";
			}
			else if (i == 1) {
				Key = "qr_code";
				Value = "1";
			}
			else {
				Key = "";
				Value = "1";
			}

			if (!Key.IsEmpty() && !Value.IsEmpty())
			{
				UrlParams += ParamIdx == 0 ? "" : "&";
				UrlParams += PercentEncode(Key) + "=" + PercentEncode(Value);
			}

			if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("UrlParams %s"), *UrlParams);

			ParamIdx++;
		}
	}

	return UrlParams;
}

/*Http calls*/
void AMyHttpPostActor::MyHttpCall()
{
	UE_LOG(LogTemp, Warning, TEXT("MyHttpCall Active"));

	//Step 1 Create te Struct
	FRequest_Order myOrderParamJson;
	myOrderParamJson.language_text = TEXT("language");
	myOrderParamJson.language_value = TEXT("1");			//1;
	myOrderParamJson.orderId_text = TEXT("qr_code");
	myOrderParamJson.orderId_value = TEXT("1");				//1;

															//2 Convert Struct into JSonContent and Send the POST Request
	FString ContentJsonString;
	GetJsonStringFromStruct<FRequest_Order>(myOrderParamJson, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest(/*"",*/ContentJsonString); //Removing credentials but keeping for Future Uses -->"user/login"
	Request->OnProcessRequestComplete().BindUObject(this, &AMyHttpPostActor::OnResponseReceived);

	if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("Sending Request"));

	Send(Request);
}

/*Assigned function on successfull http call*/
void AMyHttpPostActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FString textError = Reader->GetErrorMessage();
	if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("Response Available"));
	if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("Any Error? %s"), *textError);


	saveMyArParams(Reader);
}

//----------------------------------------------------------
void  AMyHttpPostActor::saveMyArParams(TSharedRef<TJsonReader<>> Reader) {
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObjectParsed;

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObjectParsed))
	{
		//Get the value of the json object by field name
		//bool bhasData = JsonObjectParsed->HasField("Message");
		FString recievedString = JsonObjectParsed->GetStringField("Message");
		if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("bhasData TRUE and Message is %s"), *recievedString);

		if (JsonObjectParsed->HasField("get_ar_contents")) {
			TArray <TSharedPtr<FJsonValue>> get_ar_contentsJson = JsonObjectParsed->GetArrayField("get_ar_contents");
			int numStrutsAvailable = 0;

			for (int i = 0; i != get_ar_contentsJson.Num(); i++) {
								
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("get_ar_contents[%i]-->"), i);

				//Get SUBJson Object
				TSharedPtr<FJsonObject> temp = get_ar_contentsJson[i]->AsObject();

				//wine_image
				FString recievedString_wine_image = temp->GetStringField("wine_image");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString wine_image %s"), *recievedString_wine_image);
				myLastJsonRequestResult.wine_img = recievedString_wine_image;//Save
																			 //wine_name
				FString recievedString_wine_name = temp->GetStringField("wine_name");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString wine_name %s"), *recievedString_wine_name);
				myLastJsonRequestResult.wine_name = recievedString_wine_name;//Save

																			 //TODO RECEIVING NULL. ASK SAYALI
																			 //subcolor_id 

																			 //drinking_temp
				FString recievedString_drinking_temp = temp->GetStringField("drinking_temp");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString drinking_temp %s"), *recievedString_drinking_temp);
				myLastJsonRequestResult.drinking_temp = recievedString_drinking_temp;//Save

																					 //hint_id
				FString recievedString_hint_id = temp->GetStringField("hint");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString hint_id %s"), *recievedString_hint_id);
				myLastJsonRequestResult.hint_id = recievedString_hint_id;//Save

																		 //color_image
				FString recievedString_color_image = temp->GetStringField("color_img");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString color_name %s"), *recievedString_color_image);
				myLastJsonRequestResult.color_img = recievedString_color_image;//Save
																			   //color_name
				FString recievedString_color_name = temp->GetStringField("color_name");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString color_name %s"), *recievedString_color_name);
				myLastJsonRequestResult.color_name = recievedString_color_name;//Save

																			   //flavor_one_img
				FString recievedString_flavor_one_image = temp->GetStringField("flavor_one_img");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString flavor_one_img %s"), *recievedString_flavor_one_image);
				myLastJsonRequestResult.flavor_one_img = recievedString_flavor_one_image;//Save
																						 //flavor_one_name
				FString recievedString_flavor_one_name = temp->GetStringField("flavor_one_name");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString flavor_one_name %s"), *recievedString_flavor_one_name);
				myLastJsonRequestResult.flavor_one_name = recievedString_flavor_one_name;//Save

																						 //flavor_two_img
				FString recievedString_flavor_two_image = temp->GetStringField("flavor_two_img");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString flavor_two_img %s"), *recievedString_flavor_two_image);
				myLastJsonRequestResult.flavor_two_img = recievedString_flavor_two_image;//Save
																						 //flavor_one_name
				FString recievedString_flavor_two_name = temp->GetStringField("flavor_two_name");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString flavor_two_name %s"), *recievedString_flavor_two_name);
				myLastJsonRequestResult.flavor_two_name = recievedString_flavor_two_name;//Save

																						 //taste_img
				FString recievedString_taste_image = temp->GetStringField("taste");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString taste_img %s"), *recievedString_taste_image);
				myLastJsonRequestResult.taste_img = recievedString_taste_image;//Save
																			   //taste_name
				FString recievedString_taste_name = temp->GetStringField("taste_name");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString taste_name %s"), *recievedString_taste_name);
				myLastJsonRequestResult.taste_name = recievedString_taste_name;//Save

																			   //occasion_img
				FString recievedString_occasion_image = temp->GetStringField("occasion");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString ocasion_img %s"), *recievedString_occasion_image);
				myLastJsonRequestResult.occasion_img = recievedString_occasion_image;//Save
																					 //occasion_name
				FString recievedString_occasion_name = temp->GetStringField("occasion_name");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString ocasion_name %s"), *recievedString_occasion_name);
				myLastJsonRequestResult.occasion_name = recievedString_occasion_name;//Save

																					 //dish1_img
				FString recievedString_dish1_img = temp->GetStringField("dish_one");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString dish1_img %s"), *recievedString_dish1_img);
				myLastJsonRequestResult.dish1_img = recievedString_dish1_img;//Save
																			 //dish1_name
				FString recievedString_dish1_name = temp->GetStringField("dish1_name");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString dish1_name %s"), *recievedString_dish1_name);
				myLastJsonRequestResult.dish1_name = recievedString_dish1_name;//Save

																			   //dish2_img
				FString recievedString_dish2_img = temp->GetStringField("dish_two");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString dish2_img %s"), *recievedString_dish2_img);
				myLastJsonRequestResult.dish2_img = recievedString_dish2_img;//Save
																			 //dish2_name
				FString recievedString_dish2_name = temp->GetStringField("dish2_name");
				if(bDebugMode)UE_LOG(LogTemp, Warning, TEXT("recievedString dish2_name %s"), *recievedString_dish2_name);
				myLastJsonRequestResult.dish2_name = recievedString_dish2_name;//Save

				//Save the amount of data available
				saveStructInDataTable(numStrutsAvailable);
				numStrutsAvailable++;

				//TODO how this works?
				//Output it to the engine
				//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, recievedString); //FString::FromInt(recievedInt)
			}
		}
	}
}

//------------------------------------------------------
void AMyHttpPostActor::saveStructInDataTable(int numRow) {
	//Save Obtained Struct into DataTable
	//static const FString ContextString(TEXT("GENERAL"));

	//May be not necesary
	//GameObjectLookupTable.AddRow

	

}

/**************************************************************************************************************************/

template <typename StructType>
void AMyHttpPostActor::GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput) {
	FJsonObjectConverter::UStructToJsonObjectString(StructType::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
}

template <typename StructType>
void AMyHttpPostActor::GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput) {
	StructType StructData;
	FString JsonString = Response->GetContentAsString();
	FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(JsonString, &StructOutput, 0, 0);
}

/**************************************************************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Helpers

FString AMyHttpPostActor::PercentEncode(const FString& Source)
{
	FString OutText = Source;

	OutText = OutText.Replace(TEXT(" "), TEXT("%20"));
	OutText = OutText.Replace(TEXT("!"), TEXT("%21"));
	OutText = OutText.Replace(TEXT("\""), TEXT("%22"));
	OutText = OutText.Replace(TEXT("#"), TEXT("%23"));
	OutText = OutText.Replace(TEXT("$"), TEXT("%24"));
	OutText = OutText.Replace(TEXT("&"), TEXT("%26"));
	OutText = OutText.Replace(TEXT("'"), TEXT("%27"));
	OutText = OutText.Replace(TEXT("("), TEXT("%28"));
	OutText = OutText.Replace(TEXT(")"), TEXT("%29"));
	OutText = OutText.Replace(TEXT("*"), TEXT("%2A"));
	OutText = OutText.Replace(TEXT("+"), TEXT("%2B"));
	OutText = OutText.Replace(TEXT(","), TEXT("%2C"));
	OutText = OutText.Replace(TEXT("/"), TEXT("%2F"));
	OutText = OutText.Replace(TEXT(":"), TEXT("%3A"));
	OutText = OutText.Replace(TEXT(";"), TEXT("%3B"));
	OutText = OutText.Replace(TEXT("="), TEXT("%3D"));
	OutText = OutText.Replace(TEXT("?"), TEXT("%3F"));
	OutText = OutText.Replace(TEXT("@"), TEXT("%40"));
	OutText = OutText.Replace(TEXT("["), TEXT("%5B"));
	OutText = OutText.Replace(TEXT("]"), TEXT("%5D"));
	OutText = OutText.Replace(TEXT("{"), TEXT("%7B"));
	OutText = OutText.Replace(TEXT("}"), TEXT("%7D"));

	return OutText;
}
