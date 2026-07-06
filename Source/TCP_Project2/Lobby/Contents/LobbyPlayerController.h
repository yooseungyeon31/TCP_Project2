#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h" // 본인 파일명 확인

class UChatWidgetBase; // 새로 만든 공용 채팅 위젯으로 지정!

UCLASS()
class TCP_PROJECT2_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// 강사님 코드에서 채팅 UI 템플릿과 생성된 객체를 보관할 변수 이식
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UChatWidgetBase> ChatWidgetTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UChatWidgetBase> ChatWidgetObject;

	// --- 채팅 네트워크 RPC 함수 이식 ---
	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_SendMessage(const FText& Message);
	bool C2S_SendMessage_Validate(const FText& Message);
	void C2S_SendMessage_Implementation(const FText& Message);

	UFUNCTION(Client, Reliable)
	void S2C_SendMessage(const FText& Message);
	void S2C_SendMessage_Implementation(const FText& Message);

//	//토글채팅
//protected:
//	virtual void SetupInputComponent() override;
//
//	void OnToggleChat();
};