#pragma once

#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SP_Player.generated.h"


class UInputMappingContext;
class UInputAction;
class ASP_Gun;
class AProjectile;
class USP_GunComponent;
class UHealthComponent;
class ASP_HUD;
class USubclassComponent;



UCLASS()
class ASPCharacter : public ACharacter {
	
	GENERATED_BODY()
public:
	ASPCharacter();

protected:

	ASP_HUD* hud = nullptr;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* PlayerContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RelodeAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* OpenPauseMenuAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* UltimateAciton;

	void BeginPlay()override;

	void SetupPlayerInputComponent(UInputComponent* playerInputComponent) override;

	void HandleJump();
	void HandleMovemnt(const FInputActionValue& value);
	void HandleSetRotationOff(const FInputActionValue& value);
	void HandleSetRotationOn(const FInputActionValue& value);
	void HandleLook(const FInputActionValue& value);
	void HandleRun();
	void HandleStopRun();

	void HandleStartAim();
	void HandleStopAim();

	void HandleShoot();
	void HandleRelode();

	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void OnDamage();

	USubclassComponent* SCcomponent = nullptr;

public:

	FVector GetAimPoint(float Range);

	void Tick(float DeltaTime) override;
	void GroundCheck();

	FVector GetCameraForward();
	FVector GetCameraOrigen();

	//Camera
	UFUNCTION(BlueprintImplementableEvent)
	void ClampcameraRotation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* HPComp = nullptr;

	//-------------
	//movement 
	UPROPERTY(EditDefaultsOnly, Category = "Movment")
	float MaxRunSpeed = 1000.0;
	UPROPERTY(EditDefaultsOnly, Category = "Movment")
	float MaxWalkSpeed = 600.0;

	UPROPERTY(EditDefaultsOnly, Category = "Movment")
	float JumpForce = 500;

	bool bIsGrounded;

	void SetIdleRotationOff();

	void SetIdleRotationOn();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerJump(float Force);

	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	ASP_Gun* CurrentGun = nullptr;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USP_GunComponent* EquiptGun = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	bool bCanShoot = true;
	bool bIsShooting = false;
	bool bIsAiming = false;
	bool bIsReloding = false;

	FTimerHandle GunTimerHandle;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAmmoCounter(float CurentAmmo, float RelodeAmmo);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAmmoUI(float current, float Extra);

	

	UPROPERTY(BlueprintReadWrite)
	bool bIsFullyTurnd = false;


	bool bCanRelode = true;
	FTimerHandle RelodeTimerHandle;


	void ResetTimeBetwenShots();

	UFUNCTION(BlueprintImplementableEvent)
	void RotatePlayerForward(FVector viewForward, FVector ViewOrigin);

	UFUNCTION(BlueprintCallable)
	void Shoot(FVector ViewForward, FVector ViewOrigin);
	void StopShoot();

	UFUNCTION(BlueprintCallable)
	void RelodeFinish();

	UFUNCTION(BlueprintImplementableEvent)
	void StartAimCam();

	UFUNCTION(BlueprintImplementableEvent)
	void StopAimCam();

	UFUNCTION(BlueprintImplementableEvent)
	void StartRelode(float RelodeSpeed);
	
	
};