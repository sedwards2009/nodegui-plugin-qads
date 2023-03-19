#pragma once

#include <napi.h>

#include <QPointer>

#include "QtWidgets/QFrame/qframe_macro.h"

#include "Extras/Export/export.h"
#include "ncdockmanager.hpp"
#include "DockManager.h"

class DLL_EXPORT CDockManagerWrap : public Napi::ObjectWrap<CDockManagerWrap> {
  QFRAME_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<ads::CDockManager> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  CDockManagerWrap(const Napi::CallbackInfo& info);
  ~CDockManagerWrap();
  ads::CDockManager* getInternalInstance();
  // class constructor
  static Napi::FunctionReference constructor;
  // wrapped methods
  Napi::Value addDockWidget(const Napi::CallbackInfo& info);
	Napi::Value addDockWidgetToContainer(const Napi::CallbackInfo& info);
	Napi::Value addDockWidgetTab(const Napi::CallbackInfo& info);
	Napi::Value addDockWidgetTabToArea(const Napi::CallbackInfo& info);
	Napi::Value findDockWidget(const Napi::CallbackInfo& info);
	Napi::Value removeDockWidget(const Napi::CallbackInfo& info);
};

namespace StaticCDockManagerWrapMethods {
  DLL_EXPORT Napi::Value setConfigFlag(const Napi::CallbackInfo& info);
}
