#pragma once

#include <napi.h>

#include <QPointer>

#include "QtWidgets/QSplitter/qsplitter_macro.h"

#include "Extras/Export/export.h"

#include "DockSplitter.h"

class CDockSplitterWrap : public Napi::ObjectWrap<CDockSplitterWrap> {
  QSPLITTER_WRAPPED_METHODS_DECLARATION
 private:
  QPointer<ads::CDockSplitter> instance;

 public:
  static Napi::Object init(Napi::Env env, Napi::Object exports);
  CDockSplitterWrap(const Napi::CallbackInfo& info);
  ~CDockSplitterWrap();
  ads::CDockSplitter* getInternalInstance();
  // class constructor
  static Napi::FunctionReference constructor;
  // wrapped methods
};
