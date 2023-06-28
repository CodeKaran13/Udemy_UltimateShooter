// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "AmmoType.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_SubmachineGun UMETA(DisplayName = "SubmachineGun"),
	EWT_AssaultRifle UMETA(DisplayName = "AssaultRifle"),

	EWT_MAX UMETA(DisplayName = "DefaultMAX")
};

/**
 *
 */
UCLASS()
class UDEMYSHOOTER_API AWeapon : public AItem
{
	GENERATED_BODY()
public:

	AWeapon();

	virtual void Tick(float DeltaTime) override;

protected:

	void StopFalling();

private:

	FTimerHandle ThrowWeaponTimer;

	float ThrowWeaponTime;

	bool bFalling;

	// Ammo count for this Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
		int32 Ammo;

	// Maximum Ammo Weapon can hold
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
		int32 MagazineCapacity;

	// The type of Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
		EWeaponType WeaponType;

	// The type of ammo for this Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
		EAmmoType AmmoType;

	// FName for the Reload Montage Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
		FName ReloadMontageSection;

public:

	// Adds an impulse to the Weapon
	void ThrowWeapon();

	FORCEINLINE int32 GetAmmo() const { return Ammo; }

	// Called from Character class when firing Weapon
	void DecrementAmmo();

	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }

	FORCEINLINE EAmmoType GetAmmoType() const { return AmmoType; }

	FORCEINLINE FName GetReloadMontageSection() const { return ReloadMontageSection; }

	FORCEINLINE int32 GetMagazineCapacity() const { return MagazineCapacity; }

	void ReloadAmmo(int32 Amount);
};
