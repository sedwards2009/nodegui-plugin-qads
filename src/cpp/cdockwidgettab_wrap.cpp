#include "QtGui/QIcon/qicon_wrap.h"
#include "cdockwidgettab_wrap.h"
#include "DockWidgetTab.h"
#include "DockAreaWidget.h"


Napi::FunctionReference CDockWidgetTabWrap::constructor;

Napi::Object CDockWidgetTabWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockWidgetTab";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {InstanceMethod("dockAreaWidget", &CDockWidgetTabWrap::dockAreaWidget),
       InstanceMethod("dockWidget", &CDockWidgetTabWrap::dockWidget),
       InstanceMethod("isActiveTab", &CDockWidgetTabWrap::isActiveTab),
       InstanceMethod("setActiveTab", &CDockWidgetTabWrap::setActiveTab),
       InstanceMethod("text", &CDockWidgetTabWrap::text),
       InstanceMethod("setText", &CDockWidgetTabWrap::setText),
       InstanceMethod("isTitleElided", &CDockWidgetTabWrap::isTitleElided),
       InstanceMethod("isClosable", &CDockWidgetTabWrap::isClosable),
       InstanceMethod("setElideMode", &CDockWidgetTabWrap::setElideMode),
       InstanceMethod("updateStyle", &CDockWidgetTabWrap::updateStyle),
       InstanceMethod("iconSize", &CDockWidgetTabWrap::iconSize),
       InstanceMethod("setIconSize", &CDockWidgetTabWrap::setIconSize),
       InstanceMethod("setIcon", &CDockWidgetTabWrap::setIcon),
       InstanceMethod("icon", &CDockWidgetTabWrap::icon),
       InstanceMethod("setFeature", &CDockWidgetTabWrap::setFeature),
       InstanceMethod("features", &CDockWidgetTabWrap::features),
       QFRAME_WRAPPED_METHODS_EXPORT_DEFINE(CDockWidgetTabWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CDockWidgetTab, CDockWidgetTabWrap);
  return exports;
}

ads::CDockWidgetTab* CDockWidgetTabWrap::getInternalInstance() { return this->instance; }

CDockWidgetTabWrap::~CDockWidgetTabWrap() { extrautils::safeDelete(this->instance); }

CDockWidgetTabWrap::CDockWidgetTabWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CDockWidgetTabWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 1 && info[0].IsExternal()) {
    // --- Wrap a given C++ instance
    this->instance = info[0].As<Napi::External<ads::CDockWidgetTab>>().Data();
  } else {
    Napi::TypeError::New(
        env, "NodeGui: CDockWidgetTabWrap: Wrong number of arguments to constructor")
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

Napi::Value CDockWidgetTabWrap::dockAreaWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockAreaWidget* dockAreaWidget = this->instance->dockAreaWidget();
  if (dockAreaWidget) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockAreaWidget));
  } else {
    return env.Null();
  }
}

Napi::Value CDockWidgetTabWrap::dockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockWidget* dockWidgetResult = this->instance->dockWidget();
  if (dockWidgetResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidgetResult));
  } else {
    return env.Null();
  }
}

Napi::Value CDockWidgetTabWrap::isActiveTab(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isActiveTab();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockWidgetTabWrap::setActiveTab(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool active = info[0].As<Napi::Boolean>().Value();
  this->instance->setActiveTab(active);
  return env.Null();
}

Napi::Value CDockWidgetTabWrap::text(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QString result = this->instance->text();
  return Napi::String::New(env, result.toStdString());
}

Napi::Value CDockWidgetTabWrap::setText(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::string titleNapiText = info[0].As<Napi::String>().Utf8Value();
  QString title = QString::fromUtf8(titleNapiText.c_str());
  this->instance->setText(title);
  return env.Null();
}

Napi::Value CDockWidgetTabWrap::isTitleElided(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isTitleElided();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockWidgetTabWrap::isClosable(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isClosable();
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockWidgetTabWrap::setElideMode(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Qt::TextElideMode mode = static_cast<Qt::TextElideMode>(info[0].As<Napi::Number>().Int32Value());
  this->instance->setElideMode(mode);
  return env.Null();
}

Napi::Value CDockWidgetTabWrap::updateStyle(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->instance->updateStyle();
  return env.Null();
}

Napi::Value CDockWidgetTabWrap::iconSize(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QSize result = this->instance->iconSize();
  auto resultInstance = QSizeWrap::constructor.New(
      {Napi::External<QSize>::New(env, new QSize(result))});
    return resultInstance;
}

Napi::Value CDockWidgetTabWrap::setIconSize(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QSizeWrap* SizeWrap = Napi::ObjectWrap<QSizeWrap>::Unwrap(info[0].As<Napi::Object>());
  QSize* Size = SizeWrap->getInternalInstance();
  this->instance->setIconSize(*Size);
  return env.Null();
}

Napi::Value CDockWidgetTabWrap::setIcon(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Object iconObject = info[0].As<Napi::Object>();
  QIconWrap* iconWrap = Napi::ObjectWrap<QIconWrap>::Unwrap(iconObject);
  this->instance->setIcon(*iconWrap->getInternalInstance());
  return env.Null();
}

Napi::Value CDockWidgetTabWrap::icon(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QIcon icon = this->instance->icon();
  auto instance = QIconWrap::constructor.New(
      {Napi::External<QIcon>::New(env, new QIcon(icon))});
  return instance;
}

Napi::Value CDockWidgetTabWrap::setFeature(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int flag = info[0].As<Napi::Number>().Int32Value();
  bool switchOn = info[1].As<Napi::Boolean>().Value();
  this->instance->setFeature(static_cast<ads::CDockWidgetTab::DockWidgetTabFeature>(flag), switchOn);
  return env.Null();
}

Napi::Value CDockWidgetTabWrap::features(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto features = this->instance->features();
  return Napi::Number::New(env, features);
}
