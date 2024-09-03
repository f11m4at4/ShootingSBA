// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include "Components/BoxComponent.h"
#include "CPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;

	BoxComp->SetBoxExtent(FVector(50));
	BoxComp->SetCollisionProfileName(TEXT("Enemy"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxComp);

	// ¾?¼? ??·?
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// ¾?¼??? ?¤?? ·??? ??¸?
	if (TempMesh.Succeeded())
	{
		// -> ½º?×Æ½¸Þ½? ??´?
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}
	// Material ·?????±?
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (TempMat.Succeeded())
	{
		// -> Material ??´?
		BodyMesh->SetMaterial(0, TempMat.Object);
	}
	BodyMesh->SetCollisionProfileName(TEXT("NoCollision"));

	// ?æ?¹?ß??¶§ ³??? ?×°? ³ª?? ?×??.
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnComponentBeginOverlap);
}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// 타겟이 있어야한다.
	target = Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass()));

	Direction = FVector::DownVector;
	
	int percent = FMath::RandRange(1, 10);
	// 타겟이 존재하고 30% 확률 안에 들어오면
	if (target && percent <= 3)
	{
		// Target - Me
		Direction = target->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
	}
}

float zVelocity = 0;
// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P = P0 + vt
	
}

void ACEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 부딪힌 녀석이 적이면
	//if (OtherActor->GetName().Contains("Enemy"))
	//auto enemy = Cast<ACEnemy>(OtherActor);
	//if(enemy)
	//{
	//	// -> 아무리 처리하지 않는다.
	//	return;
	//}

	// 폭발효과발생
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expFactory, GetActorLocation(), FRotator::ZeroRotator);

	OtherActor->Destroy();
	Destroy();
}

void ACEnemy::Move()
{
	FVector P0 = GetActorLocation();
	FVector vt = Direction * speed * GetWorld()->DeltaTimeSeconds;
	FVector P = P0 + vt;
	SetActorLocation(P);
	FRotator rot = UKismetMathLibrary::MakeRotFromXZ(GetActorForwardVector(), Direction);
	//FRotator rot = UKismetMathLibrary::FindLookAtRotation(P, P + Direction);
	SetActorRotation(rot);
}
