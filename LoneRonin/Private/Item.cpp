// وارد کردن هدرهای مورد نیاز برای کار با کامپوننت‌ها و قابلیت‌های بازی
#include "Item.h"  // هدر اصلی مربوط به کلاس AItem
#include "Components/StaticMeshComponent.h" // برای استفاده از StaticMesh برای مدل‌های سه‌بعدی
#include "Components/SphereComponent.h" // برای استفاده از SphereComponent جهت تشخیص برخورد
 
// سازنده کلاس AItem
AItem::AItem()
{
    // فعال کردن امکان Tick در هر فریم
    PrimaryActorTick.bCanEverTick = true;

    // ایجاد یک کامپوننت StaticMesh که مدل سه‌بعدی آیتم را نگه می‌دارد.
   // "ItemMesh" نامی است که به این کامپوننت داده شده است.
    ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
    // تعیین این که RootComponent این Actor کامپوننت ItemMesh باشد.
    RootComponent = ItemMesh;

    // ایجاد یک کامپوننت SphereComponent که برای برخورد استفاده می‌شود.
    Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    // متصل کردن Sphere به RootComponent (یعنی ItemMesh).
    Sphere->SetupAttachment(RootComponent);
    // تعیین شعاع Sphere.
    Sphere->SetSphereRadius(50.f);
}

// تابعی که در ابتدای بازی اجرا می‌شود
void AItem::BeginPlay()
{
    // فراخوانی تابع BeginPlay والد
    Super::BeginPlay();

    // فعال کردن برخورد فقط برای پرس‌و‌جو، یعنی فقط برای بررسی برخوردها.
    Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    // تعیین نوع شیء برای برخورد که در اینجا به نوع "WorldDynamic" تنظیم شده.
    Sphere->SetCollisionObjectType(ECC_WorldDynamic);
    // تعیین واکنش به تمامی کانال‌های برخورد به طوری که همه‌ی برخوردها نادیده گرفته شوند.
    Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    // تعیین این که اگر بازیگر دیگری (مانند بازیکن) به Sphere برخورد کند، این برخورد باید شناسایی شود.
    Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // اتصال تابع OnSphereOverlap به رویداد شروع برخورد
    Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
    // اتصال تابع OnSphereEndOverlap به رویداد پایان برخورد
    Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

// تابع Tick که در هر فریم اجرا می‌شود
void AItem::Tick(float DeltaTime)
{
    // فراخوانی تابع Tick والد
    Super::Tick(DeltaTime);

    // افزایش مقدار RunningTime با گذشت زمان (برای حرکت پیوسته)
    RunningTime += DeltaTime;

    // محاسبه تغییر در محور Z با استفاده از تابع سینوس برای حرکت بالا و پایین
    float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);

    // اعمال تغییر در موقعیت آیتم در محور Z
    AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
}

// تابعی که هنگام شروع برخورد با Sphere اجرا می‌شود
void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    // نمایش یک پیام دیباگ زمانی که یک برخورد شروع می‌شود
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap Begin"));
    }
}

// تابعی که هنگام پایان برخورد با Sphere اجرا می‌شود
void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    // نمایش یک پیام دیباگ زمانی که یک برخورد تمام می‌شود
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
    }
}














/*CreateDefaultSubobject چیست؟

این متد برای ایجاد کامپوننت‌ها (اجزای مختلف شیء) استفاده می‌شود. در اینجا، UStaticMeshComponent و USphereComponent ایجاد شده‌اند.
RootComponent چیست؟

RootComponent کامپوننت اصلی (یا ریشه) از یک Actor است. همه‌ی کامپوننت‌های دیگر باید به این ریشه متصل شوند. در اینجا، ItemMesh به‌عنوان ریشه تنظیم شده است.
SetupAttachment چیست؟

این متد برای متصل کردن کامپوننت‌ها به یکدیگر استفاده می‌شود. در اینجا، Sphere به RootComponent متصل شده است.
SetCollisionEnabled و SetCollisionObjectType و سایر متدهای مربوط به برخورد:

این متدها برای کنترل برخورد‌ها (Collision) استفاده می‌شوند. در اینجا، آیتم فقط زمانی که شخصیت‌ها (Pawns) به آن برخورد می‌کنند، واکنش نشان می‌دهد.
AddOnScreenDebugMessage چیست؟

این متد برای نمایش پیام‌های دیباگ (Debug) روی صفحه استفاده می‌شود. این پیام‌ها می‌توانند برای اشکال‌زدایی و بررسی دقیق‌تر کد مفید باشند.
FVector و AddActorWorldOffset:

FVector(0.f, 0.f, DeltaZ) یک بردار سه‌بعدی است که فقط تغییرات محور Z را اعمال می‌کند.
AddActorWorldOffset موقعیت جهانی (Global Position) یک شیء را به‌روزرسانی می‌کند.
FMath::Sin چیست؟

این تابع برای محاسبه سینوس یک زاویه استفاده می‌شود. در اینجا، برای حرکت آیتم به‌صورت نوسانی (up and down) استفاده شده است.
*/