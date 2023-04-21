import { checkIfNativeElement, NativeElement, QFrame, QFrameSignals, QWidget, QWidgetSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';
import { CDockAreaWidget } from './CDockAreaWidget';
import { CDockContainerWidget } from './CDockContainerWidget';
import { CDockManager } from './CDockManager';
import { CDockWidgetTab } from './CDockWidgetTab';


export class CDockWidget extends QFrame<CDockWidgetSignals> {

  constructor(title: string, arg?: QWidget<QWidgetSignals> | NativeElement) {
    let native: NativeElement;
    if (checkIfNativeElement(arg)) {
        native = arg as NativeElement;
    } else if (arg != null) {
        const parent = arg as QWidget;
        native = new addon.CDockWidget(title, parent.native);
    } else {
        native = new addon.CDockWidget(title);
    }
    super(native);
  }

  setFeature(flag: DockWidgetFeature, on: boolean): void {
    this.native.setFeature(flag, on);
  }

  features(): number {
    return this.native.features();
  }

  setWidget(widget: QWidget, insertMode=eInsertMode.AutoScrollArea): void {
    if (widget == null) {
      this.native.setWidget(null, insertMode);
    } else {
      this.native.setWidget(widget.native, insertMode);
    }
  }

  takeWidget(): QWidget | null {
    return wrapperCache.getWrapper(this.native.takeWidget()) as QWidget;
  }

  setToggleViewActionMode(mode: eToggleViewActionMode): void {
    this.native.setToggleViewActionMode(mode);
  }

  tabWidget(): CDockWidgetTab {
    return wrapperCache.getWrapper(this.native.tabWidget()) as CDockWidgetTab;
  }

  dockManager(): CDockManager {
    return wrapperCache.getWrapper(this.native.dockManager()) as CDockManager;
  }

  dockContainer(): CDockContainerWidget {
    return wrapperCache.getWrapper(this.native.dockContainer()) as CDockContainerWidget;
  }

  dockAreaWidget(): CDockAreaWidget {
    return wrapperCache.getWrapper(this.native.dockAreaWidget()) as CDockAreaWidget;
  }

  widget(): QWidget {
    return wrapperCache.getWrapper(this.native.widget()) as QWidget;
  }

  isFloating(): boolean {
    return this.native.isFloating();
  }

  isInFloatingContainer(): boolean {
    return this.native.isInFloatingContainer();
  }

  isClosed(): boolean {
    return this.native.isClosed();
  }

  // CLASS: CDockWidget
  // TODO: QAction* toggleViewAction() const

  setMinimumSizeHintMode(mode: eMinimumSizeHintMode): void {
    this.native.setMinimumSizeHintMode(mode);
  }

  // TODO: void setIcon(const QIcon& Icon);
  // TODO: QIcon icon() const;
  // TODO: QToolBar* toolBar() const;
  // TODO: QToolBar* createDefaultToolBar();
  // TODO: void setToolBar(QToolBar* ToolBar /Transfer/ );
  // TODO: void setToolBarStyle(Qt::ToolButtonStyle Style, ads::CDockWidget::eState State);
  // TODO: Qt::ToolButtonStyle toolBarStyle(ads::CDockWidget::eState State) const;
  // TODO: void setToolBarIconSize(const QSize& IconSize, ads::CDockWidget::eState State);
  // TODO: QSize toolBarIconSize(eState State) const;
  // TODO: void setTitleBarActions(QList<QAction*> actions);
  // TODO: virtual QList<QAction*> titleBarActions() const;

  setTabToolTip(text: string): void {
    this.native.setTabToolTip(text);
  }

  isCentralWidget(): boolean {
    return this.native.isCentralWidget();
  }

  isFullScreen(): boolean {
    return this.native.isFullScreen();
  }

  isTabbed(): boolean {
    return this.native.isTabbed();
  }

  isCurrentTab(): boolean {
    return this.native.isCurrentTab();
  }

  toggleView(Open: boolean=true): void {
    this.native.toggleView(Open);
  }

  setAsCurrentTab(): void {
    this.native.setAsCurrentTab();
  }

  setFloating(): void {
    this.native.setFloating();
  }

  deleteDockWidget(): void {
    this.native.deleteDockWidget();
  }

  closeDockWidget(): void {
    this.native.closeDockWidget();
  }
}

wrapperCache.registerWrapper('CDockWidgetWrap', CDockWidget);

export interface CDockWidgetSignals extends QFrameSignals {
  viewToggled: (open: boolean) => void;
  closed: () => void;
  titleChanged: (title: string) => void;
  topLevelChanged: (topLevel: boolean) => void;
  closeRequested: () => void;
  visibilityChanged: (visible: boolean) => void;
  featuresChanged: (features: number /* DockWidgetFeatures */) => void;
}

export enum DockWidgetFeature {
  DockWidgetClosable = 0x001,///< dock widget has a close button
  DockWidgetMovable = 0x002,///< dock widget is movable and can be moved to a new position in the current dock container
  DockWidgetFloatable = 0x004,///< dock widget can be dragged into a floating window
  DockWidgetDeleteOnClose = 0x008, ///< deletes the dock widget when it is closed
  CustomCloseHandling = 0x010, ///< clicking the close button will not close the dock widget but emits the closeRequested() signal instead
  DockWidgetFocusable = 0x020, ///< if this is enabled, a dock widget can get focus highlighting
  DockWidgetForceCloseWithArea = 0x040, ///< dock widget will be closed when the dock area hosting it is closed
  NoTab = 0x080, ///< dock widget tab will never be shown if this flag is set
  DeleteContentOnClose = 0x100, ///< deletes only the contained widget on close, keeping the dock widget intact and in place. Attempts to rebuild the contents widget on show if there is a widget factory set.
  DockWidgetPinnable = 0x200, ///< dock widget can be pinned and added to an auto hide dock container
  DefaultDockWidgetFeatures = DockWidgetClosable | DockWidgetMovable | DockWidgetFloatable | DockWidgetFocusable | DockWidgetPinnable,
  AllDockWidgetFeatures = DefaultDockWidgetFeatures | DockWidgetDeleteOnClose | CustomCloseHandling,
  DockWidgetAlwaysCloseAndDelete = DockWidgetForceCloseWithArea | DockWidgetDeleteOnClose,
  NoDockWidgetFeatures = 0x000
};

export enum eInsertMode {
  AutoScrollArea = 0,
  ForceScrollArea = 1,
  ForceNoScrollArea = 2,
};

export enum eToggleViewActionMode {
  ActionModeToggle = 0, //!< ActionModeToggle
  ActionModeShow = 1    //!< ActionModeShow
};

export enum eMinimumSizeHintMode {
  MinimumSizeHintFromDockWidget = 0,
  MinimumSizeHintFromContent = 1,
};
