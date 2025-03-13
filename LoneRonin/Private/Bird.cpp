// اضافه کردن فایل سرآیند (Header) "Bird.h" که شامل تعریف‌های این کلاس است
#include "Bird.h"

// اضافه کردن کتابخانه‌هایی که قابلیت‌های مربوط به اجزای مختلف را فراهم می‌کنند:
#include "Components/CapsuleComponent.h"  // برای برخورد فیزیکی (Hitbox)
#include "Components/SkeletalMeshComponent.h" // برای نمایش مدل سه‌بعدی (مش)
#include "GameFramework/SpringArmComponent.h" // برای نگه داشتن دوربین در فاصله‌ای از پرنده
#include "Camera/CameraComponent.h" // برای نمایش صحنه از دید بازیکن

// ساخت تابع سازنده‌ی کلاس `ABird`
// در C++، وقتی یک شیء از یک کلاس ساخته می‌شود، تابع سازنده (`Constructor`) اجرا می‌شود
ABird::ABird()
{
	// `PrimaryActorTick.bCanEverTick` مشخص می‌کند که آیا این Actor باید هر فریم به‌روزرسانی شود یا نه
	PrimaryActorTick.bCanEverTick = true;

	// ایجاد یک شیء جدید از نوع `UCapsuleComponent` برای برخورد فیزیکی پرنده
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	// تنظیم ارتفاع کپسول برخورد (کپسول نصف این مقدار به بالا و پایین امتداد دارد)
	Capsule->SetCapsuleHalfHeight(20.f);
	// تنظیم شعاع کپسول، که عرض آن را مشخص می‌کند
	Capsule->SetCapsuleRadius(15.f);
	// تنظیم کپسول به‌عنوان `RootComponent` یعنی مهم‌ترین بخش پرنده که همه چیز به آن متصل خواهد شد
	SetRootComponent(Capsule);

	// ایجاد مش (مدل سه‌بعدی پرنده) که یک `SkeletalMeshComponent` است
	BridMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BridMesh"));
	// متصل کردن مش به `RootComponent` یعنی کپسول، تا مش همراه با آن حرکت کند
	BridMesh->SetupAttachment(GetRootComponent());

	// ایجاد یک بازوی فنری (Spring Arm) که دوربین را نگه می‌دارد
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	// متصل کردن بازوی فنری به `RootComponent` (کپسول) تا همراه پرنده حرکت کند
	SpringArm->SetupAttachment(GetRootComponent());
	// تعیین فاصله‌ی بازوی فنری از پرنده (یعنی دوربین 300 واحد از پرنده فاصله خواهد داشت)
	SpringArm->TargetArmLength = 300.f;

	// ایجاد یک دوربین که دید بازیکن را مشخص می‌کند
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewComponent"));
	// متصل کردن دوربین به بازوی فنری تا همیشه همراه آن حرکت کند
	ViewCamera->SetupAttachment(SpringArm);

	// تعیین می‌کند که این پرنده به‌طور خودکار کنترل بازیکن شماره 0 را به دست بگیرد
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// تابع `BeginPlay` فقط یک بار در ابتدای بازی اجرا می‌شود
void ABird::BeginPlay()
{
	// `Super::BeginPlay()` باعث می‌شود که نسخه‌ی والد این تابع هم اجرا شود
	Super::BeginPlay();
}

// این تابع پرنده را در جهت جلو یا عقب حرکت می‌دهد
void ABird::MoveForward(float Value)
{
	// بررسی می‌کند که آیا `Controller` (کنترل‌کننده‌ی بازیکن) موجود است و مقدار ورودی صفر نیست
	if (Controller && (Value != 0.f))
	{
		// `GetActorForwardVector()` جهت رو به جلوی پرنده را برمی‌گرداند
		// `AddMovementInput` مقدار `Value` را به حرکت پرنده در این جهت اضافه می‌کند
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

// این تابع پرنده را به چپ یا راست می‌چرخاند
void ABird::Turn(float Value)
{
	// `AddControllerYawInput` مقدار `Value` را به چرخش افقی (Yaw) پرنده اضافه می‌کند
	AddControllerYawInput(Value);
}

// این تابع زاویه‌ی دید را بالا یا پایین می‌برد
void ABird::LookUp(float Value)
{
	// `AddControllerPitchInput` مقدار `Value` را به چرخش عمودی (Pitch) پرنده اضافه می‌کند
	AddControllerPitchInput(Value);
}

// این تابع در هر فریم از بازی اجرا می‌شود
void ABird::Tick(float DeltaTime)
{
	// `Super::Tick(DeltaTime)` باعث می‌شود که نسخه‌ی والد این تابع نیز اجرا شود
	Super::Tick(DeltaTime);
}

// این تابع ورودی‌های بازیکن را تنظیم می‌کند
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// `Super::SetupPlayerInputComponent(PlayerInputComponent)` تابع والد را اجرا می‌کند
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// `BindAxis` دکمه‌ی مربوط به حرکت رو به جلو را به تابع `MoveForward` متصل می‌کند
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABird::MoveForward);
	// `BindAxis` دکمه‌ی مربوط به چرخش افقی را به تابع `Turn` متصل می‌کند
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ABird::Turn);
	// `BindAxis` دکمه‌ی مربوط به چرخش عمودی را به تابع `LookUp` متصل می‌کند
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABird::LookUp);

}

