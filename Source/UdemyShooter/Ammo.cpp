// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"

AAmmo::AAmmo()
{
	PrimaryActorTick.bCanEverTick = true;

	// Construct the ammo mesh component and set it as the root
	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	SetRootComponent(AmmoMesh);

	CollisionBox->SetupAttachment(GetRootComponent());
	PickupWidget->SetupAttachment(GetRootComponent());
	AreaSphere->SetupAttachment(GetRootComponent());
}

void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmo::BeginPlay()
{
	Super::BeginPlay();
}

void AAmmo::SetItemProperties(EItemState State)
{
	Super::SetItemProperties(State);

	switch (State)
	{
		case EItemState::EIS_Pickup:
			// Set Mesh properties
			AmmoMesh->SetSimulatePhysics(false);
			AmmoMesh->SetEnableGravity(false);
			AmmoMesh->SetVisibility(true);
			AmmoMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		case EItemState::EIS_EquipInterping:
			PickupWidget->SetVisibility(false);
			// Set Mesh properties
			AmmoMesh->SetSimulatePhysics(false);
			AmmoMesh->SetEnableGravity(false);
			AmmoMesh->SetVisibility(true);
			AmmoMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		case EItemState::EIS_PickedUp:
			break;
		case EItemState::EIS_Equipped:
			PickupWidget->SetVisibility(false);
			// Set Mesh properties
			AmmoMesh->SetSimulatePhysics(false);
			AmmoMesh->SetEnableGravity(false);
			AmmoMesh->SetVisibility(true);
			AmmoMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AmmoMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
		case EItemState::EIS_Falling:
			// Set Mesh properties
			AmmoMesh->SetSimulatePhysics(true);
			AmmoMesh->SetEnableGravity(true);
			AmmoMesh->SetVisibility(true);
			AmmoMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AmmoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			AmmoMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
			break;
		case EItemState::EIS_MAX:
			break;
		default:
			break;
	}
}
