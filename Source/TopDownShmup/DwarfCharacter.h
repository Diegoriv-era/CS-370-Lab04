// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Animation/AnimMontage.h"
#include "TopDownShmupCharacter.h"
#include "DwarfCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API ADwarfCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
public:
    ADwarfCharacter();
    UPROPERTY(EditDefaultsOnly)
    UAnimMontage* AttackAnim;
    void StartAttack();
    void StopAttack();
    UPROPERTY(EditAnywhere, Category = "Health")
    float dwarfHP;
    UPROPERTY(EditAnywhere, Category = "Damage")
    float damage;

    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
                             AController* EventInstigator, AActor* DamageCauser) override;
    void damagePlayer();
    FTimerHandle timer;
    float attackDuration;
    
    UPROPERTY(EditDefaultsOnly)
    UAnimMontage* DeathAnim;
    FTimerHandle deathTimer;
    float deathDuration;
    void death();
};
