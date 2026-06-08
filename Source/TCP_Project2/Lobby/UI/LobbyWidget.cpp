// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Lobby/Contents/LobbyPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/GameState.h"

TArray<ALobbyPlayerState*> ULobbyWidget::GetLobbyPlayerStates()
{
	TArray<ALobbyPlayerState*> LobbyPlayerStates;

	if (AGameStateBase* GameState = UGameplayStatics::GetGameState(this))
	{
		for (APlayerState* PlayerState : GameState->PlayerArray)
		{
			ALobbyPlayerState* LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);
			if (LobbyPlayerState == nullptr)
				continue;

			LobbyPlayerStates.Add(LobbyPlayerState);
		}
	}

	return LobbyPlayerStates;
}

ALobbyPlayerState* ULobbyWidget::GetLobbyPlayerStateAtIndex(int32 InIndex)
{
	TArray<ALobbyPlayerState*> LobbyPlayerState = GetLobbyPlayerStates();

	if (InIndex < LobbyPlayerState.Num())
		return LobbyPlayerState[InIndex];

	return nullptr;
}
