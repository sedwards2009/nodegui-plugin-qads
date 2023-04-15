#pragma once

#include "FloatingDockContainer.h"

#include "Extras/Export/export.h"
#include "QtWidgets/QWidget/qwidget_macro.h"
#include "core/NodeWidget/nodewidget.h"


class NCFloatingDockContainer : public ads::CFloatingDockContainer, public NodeWidget {
  Q_OBJECT
  NODEWIDGET_IMPLEMENTATIONS(CFloatingDockContainer)
 public:
  using ads::CFloatingDockContainer::CFloatingDockContainer;  // inherit all constructors

  virtual void connectSignalsToEventEmitter() {
    QWIDGET_SIGNALS
  }
};
