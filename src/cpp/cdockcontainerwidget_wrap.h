#pragma once

#include <napi.h>

#include <QPointer>

#include "Extras/Export/export.h"
#include "QtWidgets/QFrame/qframe_macro.h"
#include "QtWidgets/QWidget/qwidget_macro.h"
#include "ncdockcontainerwidget.hpp"
#include "DockContainerWidget.h"

class DLL_EXPORT CDockContainerWidgetWrap : public Napi::ObjectWrap<CDockContainerWidgetWrap> {
  QFRAME_WRAPPED_METHODS_DECLARATION
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
  // Napi::Value setSelection(const Napi::CallbackInfo& info);
  // Napi::Value selectionStart(const Napi::CallbackInfo& info);
  // Napi::Value setBuddy(const Napi::CallbackInfo& info);
  // Napi::Value buddy(const Napi::CallbackInfo& info);
  // Napi::Value clear(const Napi::CallbackInfo& info);
  // Napi::Value setMovie(const Napi::CallbackInfo& info);
  // Napi::Value setNumDouble(const Napi::CallbackInfo& info);
  // Napi::Value setNumInt(const Napi::CallbackInfo& info);
  // Napi::Value setPicture(const Napi::CallbackInfo& info);
  // Napi::Value setPixmap(const Napi::CallbackInfo& info);
};
