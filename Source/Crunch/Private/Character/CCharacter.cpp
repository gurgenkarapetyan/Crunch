// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CCharacter.h"

#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	CAbilitySystemComponent = CreateDefaultSubobject<UCAbilitySystemComponent>( FName("CAbility System Component"));
	CAttributeSet = CreateDefaultSubobject<UCAttributeSet>(FName("CAttribute Set"));
}

void ACCharacter::ServerSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
	CAbilitySystemComponent->ApplyInitialEffects();
}

void ACCharacter::ClientSideInit()
{
	CAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACCharacter::GetAbilitySystemComponent() const
{
	return CAbilitySystemComponent;
}

