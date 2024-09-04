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

	// �ּ� ���
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	// �ּ��� ���� �ε� �Ǹ�
	if (TempMesh.Succeeded())
	{
		// -> ����ƽ�޽� �Ҵ�
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}
	// Material �ε��ϱ�
	ConstructorHelpers::FObjectFinder<UMaterial> TempMat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (TempMat.Succeeded())
	{
		// -> Material �Ҵ�
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

	// ������ ���°� Ready, Start, Playing �϶��� �̵�����
	auto gm = Cast<ACShootGameMode>(GetWorld()->GetAuthGameMode());
	if (gm && !(gm->myState == EShootGameState::Ready ||
		gm->myState == EShootGameState::Start ||
		gm->myState == EShootGameState::Playing))
	{
		return;
	}

	// ������� �Է¿����� �̵��ϰ� �ʹ�.
	// 1. ������� �Է��� �޾ƾ��Ѵ�.
	// 2. ������ �ʿ��ϴ�.
	FVector Direction(0, h, v);
	// 3. �ش�������� �̵��ϰ�ʹ�.
	// ��ӿ
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

	// ����� �Է°� ó���Լ� ��������.
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
	// ������ ���°� Ready, Start, Playing �϶��� �̵�����
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


