#include "PMilestone.h"
#include "BreakableBrick.h"
#include "ConsumableCoin.h"

PMilestone::PMilestone() {
	this->setState(PMILESTONE_STATE_HIDDEN);
}

void PMilestone::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) {
	if (this->State == PMILESTONE_STATE_PROVOKED) {
		this->Triggered_time = GetTickCount();
		for (int i = 0; i < coObjects->size() ; i++) {
			if (dynamic_cast<BreakableBrick*>(coObjects->at(i))) {
				BreakableBrick* brick = dynamic_cast<BreakableBrick*>(coObjects->at(i));
				float brick_x, brick_y;
				brick->GetLocation(brick_x, brick_y);
				if (brick_x >= 1945 && brick_x < 2135 && brick_y >= 300 && brick_y < 420) {
					brick->setState(BRICK_STATE_BROKEN);
					LPGAMEOBJECT coin = new ConsumableCoin();
					Cgame::GetInstance()->GetCurrentScene()->AddGameObject(coin,brick_x,brick_y,COIN_ANI_SET);
				}
			}
		}
		this->setState(PMILESTONE_STATE_DOWN);
	}
	else if (this->State == PMILESTONE_STATE_DOWN) {
		if (GetTickCount() - this->Triggered_time > 5000) {
			for (int i = 0; i < coObjects->size(); i++) {
				if (dynamic_cast<ConsumableCoin*>(coObjects->at(i))) {
					ConsumableCoin* coin = dynamic_cast<ConsumableCoin*>(coObjects->at(i));
					float coin_x, coin_y;
					coin->GetLocation(coin_x, coin_y);
					if (coin_x >= 1945 && coin_x < 2135 && coin_y >= 300 && coin_y < 400) {
						coin->setState(BRICK_STATE_BROKEN);
						LPGAMEOBJECT brick = new BreakableBrick();
						Cgame::GetInstance()->GetCurrentScene()->AddGameObject(brick, coin_x, coin_y, BRICK_ANI_SET);
					}
				}
			}
		}
	}
}

void PMilestone::Render() {
	int ani = -1;
	if (this->State == PMILESTONE_STATE_HIDDEN) ani = PMILESTONE_ANI_HIDDEN;
	else if (this->State == PMILESTONE_STATE_UP) ani = PMILESTONE_ANI_UP;
	else if (this->State == PMILESTONE_STATE_DOWN || this->State == PMILESTONE_STATE_PROVOKED) ani = PMILESTONE_ANI_DOWN;
	this->Animation_Set->at(ani)->Render(x, y);
}

void PMilestone::setState(int State) {
	this->State = State;
	switch (State)
	{
	case PMILESTONE_STATE_UP:
		this->y -= 17;
		break;
	case PMILESTONE_STATE_PROVOKED:
		this->y += 17;
		break;
 	default:
		break;
	}
}

void PMilestone::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	
	left = this->x;
	top = this->y;
	if (this->State == PMILESTONE_STATE_UP) {
		right = x + PMILESTONE_UP_WIDTH;
		bottom = y + PMILESTONE_UP_HEIGHT;
	}
	else {
		right = x + PMILESTONE_HIDDEN_WIDTH;
		bottom = y + PMILESTONE_HIDDEN_HEIGHT;
	}
	
}