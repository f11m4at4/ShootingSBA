// Fill out your copyright notice in the Description page of Project Settings.


#include "CShootGameMode.h"
#include "Blueprint/UserWidget.h"
#include "CMainUI.h"

ACShootGameMode::ACShootGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACShootGameMode::BeginPlay()
{
	Super::BeginPlay();

	mainUI = CreateWidget<UCMainUI>(GetWorld(), mainUIFactory);
	if (mainUI)
	{
		mainUI->AddToViewport();
	}

	// 입력모드를 UI 로 설정해주기
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void ACShootGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FString stateStr = UEnum::GetValueAsString(myState);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *stateStr);

	switch (myState)
	{
	case EShootGameState::Title:
		Title();
		break;
	case EShootGameState::Ready:
		Ready();
		break;
	case EShootGameState::Start:
		Start();
		break;
	case EShootGameState::Playing:
		Playing();
		break;
	case EShootGameState::Pause:
		Pause();
		break;
	case EShootGameState::Gameover:
		Gameover();
		break;
	}
}



void ACShootGameMode::Title()
{
}

// 일정시간 지나면 상태를 Start 로 바꾼다.
void ACShootGameMode::Ready()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > ReadyDelayTime)
	{
		currentTime = 0;
		myState = EShootGameState::Start;
	}
}

// 일정시간 지나면 상태를 Playing 로 바꾼다.
void ACShootGameMode::Start()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > StartDelayTime)
	{
		currentTime = 0;
		myState = EShootGameState::Playing;
	}
}

void ACShootGameMode::Playing()
{
}

void ACShootGameMode::Pause()
{
}

void ACShootGameMode::Gameover()
{
}
