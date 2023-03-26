#include "cdockmanager_wrap.h"
#include "DockAreaWidget.h"


Napi::FunctionReference CDockManagerWrap::constructor;

Napi::Object CDockManagerWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockManager";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {
       InstanceMethod("addDockWidgetToContainer", &CDockManagerWrap::addDockWidgetToContainer),
       InstanceMethod("addDockWidgetTab", &CDockManagerWrap::addDockWidgetTab),
       InstanceMethod("addDockWidgetTabToArea", &CDockManagerWrap::addDockWidgetTabToArea),
       InstanceMethod("findDockWidget", &CDockManagerWrap::findDockWidget),
       InstanceMethod("removeDockWidget", &CDockManagerWrap::removeDockWidget),
       InstanceMethod("centralWidget", &CDockManagerWrap::centralWidget),
       InstanceMethod("setCentralWidget", &CDockManagerWrap::setCentralWidget),
       StaticMethod("setConfigFlag", &StaticCDockManagerWrapMethods::setConfigFlag),
       CDOCKCONTAINERWIDGET_WRAPPED_METHODS_EXPORT_DEFINE(CDockManagerWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CDockManager, CDockManagerWrap);
  return exports;
}

ads::CDockManager* CDockManagerWrap::getInternalInstance() { return this->instance; }

CDockManagerWrap::~CDockManagerWrap() { extrautils::safeDelete(this->instance); }

CDockManagerWrap::CDockManagerWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CDockManagerWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 0) {
    // --- Construct a new instance
    this->instance = new NCDockManager();
  } else if (argCount == 1) {
    if (info[0].IsExternal()) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<ads::CDockManager>>().Data();
    } else {
      // --- Construct a new instance and pass a parent
      Napi::Object parentObject = info[0].As<Napi::Object>();
      NodeWidgetWrap* parentWidgetWrap = Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(parentObject);
      this->instance = new NCDockManager(parentWidgetWrap->getInternalInstance());
    }
  } else {
    Napi::TypeError::New(
        env, "NodeGui: CDockManagerWrap: Wrong number of arguments to constructor")
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

Napi::Value CDockManagerWrap::addDockWidgetToContainer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  int area = info[0].As<Napi::Number>().Int32Value();

  ads::CDockWidget* dockWidget = nullptr;
  if ( ! info[1].IsNull()) {
    Napi::Object dockObjectNapi = info[1].As<Napi::Object>();
    NodeWidgetWrap* dockWidgetWrap = Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockObjectNapi);
    QObject* dockObject = dockWidgetWrap->getInternalInstance();
    dockWidget = qobject_cast<ads::CDockWidget*>(dockObject);
  }

  ads::CDockContainerWidget* dockContainerWidget = nullptr;
  if ( ! info[2].IsNull()) {
    Napi::Object dockContainerNapi = info[2].As<Napi::Object>();
    NodeWidgetWrap* dockContianerWrap = Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockContainerNapi);
    QObject* dockContainer = dockContianerWrap->getInternalInstance();
    dockContainerWidget = qobject_cast<ads::CDockContainerWidget*>(dockContainer);
  }

  ads::CDockAreaWidget* dockAreaWidgetResult = this->instance->addDockWidgetToContainer(
    static_cast<ads::DockWidgetArea>(area),
    dockWidget, dockContainerWidget);
  if (dockAreaWidgetResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockAreaWidgetResult));
  } else {
    return env.Null();
  }
}

Napi::Value CDockManagerWrap::addDockWidgetTab(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  int area = info[0].As<Napi::Number>().Int32Value();

  ads::CDockWidget* dockWidget = nullptr;
  if ( ! info[1].IsNull()) {
    Napi::Object dockObjectNapi = info[1].As<Napi::Object>();
    NodeWidgetWrap* dockWidgetWrap = Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockObjectNapi);
    QObject* dockObject = dockWidgetWrap->getInternalInstance();
    dockWidget = qobject_cast<ads::CDockWidget*>(dockObject);
  }

  ads::CDockAreaWidget* dockAreaWidgetResult = this->instance->addDockWidgetTab(
    static_cast<ads::DockWidgetArea>(area), dockWidget);
  if (dockAreaWidgetResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockAreaWidgetResult));
  } else {
    return env.Null();
  }
}

Napi::Value CDockManagerWrap::addDockWidgetTabToArea(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Object dockObjectNapi = info[0].As<Napi::Object>();
  NodeWidgetWrap* dockWidgetWrap = Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockObjectNapi);
  QObject* dockObject = dockWidgetWrap->getInternalInstance();
  ads::CDockWidget* dockWidget = qobject_cast<ads::CDockWidget*>(dockObject);

  Napi::Object dockAreaObjectNapi = info[1].As<Napi::Object>();
  NodeWidgetWrap* dockAreaWidgetWrap = Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockAreaObjectNapi);
  QObject* dockAreaObject = dockAreaWidgetWrap->getInternalInstance();
  ads::CDockAreaWidget*dockAreaWidget = qobject_cast<ads::CDockAreaWidget*>(dockAreaObject);

  int index = info[2].As<Napi::Number>().Int32Value();

  ads::CDockAreaWidget* dockAreaWidgetResult = this->instance->addDockWidgetTabToArea(
    dockWidget, dockAreaWidget, index);
  if (dockAreaWidgetResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockAreaWidgetResult));
  } else {
    return env.Null();
  }
}

Napi::Value CDockManagerWrap::findDockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::String objectNameNapi = info[0].As<Napi::String>();
  std::string objectName = objectNameNapi.Utf8Value();
  QString qObjectName = QString::fromStdString(objectName);

  ads::CDockWidget* dockWidgetResult = this->instance->findDockWidget(qObjectName);
  if (dockWidgetResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidgetResult));
  } else {
    return env.Null();
  }
}

Napi::Value CDockManagerWrap::centralWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockWidget* dockWidgetResult = this->instance->centralWidget();
  if (dockWidgetResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidgetResult));
  } else {
    return env.Null();
  }
}

Napi::Value CDockManagerWrap::setCentralWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Object dockObjectNapi = info[0].As<Napi::Object>();
  NodeWidgetWrap* dockWidgetWrap = Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockObjectNapi);
  QObject* dockObject = dockWidgetWrap->getInternalInstance();
  ads::CDockWidget* dockWidget = qobject_cast<ads::CDockWidget*>(dockObject);

  ads::CDockAreaWidget* dockAreaWidgetResult = this->instance->setCentralWidget(dockWidget);
  if (dockAreaWidgetResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockAreaWidgetResult));
  } else {
    return env.Null();
  }
}

Napi::Value StaticCDockManagerWrapMethods::setConfigFlag(
    const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int flag = info[0].As<Napi::Number>().Int32Value();
  bool switchOn = info[1].As<Napi::Boolean>().Value();
  ads::CDockManager::setConfigFlag(static_cast<ads::CDockManager::eConfigFlag>(flag), switchOn);
  return env.Null();
}
