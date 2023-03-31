// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketLauncher.h"

ARocketLauncher::ARocketLauncher(){
    fireRate = .2f;
    weaponRange = 10000.0f;
    gunDamage = 10.0f;
}


void ARocketLauncher::OnStartFire(){
    Super::OnStartFire();
    //GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Blue,FString::Printf(TEXT("SHOOTING")));
    GetWorldTimerManager().SetTimer(timer,this,&ARocketLauncher::WeaponTrace,fireRate,true,0.0f);
    
}

void ARocketLauncher::OnStopFire(){
    Super::OnStopFire();
    //GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Blue,FString::Printf(TEXT("STOPPED SHOOTING")));
    GetWorldTimerManager().ClearTimer(timer);
}

void ARocketLauncher::WeaponTrace()
{
    static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
    static FName MuzzleSocket = FName(TEXT("MuzzleFlashSocket"));
    // Start from the muzzle's position
    FVector StartPos = WeaponMesh->GetSocketLocation(MuzzleSocket);
    // Get forward vector of MyPawn
    FVector Forward = MyPawn->GetActorForwardVector();
    // Calculate end position
    FVector EndPos = StartPos + (Forward * weaponRange);/*TODO: Figure out vector math based on the WeaponRange*/
    // Perform line trace to retrieve hit info
    FCollisionQueryParams TraceParams(WeaponFireTag, true, GetInstigator());
    // This fires the ray and checks against all objects w/ collision
    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos,
    FCollisionObjectQueryParams::AllObjects, TraceParams);
    // Did this hit anything?
    if (Hit.bBlockingHit)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),hitEffect,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());
        if (HitSound) {
            PlayWeaponSound(HitSound);
        }
    // TODO: Actually do something
        ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(Hit.GetActor());
        if (Dwarf){
            Dwarf->TakeDamage(gunDamage, FDamageEvent(), GetInstigatorController(), this);
            if(GEngine){
                GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Red,FString::Printf(TEXT("DWARF HP: %f"),Dwarf->dwarfHP));
            }
            
        }

    }
}
