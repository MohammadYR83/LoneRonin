#include "LoneRoninCharacterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ALoneRoninCharacterCharacter::ALoneRoninCharacterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewComponent"));
	ViewCamera->SetupAttachment(SpringArm);
}
void ALoneRoninCharacterCharacter::BeginPlay()
{
	Super::BeginPlay();	
}
void ALoneRoninCharacterCharacter::MoveForward(float Value)
{
	if (Controller && (Value != 0.f))
	{
		const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value);
	}
}
void ALoneRoninCharacterCharacter::MoveRight(float Value)
{
	if (Controller && (Value != 0.f))
	{
		const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
	}
}
void ALoneRoninCharacterCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}
void ALoneRoninCharacterCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}
void ALoneRoninCharacterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ALoneRoninCharacterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ALoneRoninCharacterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ALoneRoninCharacterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ALoneRoninCharacterCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ALoneRoninCharacterCharacter::LookUp);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
}

















/*تحلیل و توضیح کامل کد LoneRoninCharacterCharacter.cpp
۱. بررسی کلی کلاس
این کلاس پیاده‌سازی متدهای کاراکتر بازی است که در LoneRoninCharacterCharacter.h تعریف شده‌اند.
وظایف کلی این کلاس:

مقداردهی اولیه به اجزای کاراکتر (دوربین، حرکت، تنظیمات چرخش)
کنترل حرکت بازیکن (جلو، عقب، چپ، راست)
چرخش و حرکت دوربین
تنظیم ورودی‌های بازیکن (حرکت، چرخش، پرش)
۲. #include ها
cpp
Copy
Edit
#include "LoneRoninCharacterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
توضیح:
LoneRoninCharacterCharacter.h → کلاس کاراکتر اصلی
SpringArmComponent.h → برای کنترل بازوی فنری دوربین (USpringArmComponent)
CameraComponent.h → برای کنترل دوربین شخصیت (UCameraComponent)
CharacterMovementComponent.h → برای مدیریت حرکت کاراکتر
۳. ALoneRoninCharacterCharacter::ALoneRoninCharacterCharacter() (سازنده)
cpp
Copy
Edit
ALoneRoninCharacterCharacter::ALoneRoninCharacterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewComponent"));
	ViewCamera->SetupAttachment(SpringArm);
}
تحلیل خط به خط:
PrimaryActorTick.bCanEverTick = true;

مشخص می‌کند که این کلاس در هر فریم به‌روزرسانی شود (Tick() اجرا شود).
bUseControllerRotationPitch = false;

جلوگیری از چرخش کاراکتر در محور X (بالا/پایین) با کنترلر.
bUseControllerRotationYaw = false;

جلوگیری از چرخش کاراکتر در محور Y (چپ/راست) با کنترلر.
bUseControllerRotationRoll = false;

جلوگیری از چرخش کاراکتر در محور Z (چرخش افقی).
GetCharacterMovement()->bOrientRotationToMovement = true;

کاراکتر همیشه به سمتی که حرکت می‌کند چرخش داشته باشد.
GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

تعیین سرعت چرخش کاراکتر در محور Yaw (چپ/راست).
تعریف دوربین و بازوی فنری
SpringArm (بازوی فنری)

ایجاد و متصل کردن به ریشه‌ی کاراکتر.
TargetArmLength = 300.f; → فاصله‌ی دوربین از کاراکتر ۳۰۰ واحد.
ViewCamera (دوربین اصلی)

ایجاد و متصل کردن به SpringArm.
۴. BeginPlay()
cpp
Copy
Edit
void ALoneRoninCharacterCharacter::BeginPlay()
{
	Super::BeginPlay();	
}
این تابع هنگام شروع بازی اجرا می‌شود.
فعلاً کاری انجام نمی‌دهد، ولی می‌توان مقداردهی اولیه‌ی بیشتر در آن انجام داد.
۵. MoveForward(float Value) (حرکت به جلو/عقب)
cpp
Copy
Edit
void ALoneRoninCharacterCharacter::MoveForward(float Value)
{
	if (Controller && (Value != 0.f))
	{
		const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value);
	}
}
توضیح:
بررسی آیا کنترلر متصل است و مقدار Value صفر نیست.
ایجاد یک چرخش (YawRotation) که فقط محور Yaw (چپ/راست) را تغییر می‌دهد.
دریافت جهت حرکت X (GetUnitAxis(EAxis::X)) و اعمال حرکت (AddMovementInput).
۶. MoveRight(float Value) (حرکت به چپ/راست)
cpp
Copy
Edit
void ALoneRoninCharacterCharacter::MoveRight(float Value)
{
	if (Controller && (Value != 0.f))
	{
		const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
	}
}
مشابه MoveForward، اما جهت حرکت Y (EAxis::Y) را تنظیم می‌کند.
۷. Turn(float Value) و LookUp(float Value)
cpp
Copy
Edit
void ALoneRoninCharacterCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}
void ALoneRoninCharacterCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}
Turn() → چرخش افقی (Yaw) دوربین.
LookUp() → چرخش عمودی (Pitch) دوربین.
۸. Tick(float DeltaTime)
cpp
Copy
Edit
void ALoneRoninCharacterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
این تابع هر فریم اجرا می‌شود، اما فعلاً هیچ تغییری در کاراکتر ایجاد نمی‌کند.
۹. SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
cpp
Copy
Edit
void ALoneRoninCharacterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ALoneRoninCharacterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ALoneRoninCharacterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ALoneRoninCharacterCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ALoneRoninCharacterCharacter::LookUp);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
}
تحلیل خط به خط
BindAxis(FName("MoveForward"), this, &ALoneRoninCharacterCharacter::MoveForward);
ورودی "MoveForward" را به تابع MoveForward متصل می‌کند.
BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);
دکمه پرش را متصل به تابع Jump() از ACharacter می‌کند.
📌 توجه: نام‌هایی مثل "MoveForward" و "Jump" در Project Settings > Input تعریف شده‌اند.

🔹 جمع‌بندی نهایی
✅ این کلاس مدیریت اصلی حرکت و کنترل‌های بازیکن را انجام می‌دهد و شامل:

تعریف و مقداردهی اولیه اجزای کاراکتر (دوربین، حرکت، چرخش)
متدهای حرکتی (جلو/عقب، چپ/راست)
چرخش دوربین (چپ/راست، بالا/پایین)
تنظیم ورودی بازیکن (حرکت، چرخش، پرش)*/