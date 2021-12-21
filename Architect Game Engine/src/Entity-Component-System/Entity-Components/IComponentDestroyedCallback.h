#pragma once

struct IComponentDestroyedCallback
{
	virtual void OnDestroy() = 0;
};