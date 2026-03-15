#include "SP_Player.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SP_GunConponent.h"
#include "SP_HealthComponent.h"
#include "UI/SP_PlayerHud.h"
#include "UI/SP_HUD.h"
#include "Abilitys/SP_SubclassComponent.h"
#include "Abilitys/CreatedAbilitys/SP_StormWalker.h"
#include "Abilitys/AbilityInterface.h"
#include "SP_ProjectileClass.h"
#include "SP_MeleWeaponComponent.h"
#include "SP_MeleweaponBase.h"
#include "Math/UnrealMathUtility.h"
#include "SP_Gun.h"
#include "Abilitys/SP_AbilityBase.h"
#include "Buffes/SP_BuffeBase.h"
#include "Buffes/SP_BuffDataAsset.h"
#include "BuildSystem/SP_BuildSystemComponent.h"
#include "Inventory/SP_InventoryComponent.h"
#include "OD_InteractionSystemComponent.h"
#include "Components/BoxComponent.h"
#include "BuildSystem/OD_BuildingManager.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ASPCharacter::ASPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraSpingArm = CreateDefaultSubobject<USpringArmComponent>("PlayerSpringarm");
	CameraSpingArm->SetupAttachment(RootComponent);
	CameraSpingArm->TargetArmLength = 250.f;
	CameraSpingArm->bUsePawnControlRotation = true;
	CameraSpingArm->SocketOffset = FVector(0, 50, 70);

	PlayerCam = CreateDefaultSubobject<UCameraComponent>("PlayerCam");
	PlayerCam->SetupAttachment(CameraSpingArm, USpringArmComponent::SocketName);
	PlayerCam->bUsePawnControlRotation = false;


	HPComp = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HPComp->OnDamage.AddDynamic(this, &ASPCharacter::OnDamage);
	HPComp->OnDeath.AddDynamic(this, &ASPCharacter::OnDeath);
	HPComp->player = this;
	SCcomponent = CreateDefaultSubobject<USubclassComponent>("SubClassComponent");
	Aimpoint = CreateDefaultSubobject<USceneComponent>("aimpoint");
	Aimpoint->SetupAttachment(RootComponent);
	BuildSystemCompenent = CreateDefaultSubobject<UBuildSystemComponent>("buildComponent");
	BuildSystemCompenent->Player = this;
	invertoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
 	InteractionColider = CreateDefaultSubobject<UBoxComponent>("interactionColider");
	InteractionColider->SetupAttachment(RootComponent);
	InteractionColider->OnComponentBeginOverlap.AddDynamic(this, &ASPCharacter::OnInteractEnter);
	InteractionColider->OnComponentEndOverlap.AddDynamic(this, &ASPCharacter::OnInteractExit);
}

void ASPCharacter::BeginPlay()
{
	Super::BeginPlay();
	invertoryComponent->CreateInventoryUI();

	if (SCcomponent)
	{
		SCcomponent->InitializeSubclasses(this);
	}
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerContext, 0);
			Subsystem = nullptr;
		}
		PlayerController = nullptr;
		
	}
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	hud = Cast<ASP_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	hud->CreateSubclassMenu(this);
	CreateProjectilePool();
	CreateWeapons();
	if (BuildSystemCompenent)
	{
		BuildSystemCompenent->InitialiceBuildSystem();
	}

	if (PlayerCam)
	{
		CurrentFOV = CamDefoultFOV;
		PlayerCam->SetFieldOfView(CurrentFOV);
	}

}

void ASPCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(playerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleMovemnt);
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Started, this, &ASPCharacter::HandleSetRotationOff);
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Completed, this, &ASPCharacter::HandleSetRotationOn);


		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleLook);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleJump);

		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleRun);
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::None, this, &ASPCharacter::HandleStopRun);

		
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleStartAim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ASPCharacter::HandleStopAim);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleShoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &ASPCharacter::HandleShootRealese);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::None, this, &ASPCharacter::StopShoot);
		
		EnhancedInputComponent->BindAction(RelodeAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleRelode);

		EnhancedInputComponent->BindAction(UltimateAciton, ETriggerEvent::Started, this, &ASPCharacter::HandleUltimateTrigger);
		EnhancedInputComponent->BindAction(UltimateAciton, ETriggerEvent::Completed, this, &ASPCharacter::HandleUltimateRelease);

		EnhancedInputComponent->BindAction(PrimaryAbilityAciton, ETriggerEvent::Started, this, &ASPCharacter::HandlePrimaryAbilityTrigger);
		EnhancedInputComponent->BindAction(PrimaryAbilityAciton, ETriggerEvent::Completed, this, &ASPCharacter::HandlePrimaryAbilityRelease);

		EnhancedInputComponent->BindAction(ElementalAbilityAciton, ETriggerEvent::Started, this, &ASPCharacter::HandleElementalAbilityTrigger);
		EnhancedInputComponent->BindAction(ElementalAbilityAciton, ETriggerEvent::Completed, this, &ASPCharacter::HandleElementalAbilityRelease);
		
		EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleWeaponSwitch);

		EnhancedInputComponent->BindAction(OpenSubclassMenuAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleOpenSubclassMenu);

		EnhancedInputComponent->BindAction(BaseTeleportAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleBaseTeleport);
		EnhancedInputComponent->BindAction(BaseTeleportAction, ETriggerEvent::Completed, this, &ASPCharacter::HandleBaseTeleportRelease);

		EnhancedInputComponent->BindAction(OpenBuildMode, ETriggerEvent::Started, this, &ASPCharacter::HandleToggleBuildMode);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ASPCharacter::HandleInteraction);

		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ASPCharacter::HandleOpenInventory);


	}
}

void ASPCharacter::HandleJump()
{

	if (bIsGrounded)
	{
		PlayerJump(JumpForce);
	}

}

void ASPCharacter::HandleMovemnt(const FInputActionValue& value)
{
	const FVector2d MovementVector = value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);

}

void ASPCharacter::HandleSetRotationOff(const FInputActionValue& value)
{
	SetIdleRotationOff();
}

void ASPCharacter::HandleSetRotationOn(const FInputActionValue& value)
{
	SetIdleRotationOn();
}

void ASPCharacter::HandleLook(const FInputActionValue& value)
{
	const FVector2d LookVector = value.Get<FVector2D>();
	AddControllerPitchInput(LookVector.Y);
	AddControllerYawInput(LookVector.X);

	ClampcameraRotation();
}

void ASPCharacter::HandleRun()
{
	currentMoveSpeed = MaxRunSpeed;
	GetCharacterMovement()->MaxWalkSpeed = currentMoveSpeed + HandleMoveSpeedCalculation();


}

void ASPCharacter::HandleStopRun()
{
	currentMoveSpeed = MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = currentMoveSpeed + HandleMoveSpeedCalculation();
}

void ASPCharacter::HandleStartAim()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (!bIsUsingAbility)
		{
			bIsAiming = true;

			SetIdleRotationOff();
		}
		else
		{
			if (SCcomponent->activeSubclass->ActiveAbility)
			{
				Cast<IAbilityInterface>(SCcomponent->activeSubclass->ActiveAbility)->OnAbilitySecendaryAttack();
			}
			else
			{
				bIsUsingAbility = false;
				bIsAiming = true;

				SetIdleRotationOff();
			}

		}

	}
	


}

void ASPCharacter::HandleStopAim()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (!bIsUsingAbility)
		{
			if (bIsShooting == false)
			{
				bIsAiming = false;
				SetIdleRotationOn();
			}
		}
		else
		{
			if (SCcomponent->activeSubclass->ActiveAbility)
			{
				Cast<IAbilityInterface>(SCcomponent->activeSubclass->ActiveAbility)->OnAbilitySecendaryAttackRealese();
			}

		}
	}
	
	
	

}

void ASPCharacter::HandleShoot()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (!bIsUsingAbility && bIsFireReleased)
		{
			if (EquiptMeleWeapon)
			{
				if (EquiptMeleWeapon->bIsUsingWeapon == false)
				{
					EquiptMeleWeapon->UseWeapon();
					EquiptMeleWeapon->bIsUsingWeapon = true;
				}
			}

			if (EquiptGun)
			{
				if (EquiptGun->CurrentAmmo <= 0 && EquiptGun->ExtraAmmo <= 0)
				{
					return;
				}

				if (EquiptGun->CurrentAmmo <= 0 && bIsReloding == false)
				{
					HandleRelode();
				}

				if (bCanShoot && bIsReloding == false && EquiptGun->CurrentAmmo > 0 && bIsAiming)
				{

					FVector ViewOrigin;
					FRotator ViewRotation;


					GetController()->GetPlayerViewPoint(ViewOrigin, ViewRotation);

					FVector ViewForward = ViewRotation.Quaternion().GetForwardVector();

					/*
					if (!bIsAiming && bIsShooting == false)
					{
						bIsShooting = true;
						RotatePlayerForward(ViewForward, ViewOrigin);
					}
					*/
					if (bIsAiming || bIsFullyTurnd)
					{
						Shoot(ViewForward, ViewOrigin);
					}
				}




			}
		}
		else if (bIsUsingAbility)
		{
			bIsFireReleased = false;
			Cast<IAbilityInterface>(SCcomponent->activeSubclass->ActiveAbility)->OnAbilityPrimaryAttack();
		}
	}
	else if (playerworldState == EPlayerWorldState::buildMode)
	{
		if (BuildSystemCompenent -> bCanBuild)
		{
			BuildSystemCompenent->PlaceBuilding();
		}
	}
}

void ASPCharacter::HandleShootRealese()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (bIsAiming && !bIsUsingAbility && bIsFireReleased)
		{
			EquiptGun->RealeseWeapon();

		}
		else
		{
			if (SCcomponent->activeSubclass->ActiveAbility)
			{
				Cast<IAbilityInterface>(SCcomponent->activeSubclass->ActiveAbility)->OnAbilityPrimaryAttackRelease();
			}

		}

		if (bIsFireReleased == false)
		{
			bIsFireReleased = true;
		}
	}
	else if (playerworldState == EPlayerWorldState::buildMode)
	{
		if (BuildSystemCompenent->bCanBuild == false)
		{
			BuildSystemCompenent->bCanBuild = true;
		}
	}
	
}

void ASPCharacter::HandleRelode()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (EquiptGun->ExtraAmmo > 0 && !bIsUsingAbility)
		{
			GetWorldTimerManager().SetTimer(RelodeTimerHandle, this, &ASPCharacter::RelodeFinish, EquiptGun->RelodeTime, false);
		}
	}
	
	


}

void ASPCharacter::HandleUltimateTrigger()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (bIsUltimateReady && !bIsUsingAbility && !bIsShooting)
		{
			AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ultimate);
			if (AbilityInterface)
			{
				AbilityInterface->OnAbilityPressed();
				
			}

		}
	}
	

	
	
}

void ASPCharacter::HandleUltimateRelease()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (bIsUltimateReady && SCcomponent->IsUsingAbility(SCcomponent->activeSubclass->Ultimate))
		{
			AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ultimate);
			if (AbilityInterface)
			{
				AbilityInterface->OnAbilityReleas();
			}
		}
	}
	
	
}

void ASPCharacter::HandlePrimaryAbilityTrigger()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (bIsPrimaryAbilityReady && !bIsUsingAbility && !bIsShooting)
		{
			AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ability1);
			if (AbilityInterface)
			{
				AbilityInterface->OnAbilityPressed();
			}
		}
	}
	
	
}

void ASPCharacter::HandlePrimaryAbilityRelease()
{
	if (playerworldState == EPlayerWorldState::base)
	{
		teleportToExplormap();
	}
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (bIsPrimaryAbilityReady && SCcomponent->IsUsingAbility(SCcomponent->activeSubclass->Ability1))
		{
			AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ability1);
			if (AbilityInterface)
			{
				AbilityInterface->OnAbilityReleas();
			}
		}
	}
	
	
}

void ASPCharacter::HandleElementalAbilityTrigger()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (bIsElementalAbilityReady && !bIsUsingAbility && !bIsShooting)
		{
			AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ability2);
			if (AbilityInterface)
			{
				AbilityInterface->OnAbilityPressed();
			}
		}
	}
	
	

}

void ASPCharacter::HandleElementalAbilityRelease()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (bIsElementalAbilityReady && SCcomponent->IsUsingAbility(SCcomponent->activeSubclass->Ability2))
		{
			AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ability2);
			if (AbilityInterface)
			{
				AbilityInterface->OnAbilityReleas();
			}
		}
	}
	
	
}

void ASPCharacter::HandleWeaponSwitch(const FInputActionValue& value)
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		if (!bIsUsingAbility)
		{
			const float Value = value.Get<float>();
			SwitchWeaponWithID(Value);
		}
	}
	else if (playerworldState == EPlayerWorldState::buildMode)
	{
		BuildSystemCompenent->SwichBuilding(value.Get<float>());
	}
	
	
}

void ASPCharacter::HandleOpenSubclassMenu()
{
	if (playerworldState == EPlayerWorldState::Combat)
	{
		hud->ShowSubclassMenu();

	}
}

void ASPCharacter::HandleBaseTeleport()
{
	if (BaseTeleportcountdownCount < MaxBaseTeleportCountdown)
	{
		BaseTeleportcountdownCount += 0.01;
		hud->PlayerHudWidget->UpdateBaseTelebortSlider(BaseTeleportcountdownCount / MaxBaseTeleportCountdown);
		hud->PlayerHudWidget->UpdateBaseTeleportVisibility(true);
	}
	else if(!bHasTeleportedToBase)
	{
		bHasTeleportedToBase = true;

		TeleportToBase();
		hud->PlayerHudWidget->UpdateBaseTelebortSlider(0);
		hud->PlayerHudWidget->UpdateBaseTeleportVisibility(false);
	}
}

void ASPCharacter::HandleBaseTeleportRelease()
{
	bHasTeleportedToBase = false;
	BaseTeleportcountdownCount = 0;
	hud->PlayerHudWidget->UpdateBaseTelebortSlider(0);
	hud->PlayerHudWidget->UpdateBaseTeleportVisibility(false);
}

void ASPCharacter::HandleToggleBuildMode()
{
	if (playerworldState == EPlayerWorldState::base)
	{
		StartBuildMode();
	}
	else if (playerworldState == EPlayerWorldState::buildMode)
	{
		ExitBuildMode();
	}
}

void ASPCharacter::StartBuildMode()
{
	ChageWorldState(EPlayerWorldState::buildMode);
	BuildSystemCompenent->ActivateBuildMode();
}

void ASPCharacter::ExitBuildMode()
{
	ChageWorldState(EPlayerWorldState::base);
	BuildSystemCompenent->DeActivateBuildMode();
}

void ASPCharacter::HandleInteraction()
{
	if (CurrentInteractedObject)
	{
		CurrentInteractedObject->Interact();
	}
}

void ASPCharacter::HandleOpenInventory()
{
	invertoryComponent->OpenInventory();
}



AProjectile* ASPCharacter::GetNextAvalableProjectile()
{
	AvalableProjectile = nullptr;
	for (AProjectile* projectile : ProjectilePool)
	{
		if (projectile->IsActive == false)
		{
			AvalableProjectile = projectile;
			break;
		}
	}

	if (AvalableProjectile == nullptr)
	{
		AvalableProjectile = AddProjectileTooPool();
	}

	return AvalableProjectile;
}

AProjectile* ASPCharacter::AddProjectileTooPool()
{
	createdprojectile = nullptr;

	createdprojectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, FVector::ZeroVector, GetActorRotation());
	ProjectilePool.Add(createdprojectile);
	createdprojectile->Owningplayer = this;
	createdprojectile->DeActivate();

	return createdprojectile;
}

void ASPCharacter::CreateProjectilePool()
{
	AProjectile* Currentprojectile = nullptr;
	for (size_t i = 0; i < ProjectilePoolsice; i++)
	{

		Currentprojectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), GetActorRotation());
		 ProjectilePool.Add(Currentprojectile);
		 Currentprojectile->Owningplayer = this;
		 Currentprojectile->DeActivate();

	}
	Currentprojectile = nullptr;

}

void ASPCharacter::OnDeath()
{
}

void ASPCharacter::OnDamage()
{
	float HPPercent = HPComp->CurrentHealth / HPComp->MaxHealth;
	hud->PlayerHudWidget->UpdateHPPercent(HPPercent);
}





void ASPCharacter::OnInteractEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CurrentInteractedObject = OtherActor->FindComponentByClass<UInteractionComponent>();
}

void ASPCharacter::OnInteractExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (CurrentInteractedObject)
	{
		CurrentInteractedObject = nullptr;
	}
}

void ASPCharacter::ChageWorldState(EPlayerWorldState state)
{
	switch (state)
	{
	case EPlayerWorldState::Combat:
		playerworldState = state;
		hud->PlayerHudWidget->SetVisibility(EVisibility::HitTestInvisible);
		BuildSystemCompenent->buildingManager->DeactivateAllBuildings();
		ReEquipLastUsedWeapon();
		break;
	case EPlayerWorldState::base:
		playerworldState = state;
		hud->PlayerHudWidget->SetVisibility(EVisibility::Collapsed);
		UnequipWeapon();
		BuildSystemCompenent->buildingManager->ActivateAllBuildings();
		break;
	case EPlayerWorldState::buildMode:
		playerworldState = state;
		break;
	default:
		break;
	}
}



void ASPCharacter::RemoveBuff(UBuffBase* buff)
{
	if (PlayerBuffs.Contains(buff))
	{
		PlayerBuffs.Remove(buff);
		buff->OnBuffDepleted();
	}
}

void ASPCharacter::AddBuff(UBuffBase* buff, UBuffDataAsset* dataasset)
{
	//Check if player has buff
	for (UBuffBase* currentBuff : PlayerBuffs)
	{
		if (currentBuff->GetClass() == buff->GetClass())
		{
			currentBuff->ResetDuration();
			Bhasbuff = true;
		}
	}
	if(Bhasbuff == false)
	{
		buff->InitializeBuff(this,dataasset);

		PlayerBuffs.Add(buff);
	}
	Bhasbuff = false;
}

FVector ASPCharacter::GetCameraForward()
{
	FVector ViewOrigin;
	FRotator ViewRotation;

	GetController()->GetPlayerViewPoint(ViewOrigin, ViewRotation);

	FVector ViewForward = ViewRotation.Quaternion().GetForwardVector();

	return ViewForward;
}

FVector ASPCharacter::GetCameraOrigen()
{
	FVector ViewOrigin;
	FRotator ViewRotation;

	GetController()->GetPlayerViewPoint(ViewOrigin, ViewRotation);
	return ViewOrigin;
}

void ASPCharacter::GroundCheck()
{

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + GetActorUpVector() * -100.f, ECollisionChannel::ECC_Visibility, Params);

	if (HitResult.bBlockingHit)
	{
		bIsGrounded = true;
	}
	else
	{
		bIsGrounded = false;
	}
}

void ASPCharacter::ResetTimeBetwenShots()
{
	bCanShoot = true;
}

void ASPCharacter::Shoot(FVector ViewForward, FVector ViewOrigin)
{
	GetCharacterMovement()->bOrientRotationToMovement = false;

	//bCanShoot = false;
	bIsShooting = true;
	EquiptGun->UseWeapon(ViewOrigin, ViewForward);

}

void ASPCharacter::StopShoot()
{
	if (bIsShooting)
	{
		bIsFullyTurnd = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		bIsShooting = false;
	}
}

FVector ASPCharacter::GetAimPoint(float Range)
{
	FHitResult AimHit;

	FVector ViewOrigin;
	FRotator ViewRotation;



	GetController()->GetPlayerViewPoint(ViewOrigin, ViewRotation);

	FVector ViewForward = ViewRotation.Quaternion().GetForwardVector();
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(AimHit, ViewOrigin, ViewOrigin + ViewForward * Range, ECollisionChannel::ECC_Visibility, QueryParams);

	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	return AimPoint;
}

FVector ASPCharacter::GetPlacablePoint(float Range)
{
	FHitResult AimHit;
	FVector Result;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FVector AimPoint = GetAimPoint(Range);

	if (AimHit.bBlockingHit == false)
	{
		GetWorld()->LineTraceSingleByChannel(AimHit, AimPoint, FVector::DownVector * Range, ECollisionChannel::ECC_Visibility, QueryParams);
		Result = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;
	}
	else
	{
		Result = AimPoint;
	}

	return Result;
}

void ASPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerCam)
	{
		return;
	}

	const float TargetFOV = bIsAiming ? AimFOV : CamDefoultFOV;
	CurrentFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, FOVInterlerpSpeed);
	PlayerCam->SetFieldOfView(CurrentFOV);

	GroundCheck();
	
	//Current iteration of Handeling duration for buffs and debuffs
	if (PlayerBuffs.Num() > 0)
	{
		for (UBuffBase* buff : PlayerBuffs)
		{
			if (buff->HasDuration)
			{
				if (buff->Duration > 0)
				{
					buff->Duration -= DeltaTime;
					buff->UI->UpdateTimerText(buff->Duration);

				}
				else if (buff->Duration <= 0)
				{
					buffsToRemove.Add(buff);
				}
			}

		}
		for (UBuffBase* buff : buffsToRemove)
		{
			RemoveBuff(buff);
		}
		buffsToRemove.Empty();
	}
	// "Tick" for the build system
	if (playerworldState == EPlayerWorldState::buildMode)
	{
		BuildSystemCompenent->BuildModeCycle();
	}
	

	
	
}

void ASPCharacter::RelodeFinish()
{
	
	float BulletsShot = EquiptGun->MaxAmmo - EquiptGun->CurrentAmmo;
	if (BulletsShot > EquiptGun->ExtraAmmo)
	{
		float bulletsToAdd = EquiptGun->ExtraAmmo;

		EquiptGun->CurrentAmmo += bulletsToAdd;

		EquiptGun->ExtraAmmo -= bulletsToAdd;
	}
	else
	{
		EquiptGun->CurrentAmmo = EquiptGun->MaxAmmo;
		EquiptGun->ExtraAmmo -= BulletsShot;
	}
	hud->PlayerHudWidget->UpdateAmmoText(EquiptGun->CurrentAmmo, EquiptGun->ExtraAmmo);
	

}


void ASPCharacter::SetIdleRotationOff()
{

	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void ASPCharacter::SetIdleRotationOn()
{

	GetCharacterMovement()->bOrientRotationToMovement = true;


}

void ASPCharacter::UpdateMoveSpeed()
{
	
	GetCharacterMovement()->MaxWalkSpeed = currentMoveSpeed + HandleMoveSpeedCalculation();
}

float ASPCharacter::HandleMoveSpeedCalculation()
{
	float Speed = 0;

	for(UBuffBase* buff : PlayerBuffs)
	{
		Speed += buff->BuffMoveSpeedCalculation(this);
	}

	return Speed;
}

void ASPCharacter::ReEquipLastUsedWeapon()
{
	newWeapon = CreatedWeaponList[lastWeaponID];
	ResetGun();
	EquiptGun = Cast<USP_GunComponent>(newWeapon);
	EquiptMeleWeapon = Cast<UMeleWeaponComponent>(newWeapon);
	if (EquiptGun)
	{

		EquiptGun->Owner = this;
		EquiptGun->ActivateWeapon();
		hud->PlayerHudWidget->UpdateAmmoText(EquiptGun->CurrentAmmo, EquiptGun->ExtraAmmo);
	}
	else if (EquiptMeleWeapon)
	{

		EquiptMeleWeapon->Owner = this;
		EquiptMeleWeapon->ActivateWeapon();
	}
}

void ASPCharacter::UnequipWeapon()
{
	if (EquiptGun)
	{
		EquiptGun->DeactivateWeapon();
	}
	if (EquiptMeleWeapon)
	{
		EquiptMeleWeapon->DeactivateWeapon();
	}
	ResetGun();
}

void ASPCharacter::SwitchWeaponWithID(float ID)
{
	int WeaponID = ID;

	if (WeaponID > CreatedWeaponList.Num()-1)
	{
		WeaponID = CreatedWeaponList.Num() - 1;
	}
	if (WeaponID < 0)
	{
		WeaponID = 0;
	}
	newWeapon = CreatedWeaponList[WeaponID];
	lastWeaponID = WeaponID;
	if (EquiptGun)
	{
		EquiptGun->DeactivateWeapon();
	}
	if (EquiptMeleWeapon)
	{
		EquiptMeleWeapon->DeactivateWeapon();
	}
	ResetGun();
	EquiptGun = Cast<USP_GunComponent>(newWeapon);
	EquiptMeleWeapon = Cast<UMeleWeaponComponent>(newWeapon);
	if (EquiptGun)
	{
		
		EquiptGun->Owner = this;
		EquiptGun->ActivateWeapon();
		hud->PlayerHudWidget->UpdateAmmoText(EquiptGun->CurrentAmmo, EquiptGun->ExtraAmmo);
	}
	else if (EquiptMeleWeapon)
	{
		
		EquiptMeleWeapon->Owner = this;
		EquiptMeleWeapon->ActivateWeapon();
	}
}


void ASPCharacter::CreateWeapons()
{
	AWeaponBase* CreatedWeapon = nullptr;
	CreatedWeapon = GetWorld()->SpawnActor<AWeaponBase>(primaryWeaponTemplate);
	CreatedWeapon->AttachToComponent(GetGunpoint(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CreatedWeaponList.Add(GetWeaponCompenent(CreatedWeapon));
	CreatedWeapon = GetWorld()->SpawnActor<AWeaponBase>(SecendaryWeaponTemplate);
	CreatedWeapon->AttachToComponent(GetGunpoint(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CreatedWeaponList.Add(GetWeaponCompenent(CreatedWeapon));
	for (UWeaponBaseCompnent* weapon : CreatedWeaponList)
	{
		weapon->DeactivateWeapon();
	}
	SwitchWeaponWithID(0);
	CreatedWeapon = nullptr;
}

UWeaponBaseCompnent* ASPCharacter::GetWeaponCompenent(AWeaponBase*& weapon)
{
	melee = Cast<ASP_MeleWeapon>(weapon);
	Gun = Cast<ASP_Gun>(weapon);
	if (Gun)
	{
		return Gun->GunComponent;
	}
	else if (melee)
	{
		return melee->WeaponComponent;
	}
	return nullptr;
}
