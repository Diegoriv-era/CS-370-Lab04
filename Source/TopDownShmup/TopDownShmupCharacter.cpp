// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownShmupCharacter.h"
#include "TopDownShmup.h"
#include "TopDownShmupPlayerController.h"

ATopDownShmupCharacter::ATopDownShmupCharacter()
{
    // Set size for player capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate character to camera direction
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
    GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane = true;
    GetCharacterMovement()->bSnapToPlaneAtStart = true;

    // Create a camera boom...
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
    CameraBoom->TargetArmLength = 800.f;
    CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
    CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

    // Create a camera...
    TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
    playerHP = 100.0f;
    isDead = false;
}

void ATopDownShmupCharacter::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);
    if(GEngine){
        GEngine->AddOnScreenDebugMessage(2,1.0f,FColor::Green,FString::Printf(TEXT("PLAYER HP: %f"),playerHP));
    }
    if(GEngine){
        GEngine->AddOnScreenDebugMessage(1,1.0f,FColor::Purple,FString::Printf(TEXT("Points: %d"),points));
    }

    if(points >= 500){
        if (!upgraded) {
            // Set the weapon class to the upgraded weapon
            //WeaponClass = UpgradedWeaponClass;//ARocketLauncher::StaticClass();
            // Destroy the current weapon
            if (MyWeapon) {
                MyWeapon->OnStopFire();
                MyWeapon->Destroy();
            }
            // Spawn the upgraded weapon
            UWorld* World = GetWorld();
            if (World) {
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = this;
                SpawnParams.Instigator = GetInstigator();
                FRotator Rotation(0.0f, 0.0f, -90.0f);
                MyWeapon = World->SpawnActor<AWeapon>(UpgradedWeaponClass, FVector::ZeroVector, Rotation, SpawnParams);
                if (MyWeapon) {
                    MyWeapon->WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("WeaponPoint"));
                    MyWeapon->MyPawn = this;
                }
            }
            if(GEngine){
                GEngine->AddOnScreenDebugMessage(-1,2.5f,FColor::Blue,FString::Printf(TEXT("CONGRATS!! Weapon Upgraded")));
            }
            upgraded = true;
        }
    }

    
}

void ATopDownShmupCharacter::BeginPlay()
{
    // Call base class BeginPlay
    Super::BeginPlay();
    // Spawn the weapon, if one was specified
    if (WeaponClass)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            // Need to set rotation like this because otherwise gun points down
            // NOTE: This should probably be a blueprint parameter
            FRotator Rotation(0.0f, 0.0f, -90.0f);
            // Spawn the Weapon
            MyWeapon = World->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector,
                                                  Rotation, SpawnParams);
            if (MyWeapon)
            {
                // This is attached to "WeaponPoint" which is defined in the skeleton
                // NOTE: This should probably be a blueprint parameter
                MyWeapon->WeaponMesh->AttachToComponent(GetMesh(),
                                                        FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("WeaponPoint"));
                MyWeapon->MyPawn = this;
            }
            
        }
    }
}

void ATopDownShmupCharacter::OnStartFire(){
    if(MyWeapon)
    {
        MyWeapon->OnStartFire();
        
    }
}

void ATopDownShmupCharacter::OnStopFire(){
    if(MyWeapon)
    {
        MyWeapon->OnStopFire();
        
    }
}

float ATopDownShmupCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
                                         AController* EventInstigator, AActor* DamageCauser){
    float ActualDamage = Super::TakeDamage(Damage, DamageEvent,
                                           EventInstigator, DamageCauser);
if (ActualDamage > 0.0f)
{
    //TODO: Add a debug message on screen to know dwarf got hit
    //Reduce health points
    playerHP -= ActualDamage;
    if (playerHP <= 0.0f)
    {
        isDead = true;
        ATopDownShmupPlayerController* controller = Cast<ATopDownShmupPlayerController>(GetController());
        if(controller){
            controller->SetIgnoreLookInput(true);
            controller->SetIgnoreMoveInput(true);
        }
        OnStopFire();
        if(DeathAnim){
            deathDuration = PlayAnimMontage(DeathAnim);
            deathDuration -= 0.25f;
            GetWorldTimerManager().SetTimer(deathTimer,this,&ATopDownShmupCharacter::death,deathDuration,false);
        }


    }
}
return ActualDamage;
}
