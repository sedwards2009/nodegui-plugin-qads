#include <napi.h>
#include "cdockcontainerwidget_wrap.h"
#include "cdockmanager_wrap.h"
#include "cdockareawidget_wrap.h"
#include "cdockwidget_wrap.h"
#include "cdockareatitlebar_wrap.h"
#include "cdockareatabbar_wrap.h"


Napi::Object Main(Napi::Env env, Napi::Object exports) {
//  CDockContainerWidgetWrap::init(env, exports);
  CDockManagerWrap::init(env, exports);
  CDockAreaWidgetWrap::init(env, exports);
  CDockWidgetWrap::init(env, exports);
  CDockAreaTitleBarWrap::init(env, exports);
  CDockAreaTabBarWrap::init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Main)
