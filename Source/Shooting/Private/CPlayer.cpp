// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "Components/BoxComponent.h"
#include "CBullet.h"
#include "CShootGameMode.h"

// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;

	BoxComp->SetBoxExtent(FVector(50));
	BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxComp);

	// 애셋 등록
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// 애셋이 정상 로드 되면
	if (TempMesh.Succeeded())
	{
		// -> 스테틱메시 할당
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}
	// Material 로드하기
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (TempMat.Succeeded())
	{
		// -> Material 할당
		BodyMesh->SetMaterial(0, TempMat.Object);
	}
	BodyMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 게임의 상태가 Ready, Start, Playing 일때만 이동가능
	auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());
	if (gm && !(gm->myState == EShootGameState::Ready ||
		gm->myState == EShootGameState::Start ||
		gm->myState == EShootGameState::Playing))
	{
		return;
	}

	// 사용자의 입력에따라 이동하고 싶다.
	// 1. 사용자의 입력을 받아야한다.
	// 2. 방향이 필요하다.
	FVector Direction(0, h, v);
	// 3. 해당방향으로 이동하고싶다.
	// 등속운동
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector vt = Direction * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 사용자 입력과 처리함수 묶어주자.
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::Vertical);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ACPlayer::Fire);
}

void ACPlayer::Horizontal(float value)
{
	h = value;
}

void ACPlayer::Vertical(float value)
{
	v = value;
}

void ACPlayer::Fire()
{
	// 게임의 상태가 Ready, Start, Playing 일때만 이동가능
	auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());
	if (gm && !(gm->myState == EShootGameState::Ready ||
		gm->myState == EShootGameState::Start ||
		gm->myState == EShootGameState::Playing))
	{
		return;
	}
	PlayFireSound();
	GetWorld()->SpawnActor<ACBullet>(bulletFactory, GetActorLocation(), FRotator::ZeroRotator);
}


