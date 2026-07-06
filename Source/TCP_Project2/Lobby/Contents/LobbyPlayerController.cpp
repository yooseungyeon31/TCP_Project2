// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "Lobby/ChatWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyPlayerState.h"

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (ChatWidgetTemplate)
		{
			ChatWidgetObject = CreateWidget<UChatWidgetBase>(this, ChatWidgetTemplate);
			if (ChatWidgetObject)
			{
				ChatWidgetObject->AddToViewport(10);
			}
		}
	}


	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}

bool ALobbyPlayerController::C2S_SendMessage_Validate(const FText& Message)
{
	return true;
}

//void ALobbyPlayerController::C2S_SendMessage_Implementation(const FText& Message)
//{
//	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
//	{
//		ALobbyPlayerController* OtherPC = Cast<ALobbyPlayerController>(Iter->Get());
//		if (OtherPC)
//		{
//			OtherPC->S2C_SendMessage(Message);
//		}
//	}
//}

void ALobbyPlayerController::C2S_SendMessage_Implementation(const FText& Message)
{
    //  이 RPC를 호출한(채팅을 보낸) 플레이어 가져옴.
    FString SenderName = TEXT("Unknown");
    if (ALobbyPlayerState* MyPS = GetPlayerState<ALobbyPlayerState>())
    {
        SenderName = MyPS->Nickname.ToString();
    }

    //  [닉네임] 메시지 형태
    FString FullMessageString = FString::Printf(TEXT("[%s] : %s"), *SenderName, *Message.ToString());
    FText FullMessage = FText::FromString(FullMessageString);

    //  조립된 전체 문장 뿌림
    for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
    {
        ALobbyPlayerController* OtherPC = Cast<ALobbyPlayerController>(Iter->Get());
        if (OtherPC)
        {
           
            OtherPC->S2C_SendMessage(FullMessage);
        }
    }
}

void ALobbyPlayerController::S2C_SendMessage_Implementation(const FText& Message)
{
	if (ChatWidgetObject)
	{
		ChatWidgetObject->AddMessage(Message);
	}
}
//토글채팅
//void ALobbyPlayerController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//
//	if (InputComponent)
//	{
//		InputComponent->BindAction("ToggleChat", IE_Pressed, this, &ALobbyPlayerController::OnToggleChat);
//	}
//
//	
//}
////토글 채팅
//void ALobbyPlayerController::OnToggleChat()
//{
//	if (ChatWidgetObject)
//	{
//		ChatWidgetObject->ToggleChatActive(true);
//	}
//}
