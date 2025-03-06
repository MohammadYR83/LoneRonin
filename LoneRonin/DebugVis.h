#pragma once
#include "DrawDebugHelpers.h"

#define DrawSphere if (GetWorld()) DrawDebugSphere(GetWorld(),GetActorLocation(),25.f,24,FColor::Red)
#define DrawLine if (GetWorld()) DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation()+GetActorForwardVector()*100.f,FColor::Blue)
#define DrawPoint if (GetWorld()) DrawDebugPoint(GetWorld(),GetActorLocation()+GetActorForwardVector()*100.f,15.f,FColor::Red)
#define DrawVector if (GetWorld()) \
{ \
DrawLine; \
DrawPoint; \
}