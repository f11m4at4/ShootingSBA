// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemy.generated.h"

UCLASS()
class SHOOTING_API ACEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// box collision comp
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BodyMesh;
	// 捞悼加档 加己
	UPROPERTY(EditAnywhere, Category = "Settings")
	float speed = 500;

	//鞘夸加己: 鸥百
	UPROPERTY(EditAnywhere)
	class ACPlayer* target;

	FVector Direction;
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
