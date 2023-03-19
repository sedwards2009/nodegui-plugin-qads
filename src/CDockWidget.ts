import { checkIfNativeElement, NativeElement, QFrame, QFrameSignals, QWidget, QWidgetSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';


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

  setTabToolTip(tip: string): void {
    this.native.setTabToolTip(tip);
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
