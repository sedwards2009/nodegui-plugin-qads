#pragma once

#include "DockAreaTabBar.h"

#include "Extras/Export/export.h"
#include "QtWidgets/QFrame/qframe_macro.h"
#include "core/NodeWidget/nodewidget.h"


class DLL_EXPORT NCDockAreaTabBar : public ads::CDockAreaTabBar, public NodeWidget {
  Q_OBJECT
  NODEWIDGET_IMPLEMENTATIONS(CDockAreaTabBar)
 public:
  using ads::CDockAreaTabBar::CDockAreaTabBar;  // inherit all constructors

  virtual void connectSignalsToEventEmitter() {
    QFRAME_SIGNALS

    QObject::connect(this, &ads::CDockAreaTabBar::currentChanging, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "currentChanging"),
                             Napi::Number::New(env, index)});
    });

    QObject::connect(this, &ads::CDockAreaTabBar::currentChanged, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "currentChanged"),
                             Napi::Number::New(env, index)});
    });

    QObject::connect(this, &ads::CDockAreaTabBar::tabBarClicked, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "tabBarClicked"),
                             Napi::Number::New(env, index)});
    });

    QObject::connect(this, &ads::CDockAreaTabBar::tabCloseRequested, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "tabCloseRequested"),
                             Napi::Number::New(env, index)});
    });

    QObject::connect(this, &ads::CDockAreaTabBar::tabClosed, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "tabClosed"),
                             Napi::Number::New(env, index)});
    });

    QObject::connect(this, &ads::CDockAreaTabBar::tabOpened, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "tabOpened"),
                             Napi::Number::New(env, index)});
    });

    QObject::connect(this, &ads::CDockAreaTabBar::tabMoved, [=](int from, int to) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "tabMoved"),
                             Napi::Number::New(env, from),
                             Napi::Number::New(env, to)});
    });

    QObject::connect(this, &ads::CDockAreaTabBar::removingTab, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "removingTab"),
                             Napi::Number::New(env, index)});
    });

    QObject::connect(this, &ads::CDockAreaTabBar::tabInserted, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "tabInserted"),
                             Napi::Number::New(env, index)});
    });
  }
};
