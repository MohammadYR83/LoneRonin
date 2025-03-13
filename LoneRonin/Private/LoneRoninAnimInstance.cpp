#include "LoneRoninAnimInstance.h" // اضافه کردن هدر انیمیشن
#include "LoneRoninCharacterCharacter.h" // اضافه کردن کلاس کاراکتر
#include "GameFramework/CharacterMovementComponent.h" // اضافه کردن کامپوننت حرکت کاراکتر
#include "Kismet/KismetMathLibrary.h" // اضافه کردن توابع ریاضی برای محاسبات برداری

// تابع مقداردهی اولیه برای تنظیم متغیرهای اولیه انیمیشن
void ULoneRoninCharacterCharacterAnimInstance::NativeInitializeAnimation()
{
	// اجرای مقداردهی والد
	Super::NativeInitializeAnimation();

	// دریافت اشاره‌گر به کاراکتر مرتبط با این انیمیشن
	LoneRoninCharacterCharacter = Cast<ALoneRoninCharacterCharacter>(TryGetPawnOwner());
	// اگر کاراکتر معتبر بود، کامپوننت حرکت آن را دریافت کن
	if (LoneRoninCharacterCharacter)
	{
		LoneRoninCharacterCharacterMovement = LoneRoninCharacterCharacter->GetCharacterMovement();
	}
}

// تابع به‌روزرسانی انیمیشن در هر فریم
void ULoneRoninCharacterCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);  // اجرای نسخه والد تابع

	// اگر کامپوننت حرکت معتبر بود، اطلاعات حرکتی کاراکتر را دریافت کن
	if (LoneRoninCharacterCharacterMovement)
	{
		// محاسبه سرعت حرکت کاراکتر روی محور X و Y (بدون در نظر گرفتن Z)
		GroundSpeed = UKismetMathLibrary::VSizeXY(LoneRoninCharacterCharacterMovement->Velocity);
		// بررسی اینکه آیا کاراکتر در حال سقوط است یا نه
		IsFalling = LoneRoninCharacterCharacterMovement->IsFalling();
	}
}






/*توضیح کامل مفاهیم و اجزای کد LoneRoninAnimInstance
۱. بررسی کلی کلاس ULoneRoninCharacterCharacterAnimInstance
کلاسی که در این کد تعریف شده، از UAnimInstance ارث‌بری کرده است و مسئول کنترل و مدیریت انیمیشن‌های یک کاراکتر در Unreal Engine است.

این کلاس اطلاعات حرکتی کاراکتر را از ALoneRoninCharacterCharacter دریافت می‌کند و متغیرهای مربوط به سرعت و وضعیت سقوط (GroundSpeed و IsFalling) را به‌روزرسانی می‌کند.

۲. بررسی #include ها (اضافه کردن فایل‌های هدر)
cpp
Copy
Edit
#include "LoneRoninAnimInstance.h" 
#include "LoneRoninCharacterCharacter.h" 
#include "GameFramework/CharacterMovementComponent.h" 
#include "Kismet/KismetMathLibrary.h"
LoneRoninAnimInstance.h → این کلاس را به پروژه معرفی می‌کند.
LoneRoninCharacterCharacter.h → اطلاعات مربوط به کلاس کاراکتر را برای دریافت متغیرهای مورد نیاز وارد می‌کند.
GameFramework/CharacterMovementComponent.h → برای کار با سیستم حرکت کاراکتر استفاده می‌شود.
Kismet/KismetMathLibrary.h → برای استفاده از توابع ریاضی، مانند محاسبه سرعت، به کار می‌رود.
۳. تابع NativeInitializeAnimation (مقداردهی اولیه انیمیشن)
cpp
Copy
Edit
void ULoneRoninCharacterCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation(); 

	LoneRoninCharacterCharacter = Cast<ALoneRoninCharacterCharacter>(TryGetPawnOwner());

	if (LoneRoninCharacterCharacter)
	{
		LoneRoninCharacterCharacterMovement = LoneRoninCharacterCharacter->GetCharacterMovement();
	}
}
تحلیل خط به خط
Super::NativeInitializeAnimation();

این خط، تابع NativeInitializeAnimation کلاس والد (UAnimInstance) را اجرا می‌کند تا مقداردهی‌های داخلی Unreal Engine انجام شود.
LoneRoninCharacterCharacter = Cast<ALoneRoninCharacterCharacter>(TryGetPawnOwner());

TryGetPawnOwner() شیء (Pawn) مربوط به این انیمیشن را دریافت می‌کند.
سپس، Cast<ALoneRoninCharacterCharacter> بررسی می‌کند که آیا این Pawn از نوع ALoneRoninCharacterCharacter است یا نه.
اگر باشد، اشاره‌گر LoneRoninCharacterCharacter مقداردهی می‌شود، در غیر این صورت nullptr خواهد بود.
if (LoneRoninCharacterCharacter)

بررسی می‌کند که آیا کاراکتر معتبر است.
اگر کاراکتر معتبر باشد، کامپوننت حرکتی کاراکتر را دریافت کرده و در LoneRoninCharacterCharacterMovement ذخیره می‌کند.
۴. تابع NativeUpdateAnimation (به‌روزرسانی در هر فریم)
cpp
Copy
Edit
void ULoneRoninCharacterCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (LoneRoninCharacterCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(LoneRoninCharacterCharacterMovement->Velocity);
		IsFalling = LoneRoninCharacterCharacterMovement->IsFalling();
	}
}
تحلیل خط به خط
Super::NativeUpdateAnimation(DeltaTime);

ابتدا تابع والد UAnimInstance::NativeUpdateAnimation اجرا می‌شود تا تنظیمات داخلی Unreal Engine انجام شود.
if (LoneRoninCharacterCharacterMovement)

بررسی می‌کند که آیا اشاره‌گر LoneRoninCharacterCharacterMovement مقداردهی شده است.
اگر معتبر باشد، اطلاعات حرکتی کاراکتر پردازش می‌شود.
GroundSpeed = UKismetMathLibrary::VSizeXY(LoneRoninCharacterCharacterMovement->Velocity);

Velocity بردار سرعت کاراکتر را برمی‌گرداند.
VSizeXY() تابعی از KismetMathLibrary است که طول بردار سرعت را فقط در صفحه XY محاسبه می‌کند. (سرعت افقی)
IsFalling = LoneRoninCharacterCharacterMovement->IsFalling();

IsFalling() بررسی می‌کند که آیا کاراکتر در حال سقوط است (یعنی روی زمین نیست) یا نه.
مقدار true نشان‌دهنده این است که کاراکتر در هوا است.
۵. بررسی UCLASS() و UPROPERTY()
UCLASS()
cpp
Copy
Edit
UCLASS()
class LONERONIN_API ULoneRoninCharacterCharacterAnimInstance : public UAnimInstance
UCLASS() → این ماکرو به Unreal Engine می‌گوید که این کلاس یک کلاس UObject است و در موتور قابل استفاده است.
LONERONIN_API → این ماکرو تعیین می‌کند که کلاس در سطح ماژول LONERONIN در دسترس باشد.
UPROPERTY()
cpp
Copy
Edit
UPROPERTY(BlueprintReadOnly)
class ALoneRoninCharacterCharacter* LoneRoninCharacterCharacter;

UPROPERTY(BlueprintReadOnly, Category = Movement)
class UCharacterMovementComponent* LoneRoninCharacterCharacterMovement;

UPROPERTY(BlueprintReadOnly, Category = Movement)
float GroundSpeed;

UPROPERTY(BlueprintReadOnly, Category = Movement)
bool IsFalling;
BlueprintReadOnly → مشخص می‌کند که این متغیرها در Blueprint قابل خواندن هستند اما قابل تغییر نیستند.
Category = Movement → این متغیرها را در دسته Movement داخل Blueprint دسته‌بندی می‌کند.
۶. بررسی :: و ->
عملگر :: (Scope Resolution)
Super::NativeInitializeAnimation();
Super:: یعنی تابع NativeInitializeAnimation را از کلاس والد (UAnimInstance) اجرا کن.
عملگر -> (دسترسی به اعضای کلاس از طریق اشاره‌گر)
LoneRoninCharacterCharacter->GetCharacterMovement();
LoneRoninCharacterCharacter یک اشاره‌گر به کلاس ALoneRoninCharacterCharacter است.
-> برای دسترسی به تابع GetCharacterMovement() استفاده شده است.
۷. جمع‌بندی
✅ این کلاس، یک انیمیشن اینستنس برای کاراکتر است که:

مقداردهی اولیه (NativeInitializeAnimation) → دریافت کاراکتر و تنظیم کامپوننت حرکتی
به‌روزرسانی در هر فریم (NativeUpdateAnimation) → محاسبه سرعت و وضعیت سقوط
✅ از کامپوننت حرکت (CharacterMovementComponent) برای دریافت اطلاعات حرکتی استفاده شده است.

✅ دو متغیر اصلی:

GroundSpeed → سرعت حرکت روی زمین
IsFalling → بررسی وضعیت سقوط
✅ مفاهیم مهم استفاده شده:

:: → دسترسی به تابع کلاس والد
-> → دسترسی به اعضای کلاس با اشاره‌گر
Cast<T> → تبدیل Pawn به کلاس دلخواه
VSizeXY() → محاسبه سرعت در صفحه XY
IsFalling() → بررسی وضعیت کاراکتر روی زمین*/