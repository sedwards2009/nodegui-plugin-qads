#include "cdockwidget_wrap.h"


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
       InstanceMethod("setToggleViewActionMode", &CDockWidgetWrap::setToggleViewActionMode),
       InstanceMethod("setTabToolTip", &CDockWidgetWrap::setTabToolTip),
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
    QObject* widgetObject = info[0].As<Napi::External<QObject>>().Data();
    QWidget* widgetWidget = qobject_cast<QWidget*>(widgetObject);

    int insertMode = info[1].As<Napi::Number>().Int32Value();

    this->instance->setWidget(widgetWidget, static_cast<ads::CDockWidget::eInsertMode>(insertMode));
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
