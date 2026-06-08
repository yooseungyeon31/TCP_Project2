// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FindSessionsCallbackProxy.h"
#include "Blueprint/UserWidget.h"

#include "SessionListWidget.generated.h"

class UWrapBox;
class UButton;
class USessionItemWidget;

/**
 * 
 */
UCLASS()
class TCP_PROJECT2_API USessionListWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable)
	void SetInfo();

	UFUNCTION(BlueprintCallable)
	void RefreshUI();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UWrapBox> SessionList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Refresh;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Btn_CreateSession;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Close;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<USessionItemWidget> SessionItemClass;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<USessionItemWidget>> Sessions;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBlueprintSessionResult> SessionInfos;
	
};
