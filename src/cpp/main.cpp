#include <napi.h>
#include "DockComponentsFactory.h"
#include "cdockcontainerwidget_wrap.h"
#include "cdockmanager_wrap.h"
#include "cdockareawidget_wrap.h"
#include "cdockwidget_wrap.h"
#include "cdockareatitlebar_wrap.h"
#include "cdockareatabbar_wrap.h"
#include "cfloatingdockcontainer_wrap.h"
#include "cdocksplitter_wrap.h"
#include "ncdockareatabbar.hpp"
#include "ncdockareatitlebar.hpp"
#include "ncfloatingdockcontainer.hpp"
#include "cdockwidgettab_wrap.h"
#include "ncdockwidgettab.hpp"


class NCDockComponentsFactory : public ads::CDockComponentsFactory {
  virtual ~NCDockComponentsFactory() {}

  virtual ads::CDockWidgetTab* createDockWidgetTab(ads::CDockWidget* DockWidget) const {
    return new NCDockWidgetTab(DockWidget);
  }

  // virtual CAutoHideTab* createDockWidgetSideTab(CDockWidget* DockWidget) const;

  virtual ads::CDockAreaTabBar* createDockAreaTabBar(ads::CDockAreaWidget* DockArea) const {
    return new NCDockAreaTabBar(DockArea);
  }

  virtual ads::CDockAreaTitleBar* createDockAreaTitleBar(ads::CDockAreaWidget* DockArea) const {
    return new NCDockAreaTitleBar(DockArea);
  }

  virtual ads::CFloatingDockContainer* createCFloatingDockContainer(ads::CDockManager* DockManager) const {
    ads::CFloatingDockContainer* result = new NCFloatingDockContainer(DockManager);
    result->init();
    return result;
  }

  virtual ads::CFloatingDockContainer* createCFloatingDockContainer(ads::CDockAreaWidget* DockArea) const {
    ads::CFloatingDockContainer* result = new NCFloatingDockContainer(DockArea);
    result->init();
    return result;
  }

  virtual ads::CFloatingDockContainer* createCFloatingDockContainer(ads::CDockWidget* DockWidget) const {
    ads::CFloatingDockContainer* result = new NCFloatingDockContainer(DockWidget);
    result->init();
    return result;
  }
};

Napi::Object Main(Napi::Env env, Napi::Object exports) {
  ads::CDockComponentsFactory::setFactory(new NCDockComponentsFactory());

  CDockContainerWidgetWrap::init(env, exports);
  CDockManagerWrap::init(env, exports);
  CDockAreaWidgetWrap::init(env, exports);
  CDockWidgetWrap::init(env, exports);
  CDockAreaTitleBarWrap::init(env, exports);
  CDockAreaTabBarWrap::init(env, exports);
  CFloatingDockContainerWrap::init(env, exports);
  CDockSplitterWrap::init(env, exports);
  CDockWidgetTabWrap::init(env, exports);

  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Main)
