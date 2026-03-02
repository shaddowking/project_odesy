#include "SP_GiasTotem.h"
#include "../../SP_Player.h"
#include "../../Buffes/SP_GiasBlesing.h"
#include "../../Buffes/SP_BuffDataAsset.h"

#include "Components/SphereComponent.h"

AGiasTotem::AGiasTotem()
{
	AouraBorder = CreateDefaultSubobject<USphereComponent>("Aoutaborder");
	AouraBorder->SetupAttachment(Root);
	AouraBorder->OnComponentBeginOverlap.AddDynamic(this, &AGiasTotem::OnPlayerEnter);
	AouraBorder->OnComponentEndOverlap.AddDynamic(this, &AGiasTotem::OnPlayerExit);
}

void AGiasTotem::OnPlayerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASPCharacter* player = Cast<ASPCharacter>(OtherActor);

	if (player)
	{
		if (OnExitnewBuff)
		{
			player->RemoveBuff(OnExitnewBuff);

		}
		OnEnternewBuff = NewObject<UGiasBlesing>(OnEnterBuffToApply);
		playerList.Add(player);
		player->AddBuff(OnEnternewBuff, OnEnterBuffToApply);
	}
}

void AGiasTotem::OnPlayerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASPCharacter* player = Cast<ASPCharacter>(OtherActor);

	if (player)
	{
		if (playerList.Contains(player))
		{
			player->RemoveBuff(OnEnternewBuff);
			OnExitnewBuff = NewObject<UGiasBlesing>(OnExitBuffToApply);
			player->AddBuff(OnExitnewBuff, OnExitBuffToApply);
		}
	}

	
}

void AGiasTotem::Activate(FVector Location)
{
	SetActorLocation(Location);
	duration = Maxduration;
	SetActorHiddenInGame(false);
	BPActivate(Location);

	IsActive = true;
	AouraBorder->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AGiasTotem::DeActivate()
{
	Super::DeActivate();
	AouraBorder->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
