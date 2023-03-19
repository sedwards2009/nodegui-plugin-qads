#pragma once

#include "DockAreaWidget.h"

#include "Extras/Export/export.h"
#include "QtWidgets/QFrame/qframe_macro.h"
#include "core/NodeWidget/nodewidget.h"

class DLL_EXPORT NCDockAreaWidget : public ads::CDockAreaWidget, public NodeWidget {
  Q_OBJECT
  NODEWIDGET_IMPLEMENTATIONS(CDockAreaWidget)
 public:
  using ads::CDockAreaWidget::CDockAreaWidget;  // inherit all constructors

  virtual void connectSignalsToEventEmitter() {
    QFRAME_SIGNALS

    QObject::connect(this, &ads::CDockAreaWidget::tabBarClicked, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "tabBarClicked"),
                             Napi::Number::New(env, index)});
    });

    QObject::connect(this, &ads::CDockAreaWidget::currentChanging, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "currentChanging"),
                             Napi::Number::New(env, index)});
    });

    QObject::connect(this, &ads::CDockAreaWidget::currentChanged, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "currentChanged"),
                             Napi::Number::New(env, index)});
    });

    QObject::connect(this, &ads::CDockAreaWidget::viewToggled, [=](bool open) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "viewToggled"),
                             Napi::Boolean::New(env, open)});
    });
  }
};
