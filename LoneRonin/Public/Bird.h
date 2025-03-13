// ***** جلوگیری از تعریف چندباره‌ی این هدر *****
// زمانی که یک فایل Header در پروژه چند بار Include شود، ممکن است خطای چندباره‌تعریف (Redefinition) ایجاد شود.
// دستور `#pragma once` باعث می‌شود که این فایل فقط یک بار در طول کامپایل پردازش شود.
#pragma once

// ***** ایمپورت کتابخانه‌های ضروری *****
// "CoreMinimal.h" شامل توابع پایه‌ای موتور Unreal Engine است.
// "GameFramework/Pawn.h" شامل تعریف کلاس `APawn` است که این کلاس از آن ارث‌بری می‌کند.
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// ***** معرفی کلاس `ABird` برای Unreal Engine *****
// "GENERATED_BODY()" یک ماکرو (Macro) از UE5 است که کدهای ضروری موتور را به کلاس اضافه می‌کند.
#include "Bird.generated.h"

// ***** Forward Declaration *****
// در Unreal Engine، اگر یک کلاس را فقط به‌عنوان اشاره‌گر (Pointer) استفاده کنیم، نیازی به `#include` کردن کامل آن نیست.
// این کار باعث کاهش زمان کامپایل می‌شود. در `Bird.cpp` این کلاس‌ها را `#include` خواهیم کرد.
class UCapsuleComponent; // کامپوننت برای تشخیص برخورد (Collision)
class USkeletalMeshComponent; // مش (Mesh) برای نمایش مدل سه‌بعدی پرنده
class USpringArmComponent; // بازوی فنری برای نگه داشتن دوربین پشت پرنده
class UCameraComponent; // دوربین برای نمایش نمای اول‌شخص یا سوم‌شخص

// ***** تعریف کلاس ABird *****
// این کلاس از `APawn` ارث‌بری می‌کند، یعنی قابلیت‌هایی مثل کنترل شدن توسط بازیکن را دارد.
// در Unreal Engine، `APawn` به‌عنوان یک کلاس پایه برای اشیایی که بازیکن کنترل می‌کند استفاده می‌شود.
UCLASS()
class LONERONIN_API ABird : public APawn
{
	GENERATED_BODY() // این ماکرو ویژگی‌های خاص UE را به کلاس اضافه می‌کند، مثل سیستم Reflection و Garbage Collection.

public:
	// ***** تابع سازنده (Constructor) *****
	// این تابع هنگام ساخته شدن یک نمونه (Instance) از `ABird` در بازی اجرا می‌شود.
	// وظیفه‌ی این تابع این است که مقداردهی اولیه را انجام دهد.
	ABird();

	// ***** تابع Tick (اجرای کد در هر فریم) *****
	// این تابع در هر فریم از بازی اجرا می‌شود.
	// `DeltaTime` مدت‌زمانی است که از آخرین فریم گذشته است و به ما کمک می‌کند تا حرکات روان ایجاد کنیم.
	virtual void Tick(float DeltaTime) override;

	// ***** تابع تنظیم ورودی‌های بازیکن *****
	// این تابع در هنگام راه‌اندازی اجرا می‌شود و دکمه‌هایی که بازیکن می‌تواند فشار دهد را مشخص می‌کند.
	// مثلاً وقتی دکمه‌ی "W" را فشار دهیم، پرنده جلو می‌رود.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// ***** تابع BeginPlay (وقتی بازی شروع می‌شود) *****
	// این تابع فقط یک بار، هنگام شروع بازی، اجرا می‌شود.
	// از این تابع می‌توان برای مقداردهی اولیه و تنظیمات اولیه استفاده کرد.
	virtual void BeginPlay() override;

	// ***** توابع حرکتی پرنده *****
	// این توابع برای کنترل حرکت پرنده هنگام دریافت ورودی‌های بازیکن استفاده می‌شوند.

	// تابع `MoveForward` مقدار `Value` را دریافت می‌کند و پرنده را به جلو یا عقب حرکت می‌دهد.
	void MoveForward(float Value);

	// تابع `Turn` مقدار `Value` را دریافت می‌کند و پرنده را به چپ یا راست می‌چرخاند.
	void Turn(float Value);

	// تابع `LookUp` مقدار `Value` را دریافت می‌کند و دوربین را به بالا یا پایین حرکت می‌دهد.
	void LookUp(float Value);

private:
	// ***** اجزای پرنده (Components) *****
    // `UPROPERTY(VisibleAnywhere)` باعث می‌شود که این متغیر در پنل `Details` در ادیتور Unreal قابل مشاهده باشد،
    // اما از طریق Blueprint نمی‌توان مقدار آن را تغییر داد.

	// **کپسول برخورد (Collision Capsule)**
	// این کپسول به عنوان مرز برخوردی (Hitbox) برای پرنده عمل می‌کند.
	// این کامپوننت باعث می‌شود که Unreal Engine تشخیص دهد که پرنده با اجسام دیگر برخورد کرده است یا نه.
	UPROPERTY(VisibleAnywhere);
	UCapsuleComponent* Capsule; 

	// **مش سه‌بعدی پرنده (Skeletal Mesh)**
	// این کامپوننت مدل سه‌بعدی پرنده را نمایش می‌دهد و می‌تواند شامل انیمیشن‌های پرواز نیز باشد.
	UPROPERTY(VisibleAnywhere);
	USkeletalMeshComponent* BridMesh;

	// **کامپوننت بازوی فنری (Spring Arm)**
	// این کامپوننت برای مدیریت موقعیت دوربین نسبت به پرنده استفاده می‌شود.
	// این بازوی فنری دوربین را در فاصله‌ی مشخصی از پرنده نگه می‌دارد و هنگام برخورد با موانع،
	// طول خود را کوتاه می‌کند تا از گیر کردن دوربین پشت دیوارها جلوگیری کند.
	UPROPERTY(VisibleAnywhere);
	USpringArmComponent* SpringArm;

	// **کامپوننت دوربین (Camera)**
	// این کامپوننت دید بازیکن را مشخص می‌کند. می‌توانیم آن را در حالت سوم‌شخص قرار دهیم،
	// یا آن را به‌عنوان دوربین اول‌شخص تنظیم کنیم.
	UPROPERTY(VisibleAnywhere);
	UCameraComponent* ViewCamera;
};
