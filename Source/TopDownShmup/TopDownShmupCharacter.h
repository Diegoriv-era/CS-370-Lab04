// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "Animation/AnimMontage.h"
#include "TopDownShmupCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDownShmupCharacter : public ACharacter
{
    GENERATED_BODY()

    /** Top down camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* TopDownCameraComponent;

    /** Camera boom positioning the camera above the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;


public:
    ATopDownShmupCharacter();

    /** Returns TopDownCameraComponent subobject **/
    FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    
    UPROPERTY(EditAnywhere, Category = Weapon)
    TSubclassOf<AWeapon> WeaponClass;
    
    UPROPERTY(EditAnywhere, Category = Weapon)
    TSubclassOf<AWeapon> UpgradedWeaponClass;
    
    void OnStartFire();
    void OnStopFire();
    UPROPERTY(EditAnywhere, Category = "Health")
    float playerHP;
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
                             AController* EventInstigator, AActor* DamageCauser) override;
    bool isDead;
    bool playerDeath(){return isDead;}
    UPROPERTY(EditDefaultsOnly)
    UAnimMontage* DeathAnim;
    FTimerHandle deathTimer;
    float deathDuration;
    void death(){GetMesh()->Deactivate();}
    
    int32 points = 0;
    bool upgraded = false;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
private:
    AWeapon* MyWeapon;
};

