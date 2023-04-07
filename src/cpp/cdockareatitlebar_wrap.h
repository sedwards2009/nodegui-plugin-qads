#pragma once

#include <napi.h>

#include <QPointer>

#include "QtWidgets/QFrame/qframe_macro.h"

#include "Extras/Export/export.h"
#include "DockAreaTitleBar.h"
#include "ncdockareatitlebar.hpp"

class CDockAreaTitleBarWrap : public Napi::ObjectWrap<CDockAreaTitleBarWrap> {
  QFRAME_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<ads::CDockAreaTitleBar> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  CDockAreaTitleBarWrap(const Napi::CallbackInfo& info);
  ~CDockAreaTitleBarWrap();
  ads::CDockAreaTitleBar* getInternalInstance();
  Napi::Value insertWidget(const Napi::CallbackInfo& info);
  Napi::Value indexOf(const Napi::CallbackInfo& info);
  Napi::Value tabBar(const Napi::CallbackInfo& info);
  Napi::Value button(const Napi::CallbackInfo& info);
  Napi::Value updateDockWidgetActionsButtons(const Napi::CallbackInfo& info);
  Napi::Value titleBarButtonToolTip(const Napi::CallbackInfo& info);

  // class constructor
  static Napi::FunctionReference constructor;
};
