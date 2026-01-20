#include "Task6Actor2.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"

// Sets default values
ATask6Actor2::ATask6Actor2()
{
	// Tick 제거
	// PrimaryActorTick.bCanEverTick = true;

	// 스태틱 메쉬 생성 및 루트 지정
	StaticMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DefaultRoot"));
	SetRootComponent(StaticMesh2);

	// 임시 큐브 메쉬
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		StaticMesh2->SetStaticMesh(CubeMesh.Object);
	}

	// 메쉬 가시성
	StaticMesh2->SetVisibility(true);
	StaticMesh2->SetMobility(EComponentMobility::Movable);

	// 기본 회전 속도
	RotationSpeed = 45.f;
}

// Called when the game starts or when spawneds
void ATask6Actor2::BeginPlay()
{
	Super::BeginPlay(); // 부모 BeginPlay 호출

	// 회전 속도 랜덤화
	RotationSpeed = FMath::RandRange(30.f, 90.f);

	// 시작 위치 랜덤
	FVector RandomLocation = FVector(
		FMath::RandRange(-500.f, 500.f),
		FMath::RandRange(-500.f, 500.f),
		GetActorLocation().Z
	);
	SetActorLocation(RandomLocation);

	// 타이머 시작
	GetWorld()->GetTimerManager().SetTimer(
		RotationTimerHandle,
		this,
		&ATask6Actor2::RotatePlatform,
		RotationInterval,
		true
	);
}

// Timer 기반 회전
void ATask6Actor2::RotatePlatform()
{
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.f, RotationSpeed * RotationInterval, 0.f));
	}
}
