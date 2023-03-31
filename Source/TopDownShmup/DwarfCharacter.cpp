// Fill out your copyright notice in the Description page of Project Settings.


#include "DwarfCharacter.h"
#include "AIDwarfController.h"

ADwarfCharacter::ADwarfCharacter(){
    AIControllerClass = AAIDwarfController::StaticClass();
    dwarfHP = 20.0f;
    damage = 10.0f;
}


void ADwarfCharacter::StartAttack(){
    if(this){
        if(AttackAnim){
            attackDuration = PlayAnimMontage(AttackAnim);
            GetWorldTimerManager().SetTimer(timer,this,&ADwarfCharacter::damagePlayer,attackDuration,true);
        }
        
    }
}

void ADwarfCharacter::StopAttack(){
    StopAnimMontage(AttackAnim);
    GetWorldTimerManager().ClearTimer(timer);
}

float ADwarfCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
                                  AController* EventInstigator, AActor* DamageCauser)
    {
        float ActualDamage = Super::TakeDamage(Damage, DamageEvent,
                                               EventInstigator, DamageCauser);
    if (ActualDamage > 0.0f)
    {
        //TODO: Add a debug message on screen to know dwarf got hit
        //Reduce health points
        dwarfHP -= ActualDamage;
        if (dwarfHP <= 0.0f)
        {
            // We're dead
            SetCanBeDamaged(false); // Don't allow further damage
            // TODO: Process death
            // Stop attack animation,
            StopAttack();
            // UnPossess the AI controller,
            AController* myController = GetController();
            
            if(myController){
               
                myController->UnPossess();
                
                
            }

            if(DeathAnim){
            deathDuration = PlayAnimMontage(DeathAnim);
            
            
            // Remove the dwarf from the world
            GetWorldTimerManager().SetTimer(deathTimer,this,&ADwarfCharacter::death,deathDuration,false);
            //Destroy();
                
            }
        }
    }
    return ActualDamage;
}

void ADwarfCharacter::damagePlayer(){
    APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if(playerPawn){
        ATopDownShmupCharacter* player = Cast<ATopDownShmupCharacter>(playerPawn);
        
        if(player){
            player->TakeDamage(damage, FDamageEvent(), GetInstigatorController(), this);
            
        }
    }
}

void ADwarfCharacter::death(){
    GetWorldTimerManager().ClearTimer(deathTimer);
    APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if(playerPawn){
        ATopDownShmupCharacter* player = Cast<ATopDownShmupCharacter>(playerPawn);
        if(player){
            player->points += 100;
            
        }
        
    }
    
    
    Destroy();
    
}
