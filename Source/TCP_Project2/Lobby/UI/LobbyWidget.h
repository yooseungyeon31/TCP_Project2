// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UVerticalBox;
class UButton;
class ULobbyUserWidget;
class ALobbyPlayerState;
/**
 * 
 */
UCLASS()
class TCP_PROJECT2_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<ALobbyPlayerState*> GetLobbyPlayerStates();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ALobbyPlayerState* GetLobbyPlayerStateAtIndex(int32 InIndex);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> UserList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Btn_Close;

	

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ULobbyUserWidget> LobbyUserWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<ULobbyUserWidget>> LobbyUsers;
	
};
