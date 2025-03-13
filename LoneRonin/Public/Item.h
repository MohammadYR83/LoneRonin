// این خط باعث می‌شود که این هدر فقط یک بار در هر کامپایل پردازش شود و از ارورهای تکراری جلوگیری کند.
#pragma once

// این هدرهای اصلی آنریل انجین هستند که قابلیت‌های پایه‌ای موتور را شامل می‌شوند.
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// `GENERATED_BODY()` نیاز به پردازش‌های خاصی توسط Unreal Header Tool (UHT) دارد.
// پس باید قبل از تعریف کلاس قرار گیرد.
#include "Item.generated.h"

// این دستور `forward declaration` است، یعنی اعلام می‌کند که یک کلاس به نام `USphereComponent` وجود دارد.
// این کار سرعت کامپایل را بالا می‌برد، چون دیگر نیازی نیست که کل فایل سرآیند `USphereComponent` را در اینجا وارد کنیم.
class USphereComponent;

// تعریف کلاس `AItem` که از `AActor` به ارث می‌برد.
// `UCLASS()` یک ماکرو از آنریل است که این کلاس را برای موتور بازی مشخص می‌کند.
UCLASS()
class LONERONIN_API AItem : public AActor
{
    GENERATED_BODY() // این ماکرو نیاز است تا کلاس از سیستم بازتابی (Reflection) آنریل انجین استفاده کند.

public:
    // تابع سازنده (`Constructor`) - این تابع هنگام ساخته‌شدن یک شیء از `AItem` اجرا می‌شود.
    AItem();

    // تابع `Tick` در هر فریم اجرا می‌شود و برای اعمال تغییرات پیوسته روی آیتم استفاده می‌شود.
    virtual void Tick(float DeltaTime) override;

protected:
    // تابع `BeginPlay` فقط یک بار در ابتدای بازی اجرا می‌شود.
    virtual void BeginPlay() override;

    // این تابع هنگام ورود یک شیء دیگر به محدوده‌ی `Sphere` اجرا می‌شود.
    // `UFUNCTION()` با `()` مشخص می‌کند که این تابع یک Callback است و درون آنریل اجرا می‌شود.
    UFUNCTION()
    virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    // این تابع هنگام خروج یک شیء از محدوده‌ی `Sphere` اجرا می‌شود.
    UFUNCTION()
    virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, // virtual زدیم که بتونیم تو کلاس سلاح به سبکی که خودمون دوست داریم استفاده کنیم
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

    // یک اشاره‌گر به `UStaticMeshComponent` که مدل سه‌بعدی آیتم را نگه می‌دارد.
  // `UPROPERTY(VisibleAnywhere)` یعنی این متغیر از همه جا دیده می‌شود ولی فقط از طریق کد قابل تغییر است.
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* ItemMesh;

    // یک اشاره‌گر به `USphereComponent` که محدوده‌ی برخورد آیتم را مشخص می‌کند.
    UPROPERTY(VisibleAnywhere)
    USphereComponent* Sphere;

    // متغیر `RunningTime` برای دنبال کردن زمان اجرا به‌کار می‌رود.
    float RunningTime;

    // `Amplitude` دامنه‌ی حرکت آیتم را مشخص می‌کند.
   // مقدار آن `0.25f` است، یعنی آیتم در یک محدوده‌ی کوچک حرکت می‌کند.
    float Amplitude = 0.25f;

    // `TimeConstant` میزان سرعت حرکت آیتم را کنترل می‌کند.
    float TimeConstant = 5.f;

};






























/*#pragma once چیست؟

این دستور باعث می‌شود که هدر فقط یک بار پردازش شود و از خطای چندباره بودن جلوگیری کند.
#include چطور کار می‌کند؟

برای اضافه کردن قابلیت‌های مورد نیاز از هدرهای موتور بازی استفاده می‌شود.
برای بهینه‌سازی، بعضی کلاس‌ها فقط با class ClassName; اعلام (Forward Declare) می‌شوند.
UCLASS()، UFUNCTION() و UPROPERTY() چه کاری انجام می‌دهند؟

UCLASS() باعث می‌شود این کلاس در سیستم بازتابی آنریل ثبت شود.
UFUNCTION() مشخص می‌کند که تابع قابلیت فراخوانی در موتور را دارد (مثلاً برای برخورد).
UPROPERTY() مشخص می‌کند که این متغیر در آنریل دیده شود و بتوان با آن کار کرد.
چرا Tick و BeginPlay را override کردیم؟

Tick در هر فریم اجرا می‌شود و برای تغییرات پیوسته مناسب است.
BeginPlay فقط یک بار اجرا می‌شود و معمولاً برای مقداردهی اولیه استفاده می‌شود.
OnSphereOverlap و OnSphereEndOverlap چطور کار می‌کنند؟

وقتی یک شیء وارد Sphere شود، تابع OnSphereOverlap اجرا می‌شود.
وقتی شیء خارج شود، تابع OnSphereEndOverlap اجرا می‌شود.
این توابع معمولاً برای بررسی برخورد (Collision) یا جمع‌آوری آیتم استفاده می‌شوند.
چرا از UStaticMeshComponent* و USphereComponent* استفاده کردیم؟

UStaticMeshComponent* برای نمایش مدل سه‌بعدی آیتم استفاده می‌شود.
USphereComponent* برای تشخیص برخورد (Collision) به‌کار می‌رود.
float RunningTime; برای چیست؟

متغیری است که زمان کلی را ذخیره می‌کند و برای حرکت‌های خاص مانند شناور ماندن آیتم‌ها کاربرد دارد.
float Amplitude = 0.25f; و float TimeConstant = 5.f; چه تأثیری دارند؟

Amplitude میزان دامنه‌ی حرکت را تعیین می‌کند.
TimeConstant تعیین می‌کند که تغییرات در چه بازه‌ای از زمان رخ دهند.*/