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

	//Default Constructor
	FStructDataInfo() {}

	//Constructor with All Parameters 
	FStructDataInfo(FString _wine_img, FString _wine_name, FString _color_img, FString _color_name,
		FString _subcolor_id, FString _hint_id, FString _drinking_temp,
		FString _flavor_one_img, FString _flavor_one_name, FString _flavor_two_img, FString _flavor_two_name,
		FString _taste_img, FString _taste_name,
		FString _occasion_img, FString _occasion_name, 
		FString _dish1_img, FString _dish1_name, FString _dish2_img, FString _dish2_name) {
	
		wine_img = _wine_img;
		wine_name = _wine_name;
		color_img = _color_img;
		color_name = _color_name;

		subcolor_id = _subcolor_id;
		hint_id = _hint_id;
		drinking_temp = _drinking_temp;

		flavor_one_img = _flavor_one_img;
		flavor_one_name = _flavor_one_name;
		flavor_two_img = _flavor_two_img;
		flavor_two_name = _flavor_two_name;

		taste_img = _taste_img;
		taste_name = _taste_name;

		occasion_img = _occasion_img;
		occasion_name = _occasion_name;

		dish1_img = _dish1_img;
		dish1_name = _dish1_name;
		dish2_img = _dish2_img;
		dish2_name = _dish2_name;
	
	}
};