// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDwarfController.h"

void AAIDwarfController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    if(InPawn){
        myDwarf = Cast<ADwarfCharacter>(InPawn);
    }
}
void AAIDwarfController::BeginPlay()
{
    Super::BeginPlay();
    setState(EDwarfState::EStart);


    // Get the player pawn
    pawnPointer = UGameplayStatics::GetPlayerPawn(this, 0);
    player = Cast<ATopDownShmupCharacter>(pawnPointer);

    // Move towards the player
    if (pawnPointer != nullptr)
    {

    }
}



void AAIDwarfController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    Super::OnMoveCompleted(RequestID, Result);
//    if (GEngine) {
//        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("MOVE COMPLETED")));
//    }
    if(myDwarf == nullptr){
        return;
    }

    setState(EDwarfState::EAttacking);
    
}

void AAIDwarfController::HandleCurrentState(EDwarfState state) {
    switch (state) {
    
    case EDwarfState::EStart: {
        //start state??

    }
    break;

    case EDwarfState::EChasing: {
        //chase the player when game starts
        if(pawnPointer){
            if(myDwarf){
                MoveToActor(pawnPointer);
            }
        }
        if(myDwarf){
            myDwarf->StopAttack();
        }

    }
    break;

    case EDwarfState::EAttacking: {
        //hit the player when ogets close enough
        if(myDwarf){
            myDwarf->StartAttack();
        }

    }
    break;
    case EDwarfState::EDead: {
        
        //dwarf is killed?

    }

    break;

    //Unknown/Default State
    default:
    case EDwarfState::EUnknown: {
        //debug state
        

    }
    break;









    }
}

void AAIDwarfController::setState(EDwarfState state){
    if(myDwarf){
        dwarfState = state;
        HandleCurrentState(dwarfState);
    }
}




void AAIDwarfController::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);

    if(myDwarf){
        if (dwarfState == EDwarfState::EStart) {
            setState(EDwarfState::EChasing);
        }
        if(pawnPointer){
            float distance = myDwarf->GetDistanceTo(pawnPointer);
            if (distance > attackRange) {

                
                setState(EDwarfState::EChasing);
            }
            
            if(player->isDead){
                myDwarf->StopAttack();
            }
        }
        
    }

    
}


void AAIDwarfController::OnUnPossess(){
    Super::OnUnPossess();
    SetActorTickEnabled(false);
}
