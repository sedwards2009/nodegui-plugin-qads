#pragma once

#include <napi.h>

#include <QPointer>

#include "QtWidgets/QFrame/qframe_macro.h"

#include "Extras/Export/export.h"
#include "DockAreaTitleBar.h"
#include "ncdockareatitlebar.hpp"

class DLL_EXPORT CDockAreaTitleBarWrap : public Napi::ObjectWrap<CDockAreaTitleBarWrap> {
  QFRAME_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<ads::CDockAreaTitleBar> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  CDockAreaTitleBarWrap(const Napi::CallbackInfo& info);
  ~CDockAreaTitleBarWrap();
  ads::CDockAreaTitleBar* getInternalInstance();
  // class constructor
  static Napi::FunctionReference constructor;
  // wrapped methods
  // Napi::Value selectionStart(const Napi::CallbackInfo& info);
};
