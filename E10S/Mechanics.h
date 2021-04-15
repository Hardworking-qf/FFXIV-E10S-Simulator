#pragma once
#include <random>
#include <time.h>
#include "Rect.h"
#include "Base.h"

int* randomArr();

void SetSafeZone(int safe_dire, bool placeShadow = false);

void FrontBack();
void LeftRight();
void PlaceShadow();

void FrontBack4();
void LeftRight4();
void PlaceShadow2();