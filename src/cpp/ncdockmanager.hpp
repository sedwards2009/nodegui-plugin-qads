#pragma once

#include "DockManager.h"
#include "DockWidget.h"
#include "DockAreaWidget.h"

#include "Extras/Export/export.h"
#include "QtWidgets/QFrame/qframe_macro.h"
#include "core/NodeWidget/nodewidget.h"

class NCDockManager : public ads::CDockManager, public NodeWidget {
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
                             WrapperCache::instance.getWrapper(env, static_cast<QObject*>(floatingDockContainer))});
    });

    QObject::connect(this, &ads::CDockManager::floatingWidgetAboutToBeRemoved, [=](ads::CFloatingDockContainer *floatingDockContainer) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "floatingWidgetAboutToBeRemoved"),
                             WrapperCache::instance.getWrapper(env, static_cast<QObject*>(floatingDockContainer))});
    });

    QObject::connect(this, &ads::CDockManager::dockAreaCreated, [=](ads::CDockAreaWidget *dockAreaWidget) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "dockAreaCreated"),
                             WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockAreaWidget))});
    });

    QObject::connect(this, &ads::CDockManager::dockWidgetAdded, [=](ads::CDockWidget *dockWidget) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "dockWidgetAdded"),
                             WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidget))});
    });

    QObject::connect(this, &ads::CDockManager::dockWidgetAboutToBeRemoved, [=](ads::CDockWidget *dockWidget) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "dockWidgetAboutToBeRemoved"),
                             WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidget))});
    });

    QObject::connect(this, &ads::CDockManager::dockWidgetRemoved, [=](ads::CDockWidget *dockWidget) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "dockWidgetRemoved"),
                             WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidget))});
    });

    QObject::connect(this, &ads::CDockManager::focusedDockWidgetChanged, [=](ads::CDockWidget *dockWidget, ads::CDockWidget *dockWidget2) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "focusedDockWidgetChanged"),
                             WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidget)),
                             WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidget2))});
    });
  }
};
