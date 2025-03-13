#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LoneRoninCharacterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class LONERONIN_API ALoneRoninCharacterCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ALoneRoninCharacterCharacter();	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
private:
	UPROPERTY(VisibleAnywhere);
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere);
	UCameraComponent* ViewCamera;
};
















/*تحلیل و توضیح کامل کد LoneRoninCharacterCharacter.h
۱. بررسی کلی کلاس ALoneRoninCharacterCharacter
این کلاس، از ACharacter ارث‌بری کرده است و نشان‌دهنده‌ی کاراکتر اصلی بازی است.
این کلاس شامل متدهایی برای:

حرکت کاراکتر (به جلو، عقب، چپ، راست)
چرخش دوربین (Turn و LookUp)
تعریف اجزای دوربین (USpringArmComponent و UCameraComponent)
مدیریت ورودی بازیکن
۲. #pragma once و #includeها
cpp
Copy
Edit
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LoneRoninCharacterCharacter.generated.h"
#pragma once → از تعریف چندباره‌ی این هدر جلوگیری می‌کند.
CoreMinimal.h → شامل فایل‌های ضروری Unreal Engine است.
GameFramework/Character.h → برای ارث‌بری از ACharacter لازم است.
LoneRoninCharacterCharacter.generated.h
این فایل اتوماتیک توسط Unreal Engine ساخته می‌شود و نباید حذف شود.
این فایل، قابلیت‌های Reflection System و Blueprint Integration را به کلاس اضافه می‌کند.
۳. UCLASS() و تعریف کلاس
cpp
Copy
Edit
UCLASS()
class LONERONIN_API ALoneRoninCharacterCharacter : public ACharacter
{
	GENERATED_BODY()
UCLASS() → این ماکرو مشخص می‌کند که این کلاس در Unreal Engine قابل استفاده است.
LONERONIN_API → این ماکرو تعیین می‌کند که کلاس در سطح ماژول LONERONIN در دسترس باشد.
GENERATED_BODY() → Unreal Engine از این ماکرو برای اضافه کردن قابلیت‌های Reflection و Blueprint استفاده می‌کند.
۴. متدهای عمومی (Public)
سازنده‌ی کلاس (Constructor)
cpp
Copy
Edit
public:
	ALoneRoninCharacterCharacter();
این سازنده‌ی کلاس است که هنگام ایجاد یک شیء از این کلاس اجرا می‌شود.
Tick(float DeltaTime) → به‌روزرسانی هر فریم
cpp
Copy
Edit
virtual void Tick(float DeltaTime) override;
این تابع هر فریم اجرا می‌شود و می‌توان از آن برای اعمال تغییرات روی کاراکتر در هر فریم استفاده کرد.
SetupPlayerInputComponent() → تنظیم ورودی بازیکن
cpp
Copy
Edit
virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
این تابع برای تنظیم کنترل‌های بازیکن (مثل حرکت و چرخش دوربین) استفاده می‌شود.
۵. متدهای محافظت‌شده (Protected)
BeginPlay() → اجرا هنگام شروع بازی
cpp
Copy
Edit
protected:
	virtual void BeginPlay() override;
این تابع هنگام شروع بازی یا هنگام ورود این کاراکتر به بازی اجرا می‌شود.
برای مقداردهی اولیه‌ی اجزا استفاده می‌شود.
متدهای حرکتی و چرخش دوربین
cpp
Copy
Edit
void MoveForward(float Value);
void MoveRight(float Value);
void Turn(float Value);
void LookUp(float Value);
MoveForward(float Value) → حرکت کاراکتر به جلو یا عقب
MoveRight(float Value) → حرکت به چپ یا راست
Turn(float Value) → چرخش افقی دوربین (چرخش به چپ/راست)
LookUp(float Value) → چرخش عمودی دوربین (بالا/پایین نگاه کردن)
۶. متغیرهای خصوصی (Private)
cpp
Copy
Edit
private:
	UPROPERTY(VisibleAnywhere);
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere);
	UCameraComponent* ViewCamera;
تحلیل متغیرها
SpringArm (بازوی فنری دوربین)
این کامپوننت باعث می‌شود که دوربین با فاصله‌ی مشخصی از کاراکتر قرار گیرد و حرکت آن را نرم‌تر کند.
ViewCamera (دوربین اصلی بازی)
این دوربین، نمایی که بازیکن می‌بیند را کنترل می‌کند.
UPROPERTY(VisibleAnywhere)
VisibleAnywhere → باعث می‌شود که این متغیر در جزئیات (Details Panel) موتور یونریل نمایش داده شود، اما در Blueprint تغییر نکند.
۷. جمع‌بندی کلی
✅ این کلاس نماینده‌ی کاراکتر بازیکن در بازی است و شامل:

مدیریت ورودی بازیکن (حرکت و چرخش دوربین)
اجزای دوربین (USpringArmComponent و UCameraComponent)
تعریف توابع حرکتی (MoveForward، MoveRight)
تعریف توابع چرخش (Turn، LookUp)
وراثت از ACharacter برای کنترل کامل روی حرکت و فیزیک کاراکتر*/