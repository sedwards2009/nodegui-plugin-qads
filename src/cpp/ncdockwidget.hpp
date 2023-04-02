#pragma once

#include "DockWidget.h"

#include "Extras/Export/export.h"
#include "QtWidgets/QFrame/qframe_macro.h"
#include "core/NodeWidget/nodewidget.h"

class NCDockWidget : public ads::CDockWidget, public NodeWidget {
  Q_OBJECT
  NODEWIDGET_IMPLEMENTATIONS(CDockWidget)
 public:
  using ads::CDockWidget::CDockWidget;  // inherit all constructors

  virtual void connectSignalsToEventEmitter() {
    QFRAME_SIGNALS

    QObject::connect(this, &ads::CDockWidget::viewToggled, [=](bool open) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "viewToggled"),
                             Napi::Boolean::New(env, open)});
    });

    QObject::connect(this, &ads::CDockWidget::closed, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "closed")});
    });

    QObject::connect(this, &ads::CDockWidget::titleChanged, [=](const QString &title) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "titleChanged"),
                             Napi::Value::From(env, title.toStdString())});
    });

    QObject::connect(this, &ads::CDockWidget::topLevelChanged, [=](bool topLevel) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "topLevelChanged"),
                             Napi::Boolean::New(env, topLevel)});
    });

    QObject::connect(this, &ads::CDockWidget::closeRequested, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "closeRequested")});
    });

    QObject::connect(this, &ads::CDockWidget::visibilityChanged, [=](bool visible) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "visibilityChanged"),
                             Napi::Boolean::New(env, visible)});
    });

    QObject::connect(this, &ads::CDockWidget::featuresChanged, [=](ads::CDockWidget::DockWidgetFeatures features) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "featuresChanged"),
                             Napi::Number::New(env, features)});
    });
  }
};
