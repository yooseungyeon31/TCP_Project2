// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatWidgetBase.generated.h"

class UButton;
class UEditableTextBox;
class UScrollBox;


/**
 * 
 */
UCLASS()
class TCP_PROJECT2_API UChatWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	TObjectPtr<UButton> SendButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	TObjectPtr<UScrollBox> ChatBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	TObjectPtr<UEditableTextBox> InputText;

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void PressSend();

	UFUNCTION()
	void PressChatTextEnder(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION(BlueprintCallable)
	void AddMessage(const FText& InMessage);

	////토글 채팅 부분
	//UFUNCTION(BlueprintCallable, Category = "Chat")
	//void ToggleChatActive(bool bActive);




};
