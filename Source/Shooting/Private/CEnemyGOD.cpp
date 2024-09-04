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
	//// spawnPoint �� ã�ƿ���
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	//// �̵��߿��� spawnpoint �� ã�Ƽ� ��������
	//for (auto actor : allActors)
	//{
	//	// �̸��� spawnpoint �� �����ϰ� ������
	//	if (actor->GetName().Contains("SpawnPoint"))
	//	{
	//		// ��������
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

// �����ð��� �ѹ��� ���� ����� �ʹ�.
void ACEnemyGOD::CreateEnemy()
{
	// ������ ���°� Ready, Start, Playing �϶��� �̵�����
	auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());
	if (gm && gm->myState != EShootGameState::Playing)
	{
		return;
	}

	// spawnPoint�� ������ ó������ �ʵ���
	if (spawnPoints.Num() < 1)
	{
		return;
	}
	
	// spawnpoints �߿� ������ ��ġ�� �̾Ƽ� ����ġ�� �����ϵ��ΰ� ����
	// 1. ������ ���� �ε��� �����ϱ�
	int spawnIndex = FMath::RandRange(0, spawnPoints.Num()-1);
	// 2. ������ ��ġ
	FVector loc = spawnPoints[spawnIndex]->GetActorLocation();
	// 3. ��������
	GetWorld()->SpawnActor<ACEnemy>(enemyFactory, loc, FRotator::ZeroRotator);
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

void ACEnemyGOD::FindSpawnPoints_Implementation()
{
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red, "Test Native Event");
}

