// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	EIR_Damaged UMETA(DisplayName = "Damaged"),
	EIR_Common UMETA(DisplayName = "Common"),
	EIR_Uncommon UMETA(DisplayName = "Uncommon"),
	EIR_Rare UMETA(DisplayName = "Rare"),
	EIR_Legendary UMETA(DisplayName = "Legendary"),

	EIR_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Pickup UMETA(DisplayName = "Pickup"),
	EIS_EquipInterping UMETA(DisplayName = "EquipInterping"),
	EIS_PickedUp UMETA(DisplayName = "PickedUp"),
	EIS_Equipped UMETA(DisplayName = "Equipped"),
	EIS_Falling UMETA(DisplayName = "Falling"),

	EIS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class UDEMYSHOOTER_API AItem : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AItem();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when overlapping AreaSphere
	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when end overlapping AreaSphere
	UFUNCTION()
		void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Sets the ActiveStars array of bool based on rarity
	void SetActiveStars();

	// Set properties of the Item's components based on State
	void SetItemProperties(EItemState State);

	// Called when ItemInterping is finished
	void FinishInterping();

	// Handles Item interpolation when in the EquipInterping State
	void ItemInterp(float DeltaTime);

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Skeletal mesh for the item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* ItemMesh;

	// Line trace collides with box to show HUD widgets
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* CollisionBox;

	// Popup widget for when the player looks at the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		class UWidgetComponent* PickupWidget;

	// Enables item tracing when overlapped
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* AreaSphere;

	// The name which appears on the pickup widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		FString ItemName;

	// Item count (ammo, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		int32 ItemCount;

	// Item rarity determines numbers of stars in pickup widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		EItemRarity ItemRarity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		TArray<bool> ActiveStars;

	// State of the item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		EItemState ItemState;

	// The curve asset to use for the item's Z location when interping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		class UCurveFloat* ItemZCurve;

	// Starting location when interping begins
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		FVector ItemInterpStartLocation;

	// Target interp location in front of the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		FVector CameraTargetLocation;

	// True when interping
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		bool bInterping;

	// Plays when we start interping
	FTimerHandle ItemInterpTimer;

	// Duration of the curve and the timer
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		float ZCurveTime;

	// Pointer to the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		class AShooterCharacter* Character;

	// X and Y for the Item while interping in the EquipInterping state
	float ItemInterpX;
	float ItemInterpY;

	// Initial Yaw Offset between the camera and the interping Item
	float InterpInitialYawOffset;

	// Curve used to scale the Item when interping
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		UCurveFloat* ItemScaleCurve;

	// Sound played when Item is picked up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		class USoundCue* PickupSound;

	// Sound played when Item is equipped
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
		class USoundCue* EquipSound;

public:

	FORCEINLINE UWidgetComponent* GetPickupWidget() const { return PickupWidget; }

	FORCEINLINE USphereComponent* GetAreaSphere() const { return AreaSphere; }

	FORCEINLINE UBoxComponent* GetCollisionBox() const { return CollisionBox; }

	FORCEINLINE EItemState GetItemState() const { return ItemState; }

	void SetItemState(EItemState State);

	FORCEINLINE USkeletalMeshComponent* GetItemMesh() { return ItemMesh; }

	FORCEINLINE USoundCue* GetPickupSound() const { return PickupSound; }

	FORCEINLINE USoundCue* GetEquipSound() const { return EquipSound; }

	// Called from the AShooter character class
	void StartItemCurve(AShooterCharacter* Char);


};
