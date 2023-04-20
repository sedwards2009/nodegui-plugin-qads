#pragma once

#include <napi.h>

#include <QPointer>

#include "QtWidgets/QFrame/qframe_macro.h"

#include "Extras/Export/export.h"
#include "DockWidgetTab.h"


class CDockWidgetTabWrap : public Napi::ObjectWrap<CDockWidgetTabWrap> {
  QFRAME_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<ads::CDockWidgetTab> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  CDockWidgetTabWrap(const Napi::CallbackInfo& info);
  ~CDockWidgetTabWrap();
  ads::CDockWidgetTab* getInternalInstance();
  Napi::Value dockAreaWidget(const Napi::CallbackInfo& info);
  Napi::Value dockWidget(const Napi::CallbackInfo& info);
  Napi::Value isActiveTab(const Napi::CallbackInfo& info);
  Napi::Value setActiveTab(const Napi::CallbackInfo& info);
  Napi::Value text(const Napi::CallbackInfo& info);
  Napi::Value setText(const Napi::CallbackInfo& info);
  Napi::Value isTitleElided(const Napi::CallbackInfo& info);
  Napi::Value isClosable(const Napi::CallbackInfo& info);
  Napi::Value setElideMode(const Napi::CallbackInfo& info);
  Napi::Value updateStyle(const Napi::CallbackInfo& info);
  Napi::Value iconSize(const Napi::CallbackInfo& info);
  Napi::Value setIconSize(const Napi::CallbackInfo& info);
  Napi::Value setIcon(const Napi::CallbackInfo& info);
  Napi::Value icon(const Napi::CallbackInfo& info);

  // class constructor
  static Napi::FunctionReference constructor;
};
