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

// �����ð��� �ѹ��� ���� ����� �ʹ�.
void ACEnemyGOD::CreateEnemy()
{
	// spawnpoints �߿� ������ ��ġ�� �̾Ƽ� ����ġ�� �����ϵ��ΰ� ����
	GetWorld()->SpawnActor<ACEnemy>(enemyFactory, GetActorLocation(), FRotator::ZeroRotator);
	//// �����ð��� �ѹ��� ���� ����� �ʹ�.
	//// 1. �ð��� �귶���ϱ�
	//currentTime += GetWorld()->DeltaTimeSeconds;
	//// 2. ���� �ð��� �����ϱ�
	//// -> ���� ����ð��� �����ð��� �ʰ��ߴٸ�
	//if (currentTime > createTime)
	//{
	//	// 3. ��(Actor)�� ����� �ʹ�.
	//	GetWorld()->SpawnActor<ACEnemy>(enemyFactory, GetActorLocation(), FRotator::ZeroRotator);
	//	// 4. ����ð� �ʱ�ȭ
	//	currentTime = 0;
	//}
}

