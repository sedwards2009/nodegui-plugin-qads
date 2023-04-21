#include "cdockwidget_wrap.h"
#include "DockManager.h"
#include "DockAreaWidget.h"
#include "DockContainerWidget.h"
#include "DockWidgetTab.h"


Napi::FunctionReference CDockWidgetWrap::constructor;

Napi::Object CDockWidgetWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockWidget";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {
       InstanceMethod("setFeature", &CDockWidgetWrap::setFeature),
       InstanceMethod("features", &CDockWidgetWrap::features),
       InstanceMethod("setWidget", &CDockWidgetWrap::setWidget),
       InstanceMethod("takeWidget", &CDockWidgetWrap::takeWidget),
       InstanceMethod("widget", &CDockWidgetWrap::widget),
       InstanceMethod("setToggleViewActionMode", &CDockWidgetWrap::setToggleViewActionMode),
       InstanceMethod("setTabToolTip", &CDockWidgetWrap::setTabToolTip),
       InstanceMethod("isFloating", &CDockWidgetWrap::isFloating),
       InstanceMethod("isInFloatingContainer", &CDockWidgetWrap::isInFloatingContainer),
       InstanceMethod("isClosed", &CDockWidgetWrap::isClosed),
       InstanceMethod("setTabToolTip", &CDockWidgetWrap::setTabToolTip),
       InstanceMethod("isCentralWidget", &CDockWidgetWrap::isCentralWidget),
       InstanceMethod("isFullScreen", &CDockWidgetWrap::isFullScreen),
       InstanceMethod("isTabbed", &CDockWidgetWrap::isTabbed),
       InstanceMethod("isCurrentTab", &CDockWidgetWrap::isCurrentTab),
       InstanceMethod("toggleView", &CDockWidgetWrap::toggleView),
       InstanceMethod("setAsCurrentTab", &CDockWidgetWrap::setAsCurrentTab),
       InstanceMethod("setFloating", &CDockWidgetWrap::setFloating),
       InstanceMethod("deleteDockWidget", &CDockWidgetWrap::deleteDockWidget),
       InstanceMethod("closeDockWidget", &CDockWidgetWrap::closeDockWidget),
       InstanceMethod("setMinimumSizeHintMode", &CDockWidgetWrap::setMinimumSizeHintMode),
       InstanceMethod("dockManager", &CDockWidgetWrap::dockManager),
       InstanceMethod("dockContainer", &CDockWidgetWrap::dockContainer),
       InstanceMethod("dockAreaWidget", &CDockWidgetWrap::dockAreaWidget),
       InstanceMethod("tabWidget", &CDockWidgetWrap::tabWidget),
       QFRAME_WRAPPED_METHODS_EXPORT_DEFINE(CDockWidgetWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CDockWidget, CDockWidgetWrap);
  return exports;
}

ads::CDockWidget* CDockWidgetWrap::getInternalInstance() { return this->instance; }

CDockWidgetWrap::~CDockWidgetWrap() { extrautils::safeDelete(this->instance); }

CDockWidgetWrap::CDockWidgetWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CDockWidgetWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 1) {
    if (info[0].IsExternal()) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<ads::CDockWidget>>().Data();
    } else {
      // --- Construct a new instance and pass a parent
      Napi::String text = info[0].As<Napi::String>();
      std::string title = text.Utf8Value();
      QString qTitle = QString::fromStdString(title);
      this->instance = new NCDockWidget(qTitle);
    }
  } else if (argCount == 2) {
    // --- Construct a new instance and pass a parent
    Napi::String text = info[0].As<Napi::String>();
    std::string title = text.Utf8Value();
    QString qTitle = QString::fromStdString(title);

    Napi::Object parentObject = info[1].As<Napi::Object>();
    NodeWidgetWrap* parentWidgetWrap =
        Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(parentObject);

    this->instance = new NCDockWidget(qTitle, parentWidgetWrap->getInternalInstance());
  } else {
    Napi::TypeError::New(
        env, "NodeGui: CDockWidgetWrap: Wrong number of arguments to constructor")
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

Napi::Value CDockWidgetWrap::setFeature(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int flag = info[0].As<Napi::Number>().Int32Value();
  bool switchOn = info[1].As<Napi::Boolean>().Value();
  this->instance->setFeature(static_cast<ads::CDockWidget::DockWidgetFeature>(flag), switchOn);
  return env.Null();
}

Napi::Value CDockWidgetWrap::features(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto features = this->instance->features();
  return Napi::Number::New(env, features);
}

Napi::Value CDockWidgetWrap::setWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (info[0].IsNull()) {
    this->instance->setWidget(nullptr);
  } else {
    Napi::Object parentObject = info[0].As<Napi::Object>();
    NodeWidgetWrap* parentWidgetWrap = Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(parentObject);
    QWidget *widget = parentWidgetWrap->getInternalInstance();

    int insertMode = info[1].As<Napi::Number>().Int32Value();

    this->instance->setWidget(widget, static_cast<ads::CDockWidget::eInsertMode>(insertMode));
  }
  return env.Null();
}

Napi::Value CDockWidgetWrap::takeWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QObject* widget = this->instance->takeWidget();
  if (widget) {
    return WrapperCache::instance.getWrapper(env, widget);
  } else {
    return env.Null();
  }
}

Napi::Value CDockWidgetWrap::widget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QObject* widget = this->instance->widget();
  if (widget) {
    return WrapperCache::instance.getWrapper(env, widget);
  } else {
    return env.Null();
  }
}

Napi::Value CDockWidgetWrap::setToggleViewActionMode(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int mode = info[0].As<Napi::Number>().Int32Value();
  this->instance->setToggleViewActionMode(static_cast<ads::CDockWidget::eToggleViewActionMode>(mode));
  return env.Null();
}

Napi::Value CDockWidgetWrap::setTabToolTip(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::String text = info[0].As<Napi::String>();
  std::string tip = text.Utf8Value();
  QString qTip = QString::fromStdString(tip);
  this->instance->setTabToolTip(qTip);
  return env.Null();
}

Napi::Value CDockWidgetWrap::isFloating(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isFloating();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockWidgetWrap::isInFloatingContainer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isInFloatingContainer();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockWidgetWrap::isClosed(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isClosed();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockWidgetWrap::isCentralWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isCentralWidget();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockWidgetWrap::isFullScreen(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isFullScreen();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockWidgetWrap::isTabbed(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isTabbed();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockWidgetWrap::isCurrentTab(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isCurrentTab();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockWidgetWrap::toggleView(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool Open = info[0].As<Napi::Boolean>().Value();
  this->instance->toggleView(Open);
  return env.Null();
}

Napi::Value CDockWidgetWrap::setAsCurrentTab(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->instance->setAsCurrentTab();
  return env.Null();
}

Napi::Value CDockWidgetWrap::setFloating(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->instance->setFloating();
  return env.Null();
}

Napi::Value CDockWidgetWrap::deleteDockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->instance->deleteDockWidget();
  return env.Null();
}

Napi::Value CDockWidgetWrap::closeDockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->instance->closeDockWidget();
  return env.Null();
}

Napi::Value CDockWidgetWrap::setMinimumSizeHintMode(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int mode = info[0].As<Napi::Number>().Int32Value();
  this->instance->setMinimumSizeHintMode(static_cast<ads::CDockWidget::eMinimumSizeHintMode>(mode));
  return env.Null();
}

Napi::Value CDockWidgetWrap::dockManager(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockManager* dockManager = this->instance->dockManager();
  if (dockManager) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockManager));
  } else {
    return env.Null();
  }
}

Napi::Value CDockWidgetWrap::dockContainer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockContainerWidget* dockContainer = this->instance->dockContainer();
  if (dockContainer) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockContainer));
  } else {
    return env.Null();
  }
}

Napi::Value CDockWidgetWrap::dockAreaWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockAreaWidget* dockAreaWidget = this->instance->dockAreaWidget();
  if (dockAreaWidget) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockAreaWidget));
  } else {
    return env.Null();
  }
}

Napi::Value CDockWidgetWrap::tabWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockWidgetTab* dockWidgetTab = this->instance->tabWidget();
  if (dockWidgetTab) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidgetTab));
  } else {
    return env.Null();
  }
}
