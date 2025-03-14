// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

//الان تو این مرحله اتچ کردن وپن برای دستاییم و باید از کاراکتر استفاده کنیم پس اینکلود میکنیم
#include "LoneRoninCharacterCharacter.h"

// از .h ساخته شده
void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// حالا برای اینکه اون ویژگی و دستورات تابع اصلی تو ایتم رو داشته باشیم میایم از سوپر استفاده میکنیم و تابع های داخل اونو با این  روش زیر اجحرا مکنیم
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	// تلاش برای تبدیل OtherActor به ALoneRoninCharacterCharacter
	ALoneRoninCharacterCharacter* LoneRoninCharacterCharacter = Cast<ALoneRoninCharacterCharacter>(OtherActor);
	// بررسی اینکه آیا تبدیل موفقیت‌آمیز بوده است
	if (LoneRoninCharacterCharacter)
	{
		// تعریف قوانین پیوست برای قرار دادن آیتم روی شخصیت
        // EAttachmentRule::SnapToTarget باعث می‌شود که آیتم دقیقاً در مکان و چرخش سوکت قرار گیرد
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		// پیوست کردن مش آیتم (ItemMesh) به مش شخصیت (Skeletal Mesh)
        // آیتم به سوکت "RightHandWeapon" در مش شخصیت متصل می‌شود
		ItemMesh->AttachToComponent(LoneRoninCharacterCharacter->GetMesh(),TransformRules,FName("RightHandWeapon"));
	}
}

// از .h ساخته شده
void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// حالا برای اینکه اون ویژگی و دستورات تابع اصلی تو ایتم رو داشته باشیم میایم از سوپر استفاده میکنیم و تابع های داخل اونو با این  روش زیر اجحرا مکنیم
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
