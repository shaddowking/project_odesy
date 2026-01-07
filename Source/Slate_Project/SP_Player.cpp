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


ASPCharacter::ASPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	HPComp = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HPComp->OnDamage.AddDynamic(this, &ASPCharacter::OnDamage);
	HPComp->OnDeath.AddDynamic(this, &ASPCharacter::OnDeath);
	SCcomponent = CreateDefaultSubobject<USubclassComponent>("SubClassComponent");
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
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::None, this, &ASPCharacter::StopShoot);
		
		EnhancedInputComponent->BindAction(RelodeAction, ETriggerEvent::Triggered, this, &ASPCharacter::HandleRelode);

		EnhancedInputComponent->BindAction(UltimateAciton, ETriggerEvent::Started, this, &ASPCharacter::HandleUltimateTrigger);
		EnhancedInputComponent->BindAction(UltimateAciton, ETriggerEvent::Completed, this, &ASPCharacter::HandleUltimateRelease);

		EnhancedInputComponent->BindAction(PrimaryAbilityAciton, ETriggerEvent::Started, this, &ASPCharacter::HandlePrimaryAbilityTrigger);
		EnhancedInputComponent->BindAction(PrimaryAbilityAciton, ETriggerEvent::Completed, this, &ASPCharacter::HandlePrimaryAbilityRelease);

		EnhancedInputComponent->BindAction(ElementalAbilityAciton, ETriggerEvent::Started, this, &ASPCharacter::HandleElementalAbilityTrigger);
		EnhancedInputComponent->BindAction(ElementalAbilityAciton, ETriggerEvent::Completed, this, &ASPCharacter::HandleElementalAbilityRelease);
		



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
	GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;


}

void ASPCharacter::HandleStopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

void ASPCharacter::HandleStartAim()
{

	bIsAiming = true;

	SetIdleRotationOff();
	StartAimCam();


}

void ASPCharacter::HandleStopAim()
{
	bIsAiming = false;
	SetIdleRotationOn();
	StopAimCam();

}

void ASPCharacter::HandleShoot()
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

void ASPCharacter::HandleRelode()
{
	
	if (EquiptGun->ExtraAmmo > 0)
	{
		GetWorldTimerManager().SetTimer(RelodeTimerHandle, this, &ASPCharacter::RelodeFinish, EquiptGun->RelodeTime, false);
	}
	


}

void ASPCharacter::HandleUltimateTrigger()
{

	if (bIsUltimateReady)
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->StormsEya->Ultimate);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityPressed();
		}
	}

	
	
}

void ASPCharacter::HandleUltimateRelease()
{
	if (bIsUltimateReady)
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->StormsEya->Ultimate);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityReleas();
		}
	}
	
}

void ASPCharacter::HandlePrimaryAbilityTrigger()
{
	if (bIsPrimaryAbilityReady)
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->StormsEya->Ability1);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityPressed();
		}
	}
	
}

void ASPCharacter::HandlePrimaryAbilityRelease()
{
	if (bIsPrimaryAbilityReady)
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->StormsEya->Ability1);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityReleas();
		}
	}
	
}

void ASPCharacter::HandleElementalAbilityTrigger()
{
	if (bIsElementalAbilityReady)
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->StormsEya->Ability2);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityPressed();
		}
	}
	

}

void ASPCharacter::HandleElementalAbilityRelease()
{
	if (bIsElementalAbilityReady)
	{
		IAbilityInterface* AbilityInterface = Cast<IAbilityInterface>(SCcomponent->StormsEya->Ability2);
		if (AbilityInterface)
		{
			AbilityInterface->OnAbilityReleas();
		}
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

	bCanShoot = false;
	bIsShooting = true;
	EquiptGun->FireGun(ViewOrigin, ViewForward);

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