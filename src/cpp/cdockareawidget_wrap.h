#pragma once

#include <napi.h>

#include <QPointer>

#include "QtWidgets/QFrame/qframe_macro.h"

#include "Extras/Export/export.h"
#include "ncdockareawidget.hpp"
#include "DockAreaWidget.h"

class DLL_EXPORT CDockAreaWidgetWrap : public Napi::ObjectWrap<CDockAreaWidgetWrap> {
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

  // Napi::Value setWidget(const Napi::CallbackInfo& info);
  // Napi::Value takeWidget(const Napi::CallbackInfo& info);
  // Napi::Value setToggleViewActionMode(const Napi::CallbackInfo& info);

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
