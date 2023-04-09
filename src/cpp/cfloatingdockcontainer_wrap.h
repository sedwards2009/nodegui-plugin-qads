#pragma once

#include <napi.h>

#include <QPointer>

#include "QtWidgets/QWidget/qwidget_macro.h"

#include "Extras/Export/export.h"
#include "FloatingDockContainer.h"

class CFloatingDockContainerWrap : public Napi::ObjectWrap<CFloatingDockContainerWrap> {
  QWIDGET_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<ads::CFloatingDockContainer> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  CFloatingDockContainerWrap(const Napi::CallbackInfo& info);
  ~CFloatingDockContainerWrap();
  ads::CFloatingDockContainer* getInternalInstance();

  // class constructor
  static Napi::FunctionReference constructor;
  // wrapped methods
  Napi::Value dockContainer(const Napi::CallbackInfo& info);
  Napi::Value isClosable(const Napi::CallbackInfo& info);
  Napi::Value hasTopLevelDockWidget(const Napi::CallbackInfo& info);
  Napi::Value topLevelDockWidget(const Napi::CallbackInfo& info);
  Napi::Value dockWidgets(const Napi::CallbackInfo& info);

};
