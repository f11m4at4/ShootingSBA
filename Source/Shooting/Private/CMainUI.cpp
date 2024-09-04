// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainUI.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "CShootGameMode.h"

void UCMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	btn_GameStart->OnClicked.AddDynamic(this, &UCMainUI::OnGameStartBtnClicked);
}

void UCMainUI::OnGameStartBtnClicked()
{
	// ���� ���¸� Ready �� ��ȯ�ϰ� �ʹ�.
	// 1. ���Ӹ�尡 �־���Ѵ�.
	auto gm = Cast<ACShootGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	// 2. ���Ӹ���� ���¸� �ٲ��ش�.
	if (gm)
	{
		gm->myState = EShootGameState::Ready;
		ReadyText->SetVisibility(ESlateVisibility::Visible);
	}

	TitleCanvas->SetVisibility(ESlateVisibility::Hidden);

	// �Է¸�带 UI �� �������ֱ�
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
}
