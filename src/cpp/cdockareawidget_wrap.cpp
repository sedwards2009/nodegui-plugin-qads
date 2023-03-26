#include "cdockareawidget_wrap.h"
#include "cdockwidget_wrap.h"
#include "cdockcontainerwidget_wrap.h"
#include "cdockmanager_wrap.h"
#include "DockAreaTitleBar.h"

Napi::FunctionReference CDockAreaWidgetWrap::constructor;

Napi::Object CDockAreaWidgetWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockAreaWidget";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {
        InstanceMethod("setAllowedAreas", &CDockAreaWidgetWrap::setAllowedAreas),
        InstanceMethod("titleBar", &CDockAreaWidgetWrap::titleBar),
        InstanceMethod("dockManager", &CDockAreaWidgetWrap::dockManager),
        InstanceMethod("dockContainer", &CDockAreaWidgetWrap::dockContainer),
        InstanceMethod("titleBarGeometry", &CDockAreaWidgetWrap::titleBarGeometry),
        InstanceMethod("contentAreaGeometry", &CDockAreaWidgetWrap::contentAreaGeometry),
        InstanceMethod("dockWidgetsCount", &CDockAreaWidgetWrap::dockWidgetsCount),
        InstanceMethod("openDockWidgetsCount", &CDockAreaWidgetWrap::openDockWidgetsCount),
        InstanceMethod("currentIndex", &CDockAreaWidgetWrap::currentIndex),
        InstanceMethod("indexOfFirstOpenDockWidget", &CDockAreaWidgetWrap::indexOfFirstOpenDockWidget),
        InstanceMethod("setCurrentIndex", &CDockAreaWidgetWrap::setCurrentIndex),
        InstanceMethod("closeArea", &CDockAreaWidgetWrap::closeArea),
        InstanceMethod("closeOtherAreas", &CDockAreaWidgetWrap::closeOtherAreas),
        InstanceMethod("isCentralWidgetArea", &CDockAreaWidgetWrap::isCentralWidgetArea),
        InstanceMethod("dockWidgets", &CDockAreaWidgetWrap::dockWidgets),
        InstanceMethod("openedDockWidgets", &CDockAreaWidgetWrap::openedDockWidgets),
        InstanceMethod("dockWidget", &CDockAreaWidgetWrap::dockWidget),
        InstanceMethod("currentDockWidget", &CDockAreaWidgetWrap::currentDockWidget),
        InstanceMethod("setCurrentDockWidget", &CDockAreaWidgetWrap::setCurrentDockWidget),
        InstanceMethod("features", &CDockAreaWidgetWrap::features),
        InstanceMethod("allowedAreas", &CDockAreaWidgetWrap::allowedAreas),
        InstanceMethod("dockAreaFlags", &CDockAreaWidgetWrap::dockAreaFlags),
        InstanceMethod("titleBarButton", &CDockAreaWidgetWrap::titleBarButton),
        InstanceMethod("setDockAreaFlag", &CDockAreaWidgetWrap::setDockAreaFlag),
        QFRAME_WRAPPED_METHODS_EXPORT_DEFINE(CDockAreaWidgetWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CDockAreaWidget, CDockAreaWidgetWrap);
  return exports;
}

ads::CDockAreaWidget* CDockAreaWidgetWrap::getInternalInstance() { return this->instance; }

CDockAreaWidgetWrap::~CDockAreaWidgetWrap() { extrautils::safeDelete(this->instance); }

CDockAreaWidgetWrap::CDockAreaWidgetWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CDockAreaWidgetWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 1) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<ads::CDockAreaWidget>>().Data();
  } else if (argCount == 2) {
    // --- Construct a new instance and pass a parent
    Napi::Object dockManagerObject = info[0].As<Napi::Object>();
    CDockManagerWrap* dockManagerWrap =
        Napi::ObjectWrap<CDockManagerWrap>::Unwrap(dockManagerObject);

    Napi::Object parentObject = info[1].As<Napi::Object>();
    CDockContainerWidgetWrap* parentWidgetWrap =
        Napi::ObjectWrap<CDockContainerWidgetWrap>::Unwrap(parentObject);

    this->instance = new NCDockAreaWidget(dockManagerWrap->getInternalInstance(),
                                          parentWidgetWrap->getInternalInstance());
  } else {
    Napi::TypeError::New(
        env, "NodeGui: CDockAreaWidgetWrap: Wrong number of arguments to constructor")
        .ThrowAsJavaScriptException();
  }

  // YogaWidget* yogaWidget =
  //     dynamic_cast<YogaWidget*>(this->getInternalInstance());
  // if (yogaWidget) {
  //   auto flexNode = yogaWidget->getFlexNode();
  //   YGNodeSetNodeType(flexNode, YGNodeType::YGNodeTypeText);
  // }
  this->rawData =
      extrautils::configureQWidget(this->getInternalInstance(), true);
}

Napi::Value CDockAreaWidgetWrap::setAllowedAreas(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int areas = info[0].As<Napi::Number>().Int32Value();
  this->instance->setAllowedAreas(static_cast<ads::DockWidgetAreas>(areas));
  return env.Null();
}

Napi::Value CDockAreaWidgetWrap::titleBar(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QObject* widget = this->instance->titleBar();
  if (widget) {
    return WrapperCache::instance.getWrapper(env, widget);
  } else {
    return env.Null();
  }
}

Napi::Value CDockAreaWidgetWrap::dockManager(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockManager* dockManagerResult = this->instance->dockManager();
  if (dockManagerResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockManagerResult));
  } else {
    return env.Null();
  }
}

Napi::Value CDockAreaWidgetWrap::dockContainer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockContainerWidget* dockContainerResult = this->instance->dockContainer();
  if (dockContainerResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockContainerResult));
  } else {
    return env.Null();
  }
}

Napi::Value CDockAreaWidgetWrap::titleBarGeometry(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QRect result = this->instance->titleBarGeometry();
  auto resultInstance = QRectWrap::constructor.New(
      {Napi::External<QRect>::New(env, new QRect(result))});
    return resultInstance;
}

Napi::Value CDockAreaWidgetWrap::contentAreaGeometry(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QRect result = this->instance->contentAreaGeometry();
  auto resultInstance = QRectWrap::constructor.New(
      {Napi::External<QRect>::New(env, new QRect(result))});
    return resultInstance;
}

Napi::Value CDockAreaWidgetWrap::dockWidgetsCount(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int result = this->instance->dockWidgetsCount();
  return Napi::Number::New(env, result);
}

Napi::Value CDockAreaWidgetWrap::openDockWidgetsCount(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int result = this->instance->openDockWidgetsCount();
  return Napi::Number::New(env, result);
}

Napi::Value CDockAreaWidgetWrap::currentIndex(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int result = this->instance->currentIndex();
  return Napi::Number::New(env, result);
}

Napi::Value CDockAreaWidgetWrap::indexOfFirstOpenDockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int result = this->instance->indexOfFirstOpenDockWidget();
  return Napi::Number::New(env, result);
}

Napi::Value CDockAreaWidgetWrap::setCurrentIndex(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int index = info[0].As<Napi::Number>().Int32Value();
  this->instance->setCurrentIndex(index);
  return env.Null();
}

Napi::Value CDockAreaWidgetWrap::closeArea(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->instance->closeArea();
  return env.Null();
}

Napi::Value CDockAreaWidgetWrap::closeOtherAreas(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->instance->closeOtherAreas();
  return env.Null();
}

Napi::Value CDockAreaWidgetWrap::isCentralWidgetArea(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isCentralWidgetArea();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockAreaWidgetWrap::dockWidgets(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<ads::CDockWidget*> list = this->instance->dockWidgets();
    Napi::Array resultArrayNapi = Napi::Array::New(env, list.size());
    for (int i = 0; i < list.size(); i++) {
      resultArrayNapi[i] =
          WrapperCache::instance.getWrapper(env, list[i]);
    }
    return resultArrayNapi;
}

Napi::Value CDockAreaWidgetWrap::openedDockWidgets(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<ads::CDockWidget*> list = this->instance->openedDockWidgets();
    Napi::Array resultArrayNapi = Napi::Array::New(env, list.size());
    for (int i = 0; i < list.size(); i++) {
      resultArrayNapi[i] =
          WrapperCache::instance.getWrapper(env, list[i]);
    }
    return resultArrayNapi;
}

Napi::Value CDockAreaWidgetWrap::dockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int index = info[0].As<Napi::Number>().Int32Value();
  ads::CDockWidget* dockWidgetResult = this->instance->dockWidget(index);
  if (dockWidgetResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidgetResult));
  } else {
    return env.Null();
  }
}

Napi::Value CDockAreaWidgetWrap::currentDockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockWidget* dockWidgetResult = this->instance->currentDockWidget();
  if (dockWidgetResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidgetResult));
  } else {
    return env.Null();
  }
}

Napi::Value CDockAreaWidgetWrap::setCurrentDockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Object dockObjectNapi = info[0].As<Napi::Object>();
  NodeWidgetWrap* dockWidgetWrap = Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockObjectNapi);
  QObject* dockObject = dockWidgetWrap->getInternalInstance();
  ads::CDockWidget* dockWidget = qobject_cast<ads::CDockWidget*>(dockObject);

  this->instance->setCurrentDockWidget(dockWidget);
  return env.Null();
}

Napi::Value CDockAreaWidgetWrap::features(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto features = this->instance->features();
  return Napi::Number::New(env, features);
}

Napi::Value CDockAreaWidgetWrap::allowedAreas(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto allowedAreas = this->instance->allowedAreas();
  return Napi::Number::New(env, allowedAreas);
}

Napi::Value CDockAreaWidgetWrap::dockAreaFlags(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto dockAreaFlags = this->instance->dockAreaFlags();
  return Napi::Number::New(env, dockAreaFlags);
}

Napi::Value CDockAreaWidgetWrap::titleBarButton(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int which = info[0].As<Napi::Number>().Int32Value();
  QAbstractButton* button = this->instance->titleBarButton(static_cast<ads::TitleBarButton>(which));
  if (button) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(button));
  } else {
    return env.Null();
  }
}

Napi::Value CDockAreaWidgetWrap::setDockAreaFlag(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int flag = info[0].As<Napi::Number>().Int32Value();
  bool on = info[1].As<Napi::Boolean>().Value();
  this->instance->setDockAreaFlag(static_cast<ads::CDockAreaWidget::eDockAreaFlag>(flag), on);
  return env.Null();
}
