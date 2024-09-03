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

