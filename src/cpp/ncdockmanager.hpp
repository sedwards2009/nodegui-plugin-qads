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

    QObject::connect(this, &ads::CDockManager::floatingWidgetCreated, [=](ads::CFloatingDockContainer *floatingDockContainer) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "floatingWidgetCreated"),
                             Napi::External<ads::CFloatingDockContainer>::New(env, floatingDockContainer)});
    });

    QObject::connect(this, &ads::CDockManager::dockAreaCreated, [=](ads::CDockAreaWidget *dockAreaWidget) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "dockAreaCreated"),
                             Napi::External<ads::CDockAreaWidget>::New(env, dockAreaWidget)});
    });

    QObject::connect(this, &ads::CDockManager::dockWidgetAdded, [=](ads::CDockWidget *dockWidget) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "dockWidgetAdded"),
                             Napi::External<ads::CDockWidget>::New(env, dockWidget)});
    });

    QObject::connect(this, &ads::CDockManager::dockWidgetAboutToBeRemoved, [=](ads::CDockWidget *dockWidget) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "dockWidgetAboutToBeRemoved"),
                             Napi::External<ads::CDockWidget>::New(env, dockWidget)});
    });

    QObject::connect(this, &ads::CDockManager::dockWidgetRemoved, [=](ads::CDockWidget *dockWidget) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "dockWidgetRemoved"),
                             Napi::External<ads::CDockWidget>::New(env, dockWidget)});
    });

    QObject::connect(this, &ads::CDockManager::focusedDockWidgetChanged, [=](ads::CDockWidget *dockWidget, ads::CDockWidget *dockWidget2) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "focusedDockWidgetChanged"),
                             Napi::External<ads::CDockWidget>::New(env, dockWidget),
                             Napi::External<ads::CDockWidget>::New(env, dockWidget2)});
    });
  }
};
