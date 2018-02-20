#include "StructDataInfo.generated.h"

USTRUCT(BlueprintType)
struct EASYBACCHUSAR_API FStructDataInfo {
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString wine_img;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString wine_name;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString color_img; //This might be Id
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString color_name; //not necesary its at general id info

	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString subcolor_id; //Receiving NULL
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString hint_id;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString drinking_temp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString flavor_one_img;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString flavor_one_name;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString flavor_two_img;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString flavor_two_name;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString taste_img;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString taste_name;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString occasion_img;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString occasion_name;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString dish1_img;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString dish1_name;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString dish2_img;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite) FString dish2_name;

	//StructDataInfo() {}
};