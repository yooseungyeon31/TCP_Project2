// ChatWidgetBase.cpp
#include "ChatWidgetBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

#include "Lobby/Contents/LobbyPlayerController.h"
// #include "MyPlayerController.h" // 나중에 만들 공용 PC 헤더

void UChatWidgetBase::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (SendButton)
    {
        SendButton->OnClicked.AddDynamic(this, &UChatWidgetBase::PressSend);
    }

    if (InputText)
    {
        InputText->OnTextCommitted.AddDynamic(this, &UChatWidgetBase::PressChatTextEnder);
       
    }
    //토글 채팅 부분
    //ToggleChatActive(false);
}

void UChatWidgetBase::PressSend()
{
    // 1. 순정 PC를 먼저 가져온 뒤
    ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(GetOwningPlayer());

   
   
    if (PC && InputText)
    {
        PC->C2S_SendMessage(InputText->GetText()); // 서버로 보내는 RPC (PC 개조 후 주석 해제)
        InputText->SetText(FText::GetEmpty());
    }
}

void UChatWidgetBase::PressChatTextEnder(const FText& Text, ETextCommit::Type CommitMethod)
{
    ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(GetOwningPlayer());
    if (!PC || !InputText) return;

    switch (CommitMethod)
    {
    case ETextCommit::OnEnter:


        PC->C2S_SendMessage(Text); // 서버로 보내는 RPC (PC 개조 후 주석 해제)
        InputText->SetText(FText::GetEmpty());
        //ToggleChatActive(false);
        break;

    case ETextCommit::OnCleared:
        // 포커스가 해제되면 완전히 게임으로 포커스를 돌려줍니다.
        InputText->SetUserFocus(PC);
        //ToggleChatActive(false);
        break;
    }
}

void UChatWidgetBase::AddMessage(const FText& InMessage)
{
    if (ChatBox)
    {
        UTextBlock* NewText = NewObject<UTextBlock>(ChatBox);
        if (NewText)
        {
            NewText->SetText(InMessage);

            // 강사님 스타일 가독성 폰트 크기 세팅
            auto CurrentFont = NewText->GetFont();
            CurrentFont.Size = 24; // 40은 인게임에서 너무 클 수 있으니 취향껏 조절하세요!
            NewText->SetFont(CurrentFont);

            ChatBox->AddChild(NewText);
            ChatBox->ScrollToEnd(); // 새 채팅 오면 맨 아래로 자동 스크롤
        }
    }
}

////채팅창 토글 부분
//void UChatWidgetBase::ToggleChatActive(bool bActive)
//{
//    ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(GetOwningPlayer());
//    if (!PC || !InputText || !SendButton) return;
//
//    if (bActive)
//    {
//        // 1. 숨겨놨던 입력창과 전송 버튼을 다시 보여줍니다.
//        InputText->SetVisibility(ESlateVisibility::Visible);
//        SendButton->SetVisibility(ESlateVisibility::Visible);
//
//        // 2. 마우스 커서와 타이핑 포커스를 입력창으로 강제 배달합니다!
//        InputText->SetUserFocus(PC);
//    }
//    else
//    {
//        // 1. 입력창과 전송 버튼을 화면에서 숨겨서 깔끔하게 만듭니다.
//        InputText->SetVisibility(ESlateVisibility::Collapsed);
//        SendButton->SetVisibility(ESlateVisibility::Collapsed);
//    }
//}
