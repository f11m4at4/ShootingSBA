// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyGOD.h"
#include "CEnemy.h"

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
	// spawnpoints 중에 랜덤한 위치를 뽑아서 그위치에 생성하도로고 하자
	GetWorld()->SpawnActor<ACEnemy>(enemyFactory, GetActorLocation(), FRotator::ZeroRotator);
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

