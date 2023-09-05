#pragma once
#include "LineMesh.h"

class UIManager
{
	DECLARE_SINGLE(UIManager);

public:
	void Init();
	void Render(HDC hdc);

private:
	void				RenderBackground(HDC hdc);
	void				RenderWind(HDC hdc);
	void				RenderPower(HDC hdc);
	void				RenderStamina(HDC hdc);
	void				RenderTime(HDC hdc);
	void				RenderAngle(HDC hdc);
	void				RenderWeaponChoice(HDC hdc);
	void				RenderMiniMap(HDC hdc);

public:
	void				SetWindPercent(float windPercent) { _windPercent = windPercent; }
	void				SetPowerPercent(float powerPercent) { _powerPercent = powerPercent; }
	void				SetStaminaPercent(float staminaPercent) { _staminaPercent = staminaPercent; }
	void				SetPlayerAngle(float angle) { _playerAngle = angle;}
	void				SetBarrelAngle(float angle) { _barrelAngle = angle;}
	void				SetSpecialWeapon(bool specialWeapon) { _specialWeapon = specialWeapon; }
	void				SetRemainTime(int32 remainTime) { _remainTime = remainTime; }

	float				GetWindPercent() { return _windPercent; }
	float				GetPowerPercent() { return _powerPercent; }
	float				GetStaminaPercent() { return _staminaPercent; }
	float				GetPlayerAngle() { return _playerAngle; }
	float				GetBarrelAngle() { return _barrelAngle; }
	bool				GetSpecialWeapon() { return _specialWeapon; }
	int32				GetRemainTime() { return _remainTime; }

private:
	float				_windPercent = 0; // [-100~100]
	float				_powerPercent = 0;
	float				_staminaPercent = 0;
	float				_playerAngle = 0;
	float				_barrelAngle = 0;
	bool				_specialWeapon = false;
	int32				_remainTime = 0;
};

