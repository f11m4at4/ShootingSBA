// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPlayer.generated.h"

UCLASS()
class SHOOTING_API ACPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// box collision comp
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComp;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BodyMesh;
	// �̵��ӵ� �Ӽ�
	UPROPERTY(EditAnywhere, Category="Settings")
	float speed = 500;

	float h;
	float v;
	void Horizontal(float value);
	void Vertical(float value);

	// ����ڰ� �߻��ư�� ������ �Ѿ��� �߻��ϰ� �ʹ�.
	// �ʿ�Ӽ� : �Ѿ˰���
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<class ACBullet> bulletFactory;
	void Fire();

	/*UPROPERTY(EditDefaultsOnly, Category = "Settings")
	class USoundBase* bulletSound;*/

	UFUNCTION(BlueprintImplementableEvent)
	void PlayFireSound();
};
