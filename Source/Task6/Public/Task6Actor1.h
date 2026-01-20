#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Task6Actor1.generated.h"

UCLASS()
class TASK6_API ATask6Actor1 : public AActor
{
    GENERATED_BODY()

public:
    // 생성자
    ATask6Actor1();

protected:
    // 게임 시작 시 호출
    virtual void BeginPlay() override;

    // 타이머에서 호출될 이동 함수
    void MovePlatform();

    // 플랫폼 스태틱 메쉬
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform")
    UStaticMeshComponent* StaticMesh1;

    // 이동 속도 (랜덤 범위)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
    float MoveSpeedMin = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
    float MoveSpeedMax = 400.f;

    // 최대 이동 범위
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
    float MaxRange = 500.f;

    // 이동 간격 (초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform|Movement")
    float MoveInterval = 0.02f;

    // 랜덤으로 결정되는 실제 속도
    float MoveSpeed;

    // 랜덤으로 결정되는 실제 이동 범위
    float MaxMoveRange;

private:
    // 시작 위치
    FVector StartLocation;

    // 이동 방향
    int MoveDirection = 1;

    // 타이머 핸들
    FTimerHandle MoveTimerHandle;
};