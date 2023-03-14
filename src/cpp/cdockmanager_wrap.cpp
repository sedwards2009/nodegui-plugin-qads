#include "cdockmanager_wrap.h"
#include "DockAreaWidget.h"


Napi::FunctionReference CDockManagerWrap::constructor;

Napi::Object CDockManagerWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockManager";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {InstanceMethod("addDockWidget", &CDockManagerWrap::addDockWidget),
       StaticMethod("setConfigFlag", &StaticCDockManagerWrapMethods::setConfigFlag),
       QFRAME_WRAPPED_METHODS_EXPORT_DEFINE(CDockManagerWrap)});
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
      NodeWidgetWrap* parentWidgetWrap =
          Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(parentObject);
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

Napi::Value CDockManagerWrap::addDockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  int area = info[0].As<Napi::Number>().Int32Value();

  QObject* dockObject = info[1].As<Napi::External<QObject>>().Data();
  ads::CDockWidget* dockWidget = qobject_cast<ads::CDockWidget*>(dockObject);

  ads::CDockAreaWidget* dockAreaWidget = nullptr;
  if ( ! info[2].IsNull()) {
    QObject* dockAreaObject = info[2].As<Napi::External<QObject>>().Data();
    dockAreaWidget = qobject_cast<ads::CDockAreaWidget*>(dockAreaObject);
  }

  int index = info[3].As<Napi::Number>().Int32Value();
  ads::CDockAreaWidget* dockAreaWidgetResult = this->instance->addDockWidget(static_cast<ads::DockWidgetArea>(area),
    dockWidget, dockAreaWidget, index);

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
