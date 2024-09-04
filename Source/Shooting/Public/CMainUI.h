// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMainUI.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API UCMainUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UButton* btn_GameStart;
	UPROPERTY(meta=(BindWidget))
	class UCanvasPanel* TitleCanvas;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* ReadyText;

	UFUNCTION()
	void OnGameStartBtnClicked();
};
