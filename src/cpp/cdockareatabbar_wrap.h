#pragma once

#include <napi.h>

#include <QPointer>

#include "QtWidgets/QFrame/qframe_macro.h"

#include "Extras/Export/export.h"
#include "DockAreaTabBar.h"
#include "ncdockareatabbar.hpp"

class DLL_EXPORT CDockAreaTabBarWrap : public Napi::ObjectWrap<CDockAreaTabBarWrap> {
  QFRAME_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<ads::CDockAreaTabBar> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  CDockAreaTabBarWrap(const Napi::CallbackInfo& info);
  ~CDockAreaTabBarWrap();
  ads::CDockAreaTabBar* getInternalInstance();

  // class constructor
  static Napi::FunctionReference constructor;
  // wrapped methods
  // Napi::Value selectionStart(const Napi::CallbackInfo& info);
};
