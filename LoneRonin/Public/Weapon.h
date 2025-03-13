// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class LONERONIN_API AWeapon : public AItem // این کلاس اسلحه از Item ارثبری کرده و ویژگیای اون مثل اورلپ و حرکت سینوسی رو داره
{
	GENERATED_BODY()
protected:

    // اینارو از ایتم اوردیم  و ufunction هارو حذف کردیم تا به ارور نخوریم و ی اور راید هم تهشون اضافه کردیم
    // حالا اینکه تو کلاس فرزند virtual رو بنویسم یا نه اختیاری و نوشتنش برای مستند سازی خوبه
    virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult) override;
    virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)  override;
};
