#pragma once

#include <napi.h>

#include <QPointer>

#include "QtWidgets/QFrame/qframe_macro.h"

#include "Extras/Export/export.h"
#include "ncdockwidget.hpp"
#include "DockWidget.h"

class DLL_EXPORT CDockWidgetWrap : public Napi::ObjectWrap<CDockWidgetWrap> {
  QFRAME_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<ads::CDockWidget> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  CDockWidgetWrap(const Napi::CallbackInfo& info);
  ~CDockWidgetWrap();
  ads::CDockWidget* getInternalInstance();
  // class constructor
  static Napi::FunctionReference constructor;
  // wrapped methods
  Napi::Value setFeature(const Napi::CallbackInfo& info);
  Napi::Value features(const Napi::CallbackInfo& info);
  Napi::Value setWidget(const Napi::CallbackInfo& info);
  Napi::Value takeWidget(const Napi::CallbackInfo& info);
  Napi::Value setToggleViewActionMode(const Napi::CallbackInfo& info);
  Napi::Value setTabToolTip(const Napi::CallbackInfo& info);
  Napi::Value widget(const Napi::CallbackInfo& info);
  Napi::Value isFloating(const Napi::CallbackInfo& info);
  Napi::Value isInFloatingContainer(const Napi::CallbackInfo& info);
  Napi::Value isClosed(const Napi::CallbackInfo& info);
  Napi::Value isCentralWidget(const Napi::CallbackInfo& info);
  Napi::Value isFullScreen(const Napi::CallbackInfo& info);
  Napi::Value isTabbed(const Napi::CallbackInfo& info);
  Napi::Value isCurrentTab(const Napi::CallbackInfo& info);
  Napi::Value toggleView(const Napi::CallbackInfo& info);
  Napi::Value setAsCurrentTab(const Napi::CallbackInfo& info);
  Napi::Value setFloating(const Napi::CallbackInfo& info);
  Napi::Value deleteDockWidget(const Napi::CallbackInfo& info);
  Napi::Value closeDockWidget(const Napi::CallbackInfo& info);
  Napi::Value setMinimumSizeHintMode(const Napi::CallbackInfo& info);
  Napi::Value dockManager(const Napi::CallbackInfo& info);
  Napi::Value dockContainer(const Napi::CallbackInfo& info);
  Napi::Value dockAreaWidget(const Napi::CallbackInfo& info);
};
