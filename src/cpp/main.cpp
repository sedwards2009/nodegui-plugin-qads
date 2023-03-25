#include <napi.h>
#include "DockComponentsFactory.h"
#include "cdockcontainerwidget_wrap.h"
#include "cdockmanager_wrap.h"
#include "cdockareawidget_wrap.h"
#include "cdockwidget_wrap.h"
#include "cdockareatitlebar_wrap.h"
#include "cdockareatabbar_wrap.h"
#include "cfloatingdockcontainer_wrap.h"
#include "ncdockareatabbar.hpp"
#include "ncdockareatitlebar.hpp"


class NCDockComponentsFactory : public ads::CDockComponentsFactory {
	virtual ~NCDockComponentsFactory() {}
	// virtual CDockWidgetTab* createDockWidgetTab(CDockWidget* DockWidget) const;
	// virtual CAutoHideTab* createDockWidgetSideTab(CDockWidget* DockWidget) const;

	virtual ads::CDockAreaTabBar* createDockAreaTabBar(ads::CDockAreaWidget* DockArea) const {
    return new NCDockAreaTabBar(DockArea);
  }

	virtual ads::CDockAreaTitleBar* createDockAreaTitleBar(ads::CDockAreaWidget* DockArea) const {
    return new NCDockAreaTitleBar(DockArea);
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

  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Main)
