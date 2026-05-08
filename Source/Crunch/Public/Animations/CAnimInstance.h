// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

class UCharacterMovementComponent;

UCLASS()
class CRUNCH_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Initializes the animation instance and caches the owning character and movement component.
	 */
	virtual void NativeInitializeAnimation() override;

	/**
	 * @brief Updates animation values such as speed, jumping state, yaw speed, and look offsets.
	 * @param DeltaSeconds Time elapsed since the previous animation update.
	 */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/**
	 * @brief Performs thread-safe animation updates.
	 * @param DeltaSeconds Time elapsed since the previous thread-safe animation update.
	 */
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	/**
	 * @brief Returns whether the character is currently jumping or falling.
	 * @return True if the character is in the air.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool GetIsJumping() const { return bIsJumping; }

	/**
	 * @brief Returns whether the character is currently on the ground.
	 * @return True if the character is not jumping or falling.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool GetIsOnGround() const { return !bIsJumping; }

	/**
	 * @brief Returns the current movement speed of the owning character.
	 * @return Character velocity length.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetSpeed() const { return Speed; } 

	/**
	 * @brief Returns whether the character is currently moving.
	 * @return True if speed is not zero.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsMoving() const { return Speed != 0; }

	/**
	 * @brief Returns whether the character is currently not moving.
	 * @return True if speed is zero.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsNotMoving() const { return Speed == 0; }

	/**
	 * @brief Returns the raw yaw rotation speed of the character body.
	 * @return Yaw speed in degrees per second.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetYawSpeed() const { return YawSpeed; }

	/**
	 * @brief Returns the interpolated yaw rotation speed of the character body.
	 * @return Smoothed yaw speed value.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetSmoothedYawSpeed() const { return SmoothedYawSpeed; }

	/**
	 * @brief Returns the yaw offset between the aim rotation and body rotation.
	 * @return Look yaw offset in degrees.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetLookYawOffset() const { return LookRotationOffset.Yaw; }

	/**
	 * @brief Returns the pitch offset between the aim rotation and body rotation.
	 * @return Look pitch offset in degrees.
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	FORCEINLINE float GetLookPitchOffset() const { return LookRotationOffset.Pitch; }
	
private:

	/** Owning character used as the source of movement and rotation data. */
	UPROPERTY()
	ACharacter* OwnerCharacter = nullptr;

	/** Movement component used to query the character movement state. */
	UPROPERTY()
	UCharacterMovementComponent* OwnerMovementComponent = nullptr;

	/** True when the character is falling or jumping. */
	bool bIsJumping = false;

	/** Current velocity length of the owning character. */
	float Speed = 0.f;

	/** Raw yaw rotation speed calculated from body rotation delta. */
	float YawSpeed = 0.f;

	/** Interpolated yaw speed used for smoother animation blending. */
	float SmoothedYawSpeed = 0.f;

	/** Interpolation speed used when smoothing yaw speed. */
	UPROPERTY(EditAnywhere, Category = "Animation")
	float YawSpeedSmoothLerpSpeed = 1.f;

	/** Previous body rotation used to calculate yaw rotation delta. */
	FRotator BodyPreviousRotation = FRotator::ZeroRotator;

	/** Offset between the character aim rotation and body rotation. */
	FRotator LookRotationOffset = FRotator::ZeroRotator;
};