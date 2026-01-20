#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Task6Actor2.generated.h"

UCLASS()
class TASK6_API ATask6Actor2 : public AActor
{
	GENERATED_BODY()

public:
	// 생성자
	ATask6Actor2();

protected:
	// 게임 시작 시 호출
	virtual void BeginPlay() override;

	// 타이머에서 호출될 회전 함수
	void RotatePlatform();

	// 플랫폼 스태틱 메쉬
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform")
	UStaticMeshComponent* StaticMesh2;

	// 회전 속도 (초당 Y축)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Rotation")
	float RotationSpeed = 45.f;

	// 회전 간격 (초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Rotation")
	float RotationInterval = 0.02f; // 50Hz 정도

private:
	// 타이머 핸들
	FTimerHandle RotationTimerHandle;
};
