#include "CBullet.h"
#include "Components/BoxComponent.h"

// Sets default values
ACBullet::ACBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;

	BoxComp->SetBoxExtent(FVector(50));
	BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxComp->SetRelativeScale3D(FVector(1, 0.25f, 0.5f));


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
void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector P = GetActorLocation() + FVector::UpVector * speed * DeltaTime;
	SetActorLocation(P);
}

