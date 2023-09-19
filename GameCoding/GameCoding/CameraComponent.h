#pragma once
#include "Component.h"

class CameraComponent : public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent() override;
	virtual void Render(HDC hdc) override;

};

