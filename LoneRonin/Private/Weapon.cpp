// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// از .h ساخته شده
void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// حالا برای اینکه اون ویژگی و دستورات تابع اصلی تو ایتم رو داشته باشیم میایم از سوپر استفاده میکنیم و تابع های داخل اونو با این  روش زیر اجحرا مکنیم
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

// از .h ساخته شده
void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// حالا برای اینکه اون ویژگی و دستورات تابع اصلی تو ایتم رو داشته باشیم میایم از سوپر استفاده میکنیم و تابع های داخل اونو با این  روش زیر اجحرا مکنیم
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
