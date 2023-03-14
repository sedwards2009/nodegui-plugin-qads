#pragma once

#include "DockManager.h"

#include "Extras/Export/export.h"
#include "QtWidgets/QFrame/qframe_macro.h"
#include "core/NodeWidget/nodewidget.h"

class DLL_EXPORT NCDockManager : public ads::CDockManager, public NodeWidget {
  Q_OBJECT
  NODEWIDGET_IMPLEMENTATIONS(CDockManager)
 public:
  using ads::CDockManager::CDockManager;  // inherit all constructors

  virtual void connectSignalsToEventEmitter() {
    QFRAME_SIGNALS
    // QObject::connect(this, &QLabel::linkActivated, [=](const QString& link) {
    //   Napi::Env env = this->emitOnNode.Env();
    //   Napi::HandleScope scope(env);
    //   this->emitOnNode.Call({Napi::String::New(env, "linkActivated"),
    //                          Napi::String::New(env, link.toStdString())});
    // });
    // QObject::connect(this, &QLabel::linkHovered, [=](const QString& link) {
    //   Napi::Env env = this->emitOnNode.Env();
    //   Napi::HandleScope scope(env);
    //   this->emitOnNode.Call({Napi::String::New(env, "linkHovered"),
    //                          Napi::String::New(env, link.toStdString())});
    // });
  }
};
