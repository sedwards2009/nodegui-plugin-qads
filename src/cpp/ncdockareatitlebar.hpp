#pragma once

#include "DockAreaTitleBar.h"

#include "Extras/Export/export.h"
#include "QtWidgets/QFrame/qframe_macro.h"
#include "core/NodeWidget/nodewidget.h"


class NCDockAreaTitleBar : public ads::CDockAreaTitleBar, public NodeWidget {
  Q_OBJECT
  NODEWIDGET_IMPLEMENTATIONS(CDockAreaTitleBar)
 public:
  using ads::CDockAreaTitleBar::CDockAreaTitleBar;  // inherit all constructors

  virtual void connectSignalsToEventEmitter() {
    QFRAME_SIGNALS

    QObject::connect(this, &ads::CDockAreaTitleBar::tabBarClicked, [=](int index) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "tabBarClicked"),
                             Napi::Number::New(env, index)});
    });
  }
};
