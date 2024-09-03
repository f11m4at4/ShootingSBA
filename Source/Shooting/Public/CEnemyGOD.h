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
	// �ʿ�Ӽ� : �����ð�, ����ð�, ������
	UPROPERTY(EditAnywhere)
	float createTime = 2;
	float currentTime = 0;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACEnemy> enemyFactory;
	// �����ð��� �ѹ��� ���� ����� �ʹ�.
	void CreateEnemy();

	// ���� ������ ��ġ��� �迭
	//UPROPERTY(EditInstanceOnly, meta=(MakeEditWidget = true))
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> spawnPoints;

	UFUNCTION(BlueprintNativeEvent)
	void FindSpawnPoints();
};
