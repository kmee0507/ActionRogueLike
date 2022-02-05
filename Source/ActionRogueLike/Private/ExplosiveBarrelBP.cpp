// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrelBP.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AExplosiveBarrelBP::AExplosiveBarrelBP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetCollisionProfileName("PhysicsActor");
	RootComponent = StaticMeshComp;
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->Radius = 700.0f;
	RadialForceComp->ImpulseStrength = 2000.0f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->SetupAttachment(StaticMeshComp);

}

// Called when the game starts or when spawned
void AExplosiveBarrelBP::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComp->OnComponentHit.AddDynamic(this, &AExplosiveBarrelBP::OnHit);
	
}

// Called every frame
void AExplosiveBarrelBP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosiveBarrelBP::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	RadialForceComp->FireImpulse();
	UE_LOG(LogTemp, Warning, TEXT("We Hit Barrel"));
}

