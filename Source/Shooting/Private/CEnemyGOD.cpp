// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyGOD.h"
#include "CEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "CShootGameMode.h"

// Sets default values
ACEnemyGOD::ACEnemyGOD()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEnemyGOD::BeginPlay()
{
	Super::BeginPlay();
	
	FindSpawnPoints();

	//TArray<AActor*> allActors;
	//// spawnPoint 들 찾아오기
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	//// 이들중에서 spawnpoint 만 찾아서 가져오자
	//for (auto actor : allActors)
	//{
	//	// 이름이 spawnpoint 를 포함하고 있으면
	//	if (actor->GetName().Contains("SpawnPoint"))
	//	{
	//		// 가져오기
	//		spawnPoints.Add(actor);
	//	}
	//}

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACEnemyGOD::CreateEnemy, createTime, true);
}

// Called every frame
void ACEnemyGOD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	//CreateEnemy();
}

// 일정시간에 한번씩 적을 만들고 싶다.
void ACEnemyGOD::CreateEnemy()
{
	// 게임의 상태가 Ready, Start, Playing 일때만 이동가능
	auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());
	if (gm && gm->myState != EShootGameState::Playing)
	{
		return;
	}

	// spawnPoint가 없으면 처리하지 않도록
	if (spawnPoints.Num() < 1)
	{
		return;
	}
	
	// spawnpoints 중에 랜덤한 위치를 뽑아서 그위치에 생성하도로고 하자
	// 1. 랜덤한 스폰 인덱스 추출하기
	int spawnIndex = FMath::RandRange(0, spawnPoints.Num()-1);
	// 2. 스폰할 위치
	FVector loc = spawnPoints[spawnIndex]->GetActorLocation();
	// 3. 생성하자
	GetWorld()->SpawnActor<ACEnemy>(enemyFactory, loc, FRotator::ZeroRotator);
	//// 일정시간에 한번씩 적을 만들고 싶다.
	//// 1. 시간이 흘렀으니까
	//currentTime += GetWorld()->DeltaTimeSeconds;
	//// 2. 생성 시간이 됐으니까
	//// -> 만약 경과시간이 생성시간을 초과했다면
	//if (currentTime > createTime)
	//{
	//	// 3. 적(Actor)을 만들고 싶다.
	//	GetWorld()->SpawnActor<ACEnemy>(enemyFactory, GetActorLocation(), FRotator::ZeroRotator);
	//	// 4. 경과시간 초기화
	//	currentTime = 0;
	//}
}

void ACEnemyGOD::FindSpawnPoints_Implementation()
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, "Test Native Event");
}

