#include "Mechanics.h"


int* randomArr() {
	int* arr = new int[4]{ 0,1,2,3 };
	for (int i = 3; i > 0; --i) {
		int j = rand() % 4;
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	return arr;
}

extern Player player;
extern Boss boss;

void (*DrawMechanics)(void);
time_t currT, lastT, deltaT, MechanicsStartT;
Rect safeZone = Rect{ {0,0},{1,1} };
void SetSafeZone(int safe_dire, bool placeShadow) {
	if (placeShadow) {
		switch (safe_dire) {
		case NORTH: safeZone = Rect{ {.25,1},{.75,.6} }; break;
		case SOUTH:safeZone = Rect{ {.25,0},{.75,.4} }; break;
		case WEST:safeZone = Rect{ {0,.25},{.4,.75} }; break;
		case EAST:safeZone = Rect{ {.6,.25 }, { 1,.75 } }; break;
		default:safeZone = Rect{ {0,0},{0,0} }; break;
		}
	}
	else {
		switch (safe_dire) {
		case NORTH: safeZone = Rect{ {0,1},{1,.5} }; break;
		case SOUTH:safeZone = Rect{ {0,0},{1,.5} }; break;
		case WEST:safeZone = Rect{ {0,0},{.5,1} }; break;
		case EAST:safeZone = Rect{ {.5,0 }, { 1,1 } }; break;
		default:safeZone = Rect{ {0,0},{0,0} }; break;
		}
	}
}

// 前后刀
void FrontBack() {
	srand(clock());
	boss.ATK_DIRE = rand() % 2*2;
	boss.FACE_DIRE = rand() % 4;
	boss.SHADOW_DIRE = rand() % 4;
	int safe_dire = (boss.ATK_DIRE + boss.SHADOW_DIRE)%4;
	SetSafeZone(safe_dire);
	MechanicsStartT = currT;
	DrawMechanics = []() {
		if (currT - MechanicsStartT >= 3000) {
			glColor3f(.2, 0, 0);
			DrawRect(Vector2Df{ 0,0 }, Vector2Df{ 1,1 });
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
	};
}

// 左右刀
void LeftRight() {
	srand(clock());
	boss.ATK_DIRE = rand() % 2 * 2+1;
	boss.FACE_DIRE = rand() % 4;
	boss.SHADOW_DIRE = rand() % 4;
	int safe_dire = (boss.ATK_DIRE + boss.SHADOW_DIRE) % 4;
	SetSafeZone(safe_dire);
	MechanicsStartT = currT;
	DrawMechanics = []() {
		if (currT - MechanicsStartT >= 3000) {
			glColor3f(.2, 0, 0);
			DrawRect(Vector2Df{ 0,0 }, Vector2Df{ 1,1 });
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
	};
}

 // 放影子
void PlaceShadow() {
	srand(clock());
	boss.ATK_DIRE = rand() % 2 * 2 + 1;
	boss.FACE_DIRE = rand() % 4;
	player.SHADOW_DIRE = rand() % 4;
	int safe_dire = (boss.ATK_DIRE + player.SHADOW_DIRE + 2) % 4;
	SetSafeZone(safe_dire, true);
	MechanicsStartT = currT;
	DrawMechanics = []() {
		if (currT - MechanicsStartT >= 3000) {
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
	};
}

int* shadowArr;
void FrontBack4(){
	srand(clock());
	boss.ATK_DIRE = rand() % 2 * 2;
	boss.FACE_DIRE = rand() % 4;
	shadowArr = randomArr();
	MechanicsStartT = currT;
	DrawMechanics = []() {
		glColor3f(.2, 0, 0);
		if (currT - MechanicsStartT <=3000) {
			boss.SHADOW_DIRE = shadowArr[0];
		}
		else if (currT - MechanicsStartT <= 4500) {// 第一次区域&第二次影子显示
			boss.SHADOW_DIRE = shadowArr[1];
			int safe_dire = (boss.ATK_DIRE + shadowArr[0]) % 4;
			SetSafeZone(safe_dire);
			DrawRect(Vector2Df{ 0,0 }, Vector2Df{ 1,1 });
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
		else if (currT - MechanicsStartT <= 6000) {
			boss.SHADOW_DIRE = shadowArr[2];
			int safe_dire = (boss.ATK_DIRE + shadowArr[1]) % 4;
			SetSafeZone(safe_dire);
			DrawRect(Vector2Df{ 0,0 }, Vector2Df{ 1,1 });
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
		else if(currT - MechanicsStartT <= 7500) {
			boss.SHADOW_DIRE = shadowArr[3];
			int safe_dire = (boss.ATK_DIRE + shadowArr[2]) % 4;
			SetSafeZone(safe_dire);
			DrawRect(Vector2Df{ 0,0 }, Vector2Df{ 1,1 });
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
		else {
			int safe_dire = (boss.ATK_DIRE + boss.SHADOW_DIRE) % 4;
			SetSafeZone(safe_dire);
			DrawRect(Vector2Df{ 0,0 }, Vector2Df{ 1,1 });
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
	};
}

void LeftRight4() {
	srand(clock());
	boss.ATK_DIRE = rand() % 2 * 2 + 1;
	boss.FACE_DIRE = rand() % 4;
	shadowArr = randomArr();
	MechanicsStartT = currT;
	DrawMechanics = []() {
		glColor3f(.2, 0, 0);
		if (currT - MechanicsStartT <= 3000) {
			boss.SHADOW_DIRE = shadowArr[0];
		}
		else if (currT - MechanicsStartT <= 4500) {// 第一次区域&第二次影子显示
			boss.SHADOW_DIRE = shadowArr[1];
			int safe_dire = (boss.ATK_DIRE + shadowArr[0]) % 4;
			SetSafeZone(safe_dire);
			DrawRect(Vector2Df{ 0,0 }, Vector2Df{ 1,1 });
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
		else if (currT - MechanicsStartT <= 6000) {
			boss.SHADOW_DIRE = shadowArr[2];
			int safe_dire = (boss.ATK_DIRE + shadowArr[1]) % 4;
			SetSafeZone(safe_dire);
			DrawRect(Vector2Df{ 0,0 }, Vector2Df{ 1,1 });
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
		else if (currT - MechanicsStartT <= 7500) {
			boss.SHADOW_DIRE = shadowArr[3];
			int safe_dire = (boss.ATK_DIRE + shadowArr[2]) % 4;
			SetSafeZone(safe_dire);
			DrawRect(Vector2Df{ 0,0 }, Vector2Df{ 1,1 });
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
		else {
			int safe_dire = (boss.ATK_DIRE + boss.SHADOW_DIRE) % 4;
			SetSafeZone(safe_dire);
			DrawRect(Vector2Df{ 0,0 }, Vector2Df{ 1,1 });
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
	};
}

bool secondFin = false;
void PlaceShadow2() {
	srand(clock());
	secondFin = false;
	boss.ATK_DIRE = rand() % 2 * 2 + 1;
	boss.FACE_DIRE = rand() % 4;
	player.SHADOW_DIRE = rand() % 4;
	int safe_dire = (boss.ATK_DIRE + player.SHADOW_DIRE + 2) % 4;
	SetSafeZone(safe_dire, true);
	MechanicsStartT = currT;
	DrawMechanics = []() {
		if (currT - MechanicsStartT <= 3000) {

		}
		else if (currT - MechanicsStartT <= 6000) {
			glColor3f(0, 1, 0);
			DrawRect(safeZone.a, safeZone.b);
		}
		else {
			if (!secondFin) {
				boss.ATK_DIRE = rand() % 2 * 2 + 1;
				// boss.FACE_DIRE = rand() % 4; 面向不改变
				player.SHADOW_DIRE = rand() % 4;
				int safe_dire = (boss.ATK_DIRE + player.SHADOW_DIRE + 2) % 4;
				SetSafeZone(safe_dire, true);
				MechanicsStartT = currT;
				DrawMechanics = []() {
					if (currT - MechanicsStartT >= 3000) {
						glColor3f(0, 1, 0);
						DrawRect(safeZone.a, safeZone.b);
					}
				};
			}
			secondFin = true;
		}
	};
}