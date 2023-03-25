#pragma once

#include <napi.h>

#include <QPointer>

#include "Extras/Export/export.h"
#include "DockContainerWidget.h"
#include "DockAreaWidget.h"
#include "ncdockcontainerwidget.hpp"
#include "cdockcontainerwidget_macro.h"


class DLL_EXPORT CDockContainerWidgetWrap : public Napi::ObjectWrap<CDockContainerWidgetWrap> {

  CDOCKCONTAINERWIDGET_WRAPPED_METHODS_DECLARATION

 private:
  QPointer<ads::CDockContainerWidget> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  CDockContainerWidgetWrap(const Napi::CallbackInfo& info);
  ~CDockContainerWidgetWrap();
  ads::CDockContainerWidget* getInternalInstance();
  // class constructor
  static Napi::FunctionReference constructor;
  // wrapped methods

};
