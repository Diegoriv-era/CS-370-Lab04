// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "DwarfCharacter.h"
#include "AssaultWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API AAssaultWeapon : public AWeapon
{
	GENERATED_BODY()
public:
    AAssaultWeapon();

    virtual void OnStartFire() override;
    virtual void OnStopFire() override;

    UPROPERTY(EditAnywhere, Category = "GunStats")
    float fireRate;
    
    UPROPERTY(EditAnywhere, Category = "GunStats")
    float weaponRange;
    
    UPROPERTY(EditDefaultsOnly)
    UParticleSystem* hitEffect;
    FTimerHandle timer;
    UPROPERTY(EditAnywhere, Category = "Damage")
    float gunDamage;
protected:
    void WeaponTrace();
	
};





