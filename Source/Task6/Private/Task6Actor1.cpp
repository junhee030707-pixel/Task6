#include "Task6Actor1.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"

// Sets default values
ATask6Actor1::ATask6Actor1()
{
    // Tick 사용 안함
    PrimaryActorTick.bCanEverTick = false;

    // 스태틱 메쉬 생성 및 루트 지정
    StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh1"));
    RootComponent = StaticMesh1;

    // 임시 큐브 메쉬
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        StaticMesh1->SetStaticMesh(CubeMesh.Object);
    }

    // 메쉬 가시성
    StaticMesh1->SetVisibility(true);
    StaticMesh1->SetMobility(EComponentMobility::Movable);

    // 기본 값
    MoveSpeed = 200.f;
    MaxRange = 500.f;
    MoveDirection = 1;

    // 랜덤 범위용 초기화
    MaxMoveRange = 0.f;
}

// Called when the game starts or when spawned
void ATask6Actor1::BeginPlay()
{
    Super::BeginPlay();

    // 시작 위치 랜덤화
    FVector RandomLocation = FVector(
        FMath::RandRange(-500.f, 500.f),
        FMath::RandRange(-500.f, 500.f),
        GetActorLocation().Z
    );
    SetActorLocation(RandomLocation);

    // StartLocation도 랜덤 위치로 변경
    StartLocation = GetActorLocation();

    // 최대 이동 범위 랜덤
    MaxMoveRange = FMath::RandRange(100.f, MaxRange);

    // 이동 속도 랜덤
    MoveSpeed = FMath::RandRange(MoveSpeedMin, MoveSpeedMax);

    // 타이머 시작
    GetWorld()->GetTimerManager().SetTimer(
        MoveTimerHandle,
        this,
        &ATask6Actor1::MovePlatform,
        MoveInterval,
        true
    );
}

void ATask6Actor1::MovePlatform()
{
    FVector CurrentLocation = GetActorLocation();
    CurrentLocation.X += MoveSpeed * MoveInterval * MoveDirection;

    // 범위를 벗어나면 방향 반전
    if ((CurrentLocation - StartLocation).SizeSquared() >= MaxMoveRange * MaxMoveRange)
    {
        MoveDirection *= -1;
    }

    SetActorLocation(CurrentLocation);
}
