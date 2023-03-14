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
