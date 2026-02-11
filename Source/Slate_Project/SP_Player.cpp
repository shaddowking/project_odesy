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

ASPCharacter::ASPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	HPComp = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HPComp->OnDamage.AddDynamic(this, &ASPCharacter::OnDamage);
	HPComp->OnDeath.AddDynamic(this, &ASPCharacter::OnDeath);
	SCcomponent = CreateDefaultSubobject<USubclassComponent>("SubClassComponent");
	Aimpoint = CreateDefaultSubobject<USceneComponent>("aimpoint");
	Aimpoint->SetupAttachment(RootComponent);
}

void ASPCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (SCcomponent)
	{
		SCcomponent->InitializeSubclasses(this);
	}
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerContext, 0);
		}
	}
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	hud = Cast<ASP_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	CreateProjectilePool();
	CreateWeapons();

}

void ASPCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(playerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleMovemnt);
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Started, this, &ASPCharacter::HandleSetRotationOff);
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Canceled, this, &ASPCharacter::HandleSetRotationOn);
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


	}
}

void ASPCharacter::HandleJump()
{

	if (bIsGrounded)
	{
		PlayerJump(JumpForce);
	}

	HPComp->TakeDamage(10);
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

	if (!bIsUsingAbility)
	{
		bIsAiming = true;

		SetIdleRotationOff();
		StartAimCam();
	}
	else
	{
		Cast<IAbilityInterface>(SCcomponent->activeSubclass->ActiveAbility)->OnAbilitySecendaryAttack();

	}
	


}

void ASPCharacter::HandleStopAim()
{
	if (!bIsUsingAbility)
	{
		if (bIsShooting == false)
		{
			bIsAiming = false;
			SetIdleRotationOn();
			StopAimCam();
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

void ASPCharacter::HandleShoot()
{
	if (!bIsUsingAbility && bIsFireReleas)
	{
		if (EquiptMeleWeapon)
		{
			if (EquiptMeleWeapon->bIsUsingWeapon == false)
			{
				EquiptMeleWeapon->UseWeapon(FVector::Zero(), FVector::Zero());
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

				if (!bIsAiming && bIsShooting == false)
				{
					bIsShooting = true;
					RotatePlayerForward(ViewForward, ViewOrigin);
				}
				else if (bIsAiming || bIsFullyTurnd)
				{
					Shoot(ViewForward, ViewOrigin);
				}
			}

			
			

		}
	}
	else if (bIsUsingAbility)
	{
		bIsFireReleas = false;
		Cast<IAbilityInterface>(SCcomponent->activeSubclass->ActiveAbility)->OnAbilityPrimaryAttack();
	}
	

	
	
	


}

void ASPCharacter::HandleShootRealese()
{
	if (bIsAiming && !bIsUsingAbility && bIsFireReleas)
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

	if (bIsFireReleas == false)
	{
		bIsFireReleas = true;
	}
}

void ASPCharacter::HandleRelode()
{
	
	if (EquiptGun->ExtraAmmo > 0 && !bIsUsingAbility)
	{
		GetWorldTimerManager().SetTimer(RelodeTimerHandle, this, &ASPCharacter::RelodeFinish, EquiptGun->RelodeTime, false);
	}
	


}

void ASPCharacter::HandleUltimateTrigger()
{

	if (bIsUltimateReady && !bIsUsingAbility && !bIsShooting)
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ultimate);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityPressed();
		}
	}

	
	
}

void ASPCharacter::HandleUltimateRelease()
{
	if (bIsUltimateReady && SCcomponent->IsUsingAbility(SCcomponent->activeSubclass->Ultimate))
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ultimate);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityReleas();
		}
	}
	
}

void ASPCharacter::HandlePrimaryAbilityTrigger()
{
	if (bIsPrimaryAbilityReady && !bIsUsingAbility && !bIsShooting)
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ability1);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityPressed();
		}
	}
	
}

void ASPCharacter::HandlePrimaryAbilityRelease()
{
	if (bIsPrimaryAbilityReady && SCcomponent->IsUsingAbility(SCcomponent->activeSubclass->Ability1))
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ability1);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityReleas();
		}
	}
	
}

void ASPCharacter::HandleElementalAbilityTrigger()
{
	if (bIsElementalAbilityReady && !bIsUsingAbility && !bIsShooting)
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ability2);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityPressed();
		}
	}
	

}

void ASPCharacter::HandleElementalAbilityRelease()
{
	if (bIsElementalAbilityReady && SCcomponent->IsUsingAbility(SCcomponent->activeSubclass->Ability2))
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->activeSubclass->Ability2);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityReleas();
		}
	}
	
}

void ASPCharacter::HandleWeaponSwitch(const FInputActionValue& value)
{
	if (!bIsUsingAbility)
	{
		const float Value = value.Get<float>();
		SwitchWeaponWithID(Value);
	}
	
}



AProjectile* ASPCharacter::GetNextAvalableProjectile()
{
	AProjectile* result = nullptr;
	for (AProjectile* projectile : ProjectilePool)
	{
		if (projectile->IsActive == false)
		{
			result = projectile;
			break;
		}
	}

	if (result == nullptr)
	{
		result = AddProjectileTooPool();
	}

	return result;
}

AProjectile* ASPCharacter::AddProjectileTooPool()
{
	AProjectile* createdprojectile = nullptr;

	createdprojectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, FVector::ZeroVector, GetActorRotation());
	ProjectilePool.Add(createdprojectile);
	createdprojectile->DeActivate();

	return createdprojectile;
}






	



void ASPCharacter::CreateProjectilePool()
{
	AProjectile* createdprojectile = nullptr;
	for (size_t i = 0; i < ProjectilePoolsice; i++)
	{

		 createdprojectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetActorLocation(), GetActorRotation());
		 ProjectilePool.Add(createdprojectile);
		 createdprojectile->DeActivate();

	}

}

void ASPCharacter::OnDeath()
{
}

void ASPCharacter::OnDamage()
{
	float HPPercent = HPComp->CurrentHealth / HPComp->MaxHealth;
	hud->PlayerHudWidget->UpdateHPPercent(HPPercent);
}

void ASPCharacter::RemoveBuff(UBuffBase* buff)
{
	if (PlayerBuffs.Contains(buff))
	{
		
		PlayerBuffs.Remove(buff);
		buff->OnBuffDepleted();
		buff = nullptr;
	}
}

void ASPCharacter::AddBuff(UBuffBase* buff, UBuffDataAsset* dataasset)
{
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
		PlayerBuffs.Add(buff);
		buff->InitializeBuff(dataasset->HasDuration, dataasset->Duration,dataasset->BuffBrush,dataasset->buffUITemplate,this,dataasset->Name);
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
	FHitResult AimHit2;

	FVector ViewOrigin;
	FRotator ViewRotation;

	FVector Result;



	GetController()->GetPlayerViewPoint(ViewOrigin, ViewRotation);

	FVector ViewForward = ViewRotation.Quaternion().GetForwardVector();

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(AimHit, ViewOrigin, ViewOrigin + ViewForward * Range, ECollisionChannel::ECC_Visibility, QueryParams);

	FVector AimPoint = AimHit.bBlockingHit ? AimHit.Location : AimHit.TraceEnd;

	if (AimHit.bBlockingHit == false)
	{
		GetWorld()->LineTraceSingleByChannel(AimHit2, AimHit.TraceEnd, FVector::DownVector * Range, ECollisionChannel::ECC_Visibility, QueryParams);
		Result = AimHit2.bBlockingHit ? AimHit2.Location : AimHit2.TraceEnd;
	}
	else
	{
		Result = AimHit.Location;
	}

	return Result;
}

void ASPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GroundCheck();

	for (UBuffBase* buff : PlayerBuffs) 
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

	for (UBuffBase* buff : buffsToRemove) 
	{
		RemoveBuff(buff);
	}
	buffsToRemove.Empty();

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
	float test = HandleMoveSpeedCalculation();
	GetCharacterMovement()->MaxWalkSpeed = currentMoveSpeed + test;
}

float ASPCharacter::HandleMoveSpeedCalculation()
{
	float value = 0;

	for(UBuffBase* buff : PlayerBuffs)
	{
		value += buff->BuffMoveSpeedCalculation(this);
	}

	return value;
}



void ASPCharacter::SwitchWeaponWithID(float ID)
{
	int NewID = ID;

	if (NewID > CreatedWeaponList.Num()-1)
	{
		NewID = CreatedWeaponList.Num() - 1;
	}
	if (NewID < 0)
	{
		NewID = 0;
	}
	newWeapon = CreatedWeaponList[NewID];

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
		curentweapon = EquiptGun->OwningGun;
		hud->PlayerHudWidget->UpdateAmmoText(EquiptGun->CurrentAmmo, EquiptGun->ExtraAmmo);
	}
	else if (EquiptMeleWeapon)
	{
		
		EquiptMeleWeapon->Owner = this;
		EquiptMeleWeapon->ActivateWeapon();
		curentweapon = EquiptMeleWeapon->OwningWeapon;
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
	CreatedWeaponList[0]->DeactivateWeapon();
	CreatedWeaponList[1]->DeactivateWeapon();

	SwitchWeaponWithID(0);
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






