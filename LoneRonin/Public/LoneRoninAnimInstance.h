// این دستور باعث می‌شود که این هدر فقط یک‌بار در هنگام کامپایل شدن پردازش شود و از تعریف‌های تکراری جلوگیری کند.
#pragma once
// فایل هدر اصلی موتور آنریل برای دسترسی به قابلیت‌های ضروری
#include "CoreMinimal.h"
// کلاس پایه برای مدیریت انیمیشن‌های شخصیت‌ها در آنریل انجین
#include "Animation/AnimInstance.h"
// ایجاد یک کلاس جدید با نام ULoneRoninCharacterCharacterAnimInstance
#include "LoneRoninAnimInstance.generated.h"

// تعریف یک کلاس جدید که از UAnimInstance ارث‌بری می‌کند.
// این کلاس به عنوان یک نمونه انیمیشن برای شخصیت در بازی عمل می‌کند.
UCLASS()
class LONERONIN_API ULoneRoninCharacterCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY() // این ماکرو وظیفه دارد که کد مورد نیاز Unreal Engine را برای این کلاس ایجاد کند.

public:
	// تابعی که هنگام مقداردهی اولیه انیمیشن فراخوانی می‌شود (معادل Constructor برای انیمیشن‌ها)
	virtual void NativeInitializeAnimation() override;
	// تابعی که در هر فریم برای به‌روزرسانی وضعیت انیمیشن فراخوانی می‌شود.
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	// اشاره‌گر به کلاس شخصیت که از طریق این انیمیشن کنترل می‌شود.
	UPROPERTY(BlueprintReadOnly) // این متغیر فقط خواندنی است و در بلواپرینت (Blueprint) قابل استفاده است.
	class ALoneRoninCharacterCharacter* LoneRoninCharacterCharacter;

	// اشاره‌گر به کامپوننت حرکت شخصیت، برای بررسی وضعیت حرکت آن
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* LoneRoninCharacterCharacterMovement;

	// سرعت حرکت شخصیت روی زمین
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	// آیا شخصیت در حال سقوط است یا خیر
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;

};























/*۱. UCLASS() چیست؟
این یک ماکرو از Unreal Engine است که مشخص می‌کند این کلاس یک کلاس قابل استفاده در سیستم Reflection موتور است. یعنی این کلاس می‌تواند در موتور و در ابزارهای مانند Blueprint دیده و استفاده شود.

۲. GENERATED_BODY() چیست؟
این ماکرو کدی را که برای کارکرد کلاس در آنریل انجین ضروری است، در زمان کامپایل ایجاد می‌کند.

۳. UAnimInstance چیست؟
UAnimInstance کلاس پایه‌ای است که برای کنترل و مدیریت انیمیشن‌های یک شخصیت استفاده می‌شود. این کلاس به بلواپرینت متصل می‌شود و به شخصیت امکان می‌دهد تا بر اساس وضعیت فعلی خود، انیمیشن مناسب را اجرا کند.

۴. NativeInitializeAnimation() و NativeUpdateAnimation(float DeltaTime)
NativeInitializeAnimation(): این تابع در ابتدای بازی (هنگامی که انیمیشن مقداردهی اولیه می‌شود) اجرا می‌شود. معمولاً در این تابع، مقادیر اولیه تنظیم شده و اشیاء مورد نیاز دریافت می‌شوند.
NativeUpdateAnimation(float DeltaTime): این تابع در هر فریم اجرا می‌شود و برای به‌روزرسانی وضعیت انیمیشن بر اساس داده‌های شخصیت استفاده می‌شود. DeltaTime مدت زمان سپری شده از آخرین فریم را نشان می‌دهد.
۵. UPROPERTY(BlueprintReadOnly) چیست؟
این یک ماکرو از Unreal Engine است که تعیین می‌کند متغیر قابل خواندن در Blueprint باشد اما امکان تغییر مقدار آن در بلواپرینت وجود ندارد.

۶. ALoneRoninCharacterCharacter* LoneRoninCharacterCharacter;
این یک اشاره‌گر به کلاس کاراکتر بازی است.
از طریق این متغیر، انیمیشن می‌تواند به وضعیت کاراکتر (مثلاً سرعت، وضعیت سقوط، و ...) دسترسی داشته باشد.
۷. UCharacterMovementComponent* LoneRoninCharacterCharacterMovement;
این اشاره‌گر به کامپوننت حرکت کاراکتر است.
UCharacterMovementComponent وظیفه مدیریت حرکت کاراکتر را دارد (مثلاً حرکت روی زمین، پرش، سقوط، و ...).
از این متغیر برای دریافت اطلاعاتی مثل سرعت و وضعیت سقوط استفاده می‌شود.
۸. GroundSpeed چیست؟
GroundSpeed سرعت فعلی کاراکتر روی زمین را ذخیره می‌کند.
از این متغیر در NativeUpdateAnimation() استفاده می‌شود تا مقدار آن از CharacterMovementComponent دریافت شود.
۹. IsFalling چیست؟
IsFalling مشخص می‌کند که آیا کاراکتر در حال سقوط است یا نه.
مقدار این متغیر با استفاده از تابع IsFalling() از CharacterMovementComponent به‌روزرسانی می‌شود.*/