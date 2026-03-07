#pragma once

#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "UI/SP_BuffUI.h"
#include "Inventory/SP_ItemStruct.h"
#include "Camera/CameraComponent.h"
#include "SP_Player.generated.h"


class UInputMappingContext;
class UInputAction;
class ASP_Gun;
class AProjectile;
class USP_GunComponent;
class UHealthComponent;
class ASP_HUD;
class USubclassComponent;
class UWeaponBaseCompnent;
class UMeleWeaponComponent;
class ASP_MeleWeapon;
class AWeaponBase;
class IAbilityInterface;
class UBuffBase;
class UBuffDataAsset;
class UBuffUI;
class UBuildSystemComponent;
class USP_Resorse;
class UInventoryComponent;
class UBoxComponent;
class UInteractionComponent;
class UCameraComponent;
class USpringArmComponent;




UENUM(BlueprintType)
enum class EPlayerWorldState : uint8
{
	Combat,
	base,
	buildMode
};





UCLASS()
class ASPCharacter : public ACharacter {
	
	GENERATED_BODY()
public:
	ASPCharacter();
	ASP_HUD* hud = nullptr;
protected:

	

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
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* UltimateAciton;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* PrimaryAbilityAciton;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ElementalAbilityAciton;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SwitchWeaponAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* OpenSubclassMenuAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* BaseTeleportAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* OpenBuildMode;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* InventoryAction;

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
	void HandleShootRealese();
	void HandleRelode();

	void HandleUltimateTrigger();
	void HandleUltimateRelease();

	void HandlePrimaryAbilityTrigger();
	void HandlePrimaryAbilityRelease();

	void HandleElementalAbilityTrigger();
	void HandleElementalAbilityRelease();

	void HandleWeaponSwitch(const FInputActionValue& value);

	void HandleOpenSubclassMenu();

	void HandleBaseTeleport();
	void HandleBaseTeleportRelease();

	void HandleToggleBuildMode();

	void StartBuildMode();
	void ExitBuildMode();

	void HandleInteraction();

	void HandleOpenInventory();



	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void OnDamage();



	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivate = "true"))
	float CamDefoultFOV = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivate = "true"))
	float AimFOV = 60.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivate = "true"))
	float FOVInterlerpSpeed = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivate = "true"))
	float CurrentFOV;



	void Tick(float DeltaTime) override;


private:

	float BaseTeleportcountdownCount = 0;




public:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	USpringArmComponent* CameraSpingArm = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* PlayerCam = nullptr;


	UFUNCTION(BlueprintImplementableEvent)
	void teleportToExplormap();

	//Interaction

	UPROPERTY(EditAnywhere)
	UBoxComponent* InteractionColider = nullptr;

	UFUNCTION()
	void OnInteractEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractExit(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//------------
	//Inventory
	UPROPERTY(EditAnywhere)
	UInventoryComponent* invertoryComponent = nullptr;

	//-----------------------
	//Build/Base
	UFUNCTION(BlueprintCallable)
	void ChageWorldState(EPlayerWorldState state);

	UPROPERTY(EditDefaultsOnly)
	UBuildSystemComponent* BuildSystemCompenent = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void TeleportToBase();

	UPROPERTY(EditDefaultsOnly)
	float MaxBaseTeleportCountdown = 2;

	//--------------------------

	UPROPERTY(EditDefaultsOnly)
	EPlayerWorldState playerworldState = EPlayerWorldState::Combat;

	
	

	// Buff-------

	bool Bhasbuff = false;

	UBuffUI* CreateBuffUI(TSubclassOf<UBuffUI> bufftemplate) 
	{
		return CreateWidget<UBuffUI>(GetWorld(), bufftemplate);
	}

	TArray<UBuffBase*> PlayerBuffs;
	TArray<UBuffBase*> buffsToRemove;

	void RemoveBuff(UBuffBase* buff);

	void AddBuff(UBuffBase* buff, UBuffDataAsset* dataasset);

	//------------
	

	//Ability system
	UPROPERTY(EditDefaultsOnly)
	USubclassComponent* SCcomponent = nullptr;

	bool bIsUltimateReady = true;
	bool bIsPrimaryAbilityReady = true;
	bool bIsElementalAbilityReady = true;

	//----------

	FVector GetAimPoint(float Range);
	FVector GetPlacablePoint(float Range);


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
	float MaxRunSpeed = 1200.0;
	UPROPERTY(EditDefaultsOnly, Category = "Movment")
	float MaxWalkSpeed = 600.0;

	float currentMoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Movment")
	float JumpForce = 500;

	bool bIsGrounded;

	void SetIdleRotationOff();

	void SetIdleRotationOn();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerJump(float Force);


	void UpdateMoveSpeed();

	float HandleMoveSpeedCalculation();

	// weapons----------

	int lastWeaponID = 0;

	void ReEquipLastUsedWeapon();

	void UnequipWeapon();

	UPROPERTY(EditAnywhere)
	USceneComponent* Aimpoint = nullptr;

	UPROPERTY(EditAnywhere)
	int ProjectilePoolsice = 200;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadOnly)
	TArray<AProjectile*> ProjectilePool;

	UFUNCTION()
	AProjectile* GetNextAvalableProjectile();

	AProjectile* AddProjectileTooPool();

	void CreateProjectilePool();

	UPROPERTY(BlueprintReadWrite)
	TArray<UWeaponBaseCompnent*> CreatedWeaponList;

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void EquipGun(ASP_Gun* NewGun);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SwitchWeapon(AWeaponBase*& Newweapon,AWeaponBase*& OldWeapon);

	UFUNCTION()
	void SwitchWeaponWithID(float ID);

	UFUNCTION(BlueprintCallable)
	void ResetGun() 
	{
		EquiptGun = nullptr;
		EquiptMeleWeapon = nullptr;
	};


	UFUNCTION()
	void CreateWeapons();

	UWeaponBaseCompnent* GetWeaponCompenent(AWeaponBase*& weapon);

	UFUNCTION(BlueprintImplementableEvent)
	void AnimateWeapon();

	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeaponBase> primaryWeaponTemplate;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeaponBase> SecendaryWeaponTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMeleWeaponComponent* EquiptMeleWeapon = nullptr;

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
	void StartRelode(float RelodeSpeed);

	UFUNCTION(BlueprintImplementableEvent)
	USceneComponent* GetGunpoint();
	
	UPROPERTY(BlueprintReadOnly)
	bool bIsUsingAbility = false;

private:

	UPROPERTY()
	UInteractionComponent* CurrentInteractedObject = nullptr;

	
	UWeaponBaseCompnent* newWeapon = nullptr;

	ASP_Gun* Gun = nullptr;
	ASP_MeleWeapon* melee = nullptr;
	AWeaponBase* curentweapon = nullptr;

	IAbilityInterface* ActiveAbility = nullptr;

	bool bIsFireReleased = true;;

	UPROPERTY()
	AProjectile* AvalableProjectile = nullptr;

	UPROPERTY()
	AProjectile* createdprojectile = nullptr;

	bool bHasTeleportedToBase = false;

};