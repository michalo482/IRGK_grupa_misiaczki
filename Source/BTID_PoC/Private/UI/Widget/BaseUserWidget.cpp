// Copyright Misiaczki IRGK_WSEI


#include "UI/Widget/BaseUserWidget.h"

void UBaseUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
