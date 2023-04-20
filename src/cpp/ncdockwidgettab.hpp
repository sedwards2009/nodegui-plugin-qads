#pragma once

#include "DockContainerWidget.h"

#include "Extras/Export/export.h"
#include "QtWidgets/QFrame/qframe_macro.h"
#include "core/NodeWidget/nodewidget.h"


class NCDockWidgetTab : public ads::CDockWidgetTab, public NodeWidget {
  Q_OBJECT
  NODEWIDGET_IMPLEMENTATIONS(CDockWidgetTab)
 public:
  using ads::CDockWidgetTab::CDockWidgetTab;  // inherit all constructors

  virtual void connectSignalsToEventEmitter() {
    QFRAME_SIGNALS

    QObject::connect(this, &ads::CDockWidgetTab::activeTabChanged, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "activeTabChanged")});
    });

    QObject::connect(this, &ads::CDockWidgetTab::clicked, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "clicked")});
    });

    QObject::connect(this, &ads::CDockWidgetTab::closeRequested, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "closeRequested")});
    });

    QObject::connect(this, &ads::CDockWidgetTab::closeOtherTabsRequested, [=]() {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "closeOtherTabsRequested")});
    });

    QObject::connect(this, &ads::CDockWidgetTab::moved, [=](const QPoint& GlobalPos) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      auto pointInstance = QPointWrap::constructor.New(
                     {Napi::External<QPoint>::New(env, new QPoint(GlobalPos))});
      this->emitOnNode.Call({Napi::String::New(env, "moved"), pointInstance});
    });

    QObject::connect(this, &ads::CDockWidgetTab::elidedChanged, [=](bool elided) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "elidedChanged"),
                             Napi::Boolean::New(env, elided)});
    });
  }
};
