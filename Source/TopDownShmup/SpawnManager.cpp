// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    difficultyIncrease = false;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
    GetWorldTimerManager().SetTimer(timer,this,&ASpawnManager::spawnCharacter,minSpawnTime,false);
 
	
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnManager::spawnCharacter(){
    if(spawnEnemies){
        UWorld* World = GetWorld();
        if(World){
            

            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            ATargetPoint* spawnPoint = targetPoints[FMath::RandRange(0,targetPoints.Num()-1)];
            ACharacter* newDwarf = World->SpawnActor<ACharacter>(spawnEnemies,spawnPoint->GetActorLocation(),GetActorRotation(),SpawnParams);
            if(newDwarf){
                newDwarf->SpawnDefaultController();
            }
            APawn* pawnPointer = UGameplayStatics::GetPlayerPawn(this, 0);
            if(pawnPointer){
                ATopDownShmupCharacter* player = Cast<ATopDownShmupCharacter>(pawnPointer);
                
                if(!player->isDead){
                    float randTime = FMath::RandRange(minSpawnTime,maxSpawnTime);
                    if(player->points >= 500){
                        if(!difficultyIncrease){
                            if(randTime > 2){
                                randTime -= 2;
                            }
                            difficultyIncrease = true;
                            
                        }
                    }
                GetWorldTimerManager().SetTimer(multipleTimer,this,&ASpawnManager::spawnCharacter,randTime,false);
            }
        }
            
        }
    }
}
