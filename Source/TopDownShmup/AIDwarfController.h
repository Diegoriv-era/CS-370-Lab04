// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEnemyController.h"
#include "DwarfCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownShmupPlayerController.h"
#include "TopDownShmupCharacter.h"
#include "AIDwarfController.generated.h"



enum class EDwarfState : short
{
    EStart, EChasing, EAttacking, EDead, EUnknown
};

UCLASS()

class TOPDOWNSHMUP_API AAIDwarfController : public AAIEnemyController
{
    GENERATED_BODY()

public:

    ADwarfCharacter* myDwarf;

    EDwarfState dwarfState;
    APawn* pawnPointer;


    EDwarfState getState() { return dwarfState; }
    void setState(EDwarfState state);
    void HandleCurrentState(EDwarfState state);

    UPROPERTY(EditAnywhere, Category = attackRange)
        float attackRange = 150.0f;
    ATopDownShmupCharacter* player;

protected:

    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void OnUnPossess() override;



};
