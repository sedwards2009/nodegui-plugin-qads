import { checkIfNativeElement, NativeElement, QWidget, QWidgetSignals, wrapperCache } from '@nodegui/nodegui';
import { CDockContainerWidget, CDockContainerWidgetSignals } from './CDockContainerWidget';
import { CFloatingDockContainer } from './CFloatingDockContainer';
import addon from './addon';
import { CDockAreaWidget, CDockWidget, DockWidgetArea } from './main';


export class CDockManager extends CDockContainerWidget<CDockManagerSignals> {

  constructor(arg?: QWidget<QWidgetSignals> | NativeElement) {
    let native: NativeElement;
    if (checkIfNativeElement(arg)) {
        native = arg as NativeElement;
    } else if (arg != null) {
        const parent = arg as QWidget;
        native = new addon.CDockManager(parent.native);
    } else {
        native = new addon.CDockManager();
    }
    super(native);
  }

  addDockWidgetToContainer(area: DockWidgetArea, dockWidget: CDockWidget,
      dockContainerWidget: CDockContainerWidget): CDockAreaWidget {
    return wrapperCache.getWrapper(this.native.addDockWidgetToContainer(
      area,
      dockWidget.native,
      dockContainerWidget.native)) as CDockAreaWidget;
  }

	// CAutoHideDockContainer* addAutoHideDockWidget(SideBarLocation Location, CDockWidget* Dockwidget);
	// CAutoHideDockContainer* addAutoHideDockWidgetToContainer(SideBarLocation Location,
	// 	CDockWidget* Dockwidget, CDockContainerWidget* DockContainerWidget);

  addDockWidgetTab(area: DockWidgetArea, dockWidget: CDockWidget): CDockAreaWidget {
    return wrapperCache.getWrapper(this.native.addDockWidgetTab(
      area,
      dockWidget.native,
    )) as CDockAreaWidget;
  }

  addDockWidgetTabToArea(dockWidget: CDockWidget, dockAreaWidget: CDockAreaWidget, index = -1): CDockAreaWidget {
    return wrapperCache.getWrapper(this.native.addDockWidgetTabToArea(
      dockWidget.native,
      dockAreaWidget.native,
      index
    )) as CDockAreaWidget;
  }

	addDockWidgetFloating(dockWidget: CDockWidget): CFloatingDockContainer {
    return wrapperCache.getWrapper(this.native.addDockWidgetFloating(
      dockWidget.native)) as CFloatingDockContainer;
  }

  findDockWidget(objectName: string): CDockWidget {
    return wrapperCache.getWrapper(this.native.findDockWidget(objectName)) as CDockWidget;
  }

  centralWidget(): CDockWidget {
    return wrapperCache.getWrapper(this.native.centralWidget()) as CDockWidget;
  }

  setCentralWidget(widget: CDockWidget): CDockAreaWidget {
    return wrapperCache.getWrapper(this.native.setCentralWidget(widget.native)) as CDockAreaWidget;
  }

  static setConfigFlag(flag: eConfigFlag, on: boolean = true): void {
    addon.CDockManager.setConfigFlag(flag, on);
  }
}

wrapperCache.registerWrapper('CDockManagerWrap', CDockManager);

export interface CDockManagerSignals extends CDockContainerWidgetSignals {
  // perspectiveListChanged: () => void;
  // perspectivesRemoved: () => void;
  // restoringState: () => void;
  // stateRestored: () => void;
  // openingPerspective: (const QString& PerspectiveName) => void;
  // perspectiveOpened: (const QString& PerspectiveName) => void;
  floatingWidgetCreated: (floatDockContainer: any /* CFloatingDockContainer */) => void;
  floatingWidgetAboutToBeRemoved: (floatDockContainer: any /* CFloatingDockContainer */) => void;
  floatingWidgetAboutToBeDestroyed: (floatDockContainer: any /* CFloatingDockContainer */) => void;
  dockAreaCreated: (dockAreaWidget: any /* CDockAreaWidget */) => void;
  dockWidgetAdded: (dockWidget: any /* ads::CDockWidget* */) => void;
  dockWidgetAboutToBeRemoved: (dockWidget: any /* ads::CDockWidget* */) => void;
  dockWidgetRemoved: (dockWidget: any /* ads::CDockWidget */) => void;
  focusedDockWidgetChanged: (dockWidget: any /* ads::CDockWidget* */, dockWidget2: any /* ads::CDockWidget */) => void;
}

export enum eConfigFlag {
  ActiveTabHasCloseButton = 0x0001,    //!< If this flag is set, the active tab in a tab area has a close button
  DockAreaHasCloseButton = 0x0002,     //!< If the flag is set each dock area has a close button
  DockAreaCloseButtonClosesTab = 0x0004,//!< If the flag is set, the dock area close button closes the active tab, if not set, it closes the complete dock area
  OpaqueSplitterResize = 0x0008, //!< See QSplitter::setOpaqueResize() documentation
  XmlAutoFormattingEnabled = 0x0010,//!< If enabled, the XML writer automatically adds line-breaks and indentation to empty sections between elements (ignorable whitespace).
  XmlCompressionEnabled = 0x0020,//!< If enabled, the XML output will be compressed and is not human readable anymore
  TabCloseButtonIsToolButton = 0x0040,//! If enabled the tab close buttons will be QToolButtons instead of QPushButtons - disabled by default
  AllTabsHaveCloseButton = 0x0080, //!< if this flag is set, then all tabs that are closable show a close button
  RetainTabSizeWhenCloseButtonHidden = 0x0100, //!< if this flag is set, the space for the close button is reserved even if the close button is not visible
  DragPreviewIsDynamic = 0x0400,///< If opaque undocking is disabled, this flag defines the behavior of the drag preview window, if this flag is enabled, the preview will be adjusted dynamically to the drop area
  DragPreviewShowsContentPixmap = 0x0800,///< If opaque undocking is disabled, the created drag preview window shows a copy of the content of the dock widget / dock are that is dragged
  DragPreviewHasWindowFrame = 0x1000,///< If opaque undocking is disabled, then this flag configures if the drag preview is frameless or looks like a real window
  AlwaysShowTabs = 0x2000,///< If this option is enabled, the tab of a dock widget is always displayed - even if it is the only visible dock widget in a floating widget.
  DockAreaHasUndockButton = 0x4000,     //!< If the flag is set each dock area has an undock button
  DockAreaHasTabsMenuButton = 0x8000,     //!< If the flag is set each dock area has a tabs menu button
  DockAreaHideDisabledButtons = 0x10000,    //!< If the flag is set disabled dock area buttons will not appear on the toolbar at all (enabling them will bring them back)
  DockAreaDynamicTabsMenuButtonVisibility = 0x20000, //!< If the flag is set, the tabs menu button will be shown only when it is required - that means, if the tabs are elided. If the tabs are not elided, it is hidden
  FloatingContainerHasWidgetTitle = 0x40000, //!< If set, the Floating Widget window title reflects the title of the current dock widget otherwise it displays the title set with `CDockManager::setFloatingContainersTitle` or application name as window title
  FloatingContainerHasWidgetIcon = 0x80000, //!< If set, the Floating Widget icon reflects the icon of the current dock widget otherwise it displays application icon
  HideSingleCentralWidgetTitleBar = 0x100000, //!< If there is only one single visible dock widget in the main dock container (the dock manager) and if this flag is set, then the titlebar of this dock widget will be hidden
                                              //!< this only makes sense for non draggable and non floatable widgets and enables the creation of some kind of "central" widget

  FocusHighlighting = 0x200000, //!< enables styling of focused dock widget tabs or floating widget titlebar
  EqualSplitOnInsertion = 0x400000, ///!< if enabled, the space is equally distributed to all widgets in a  splitter

  FloatingContainerForceNativeTitleBar = 0x800000, //!< Linux only ! Forces all FloatingContainer to use the native title bar. This might break docking for FloatinContainer on some Window Managers (like Kwin/KDE).
                           //!< If neither this nor FloatingContainerForceCustomTitleBar is set (the default) native titlebars are used except on known bad systems.
                           //! Users can overwrite this by setting the environment variable ADS_UseNativeTitle to "1" or "0".
      FloatingContainerForceQWidgetTitleBar = 0x1000000,//!< Linux only ! Forces all FloatingContainer to use a QWidget based title bar.
                           //!< If neither this nor FloatingContainerForceNativeTitleBar is set (the default) native titlebars are used except on known bad systems.
                           //! Users can overwrite this by setting the environment variable ADS_UseNativeTitle to "1" or "0".
  MiddleMouseButtonClosesTab = 0x2000000, //! If the flag is set, the user can use the mouse middle button to close the tab under the mouse
  FloatingContainerIndependent = 0x4000000,	//! Treat floating containers as independent windows

  DockWidgetTabContextMenu = 0x8000000,	//! Show context menu on tabs
  DockWidgetTabTitle = 0x10000000,		//! Show the tab label text

  DefaultDockAreaButtons = DockAreaHasCloseButton
            | DockAreaHasUndockButton
                      | DockAreaHasTabsMenuButton, ///< default configuration of dock area title bar buttons

  DefaultBaseConfig = DefaultDockAreaButtons
                    | ActiveTabHasCloseButton
                    | XmlCompressionEnabled
                    | FloatingContainerHasWidgetTitle, ///< default base configuration settings

  DefaultOpaqueConfig = DefaultBaseConfig
                  | OpaqueSplitterResize
                  | DragPreviewShowsContentPixmap, ///< the default configuration for non opaque operations

  DefaultNonOpaqueConfig = DefaultBaseConfig
                | DragPreviewShowsContentPixmap, ///< the default configuration for non opaque operations

  NonOpaqueWithWindowFrame = DefaultNonOpaqueConfig
                | DragPreviewHasWindowFrame ///< the default configuration for non opaque operations that show a real window with frame
};
