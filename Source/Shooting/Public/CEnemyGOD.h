#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemyGOD.generated.h"

UCLASS()
class SHOOTING_API ACEnemyGOD : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemyGOD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 필요속성 : 생성시간, 경과시간, 적공장
	UPROPERTY(EditAnywhere)
	float createTime = 2;
	float currentTime = 0;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACEnemy> enemyFactory;
	// 일정시간에 한번씩 적을 만들고 싶다.
	void CreateEnemy();

	// 적이 스폰될 위치기억 배열
	//UPROPERTY(EditInstanceOnly, meta=(MakeEditWidget = true))
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> spawnPoints;

	UFUNCTION(BlueprintNativeEvent)
	void FindSpawnPoints();
};
