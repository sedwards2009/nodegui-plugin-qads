#pragma once

#include <napi.h>

#include <QPointer>

#include "QtWidgets/QFrame/qframe_macro.h"

#include "Extras/Export/export.h"
#include "ncdockareawidget.hpp"
#include "DockAreaWidget.h"

class CDockAreaWidgetWrap : public Napi::ObjectWrap<CDockAreaWidgetWrap> {
  QFRAME_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<ads::CDockAreaWidget> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  CDockAreaWidgetWrap(const Napi::CallbackInfo& info);
  ~CDockAreaWidgetWrap();
  ads::CDockAreaWidget* getInternalInstance();
  // class constructor
  static Napi::FunctionReference constructor;
  // wrapped methods
  Napi::Value setAllowedAreas(const Napi::CallbackInfo& info);
  Napi::Value titleBar(const Napi::CallbackInfo& info);
  Napi::Value dockManager(const Napi::CallbackInfo& info);
  Napi::Value dockContainer(const Napi::CallbackInfo& info);
  Napi::Value titleBarGeometry(const Napi::CallbackInfo& info);
  Napi::Value contentAreaGeometry(const Napi::CallbackInfo& info);
  Napi::Value dockWidgetsCount(const Napi::CallbackInfo& info);
  Napi::Value openDockWidgetsCount(const Napi::CallbackInfo& info);
  Napi::Value currentIndex(const Napi::CallbackInfo& info);
  Napi::Value indexOfFirstOpenDockWidget(const Napi::CallbackInfo& info);
  Napi::Value setCurrentIndex(const Napi::CallbackInfo& info);
  Napi::Value closeArea(const Napi::CallbackInfo& info);
  Napi::Value closeOtherAreas(const Napi::CallbackInfo& info);
  Napi::Value isCentralWidgetArea(const Napi::CallbackInfo& info);
  Napi::Value dockWidgets(const Napi::CallbackInfo& info);
  Napi::Value openedDockWidgets(const Napi::CallbackInfo& info);
  Napi::Value dockWidget(const Napi::CallbackInfo& info);
  Napi::Value currentDockWidget(const Napi::CallbackInfo& info);
  Napi::Value setCurrentDockWidget(const Napi::CallbackInfo& info);
  Napi::Value features(const Napi::CallbackInfo& info);
  Napi::Value allowedAreas(const Napi::CallbackInfo& info);
  Napi::Value dockAreaFlags(const Napi::CallbackInfo& info);
  Napi::Value titleBarButton(const Napi::CallbackInfo& info);
  Napi::Value setDockAreaFlag(const Napi::CallbackInfo& info);
};
