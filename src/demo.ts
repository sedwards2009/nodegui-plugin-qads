import { QMainWindow, QLabel, AlignmentFlag, QCalendarWidget, QToolButton } from '@nodegui/nodegui';
import { CDockManager, CDockContainerWidget, CDockWidget, eConfigFlag, DockWidgetFeature, eToggleViewActionMode, DockWidgetArea } from './main';

class Demo {

  #window: QMainWindow = null;
  #dockManager: CDockManager = null;
  #labelCount = 0;
  #calendarCount = 0;
  #windowTitleTestDockWidget: CDockWidget = null;

  run(): void {
    this.#window = new QMainWindow();
    this.#window.setWindowTitle('Qt Advanced Docking System Demo');

    CDockManager.setConfigFlag(eConfigFlag.FocusHighlighting, true);

    this.#dockManager = new CDockManager(this.#window);

    const dockWidget = this.#createLongTextLabelDockWidget();
    // self.window_title_test_dock_widget = dock_widget
    dockWidget.setFeature(DockWidgetFeature.DockWidgetFocusable, false);

    this.#createContent();

    this.#window.show();
  }

  #createContent(): void {
    const dockWidget = this.#createCalendarDockWidget();
    dockWidget.setFeature(DockWidgetFeature.DockWidgetClosable, false);
    const specialDockArea = this.#dockManager.addDockWidget(DockWidgetArea.LeftDockWidgetArea, dockWidget);
    specialDockArea.setAllowedAreas(DockWidgetArea.OuterDockAreas);

    const dockWidget2 = this.#createLongTextLabelDockWidget();
    this.#windowTitleTestDockWidget = dockWidget2;
    dockWidget2.setFeature(DockWidgetFeature.DockWidgetFocusable, false);
    this.#dockManager.addDockWidget(DockWidgetArea.LeftDockWidgetArea, dockWidget2);

    const fileSystemWidget = this.#createFileSystemTreeDockWidget();
    // const toolBar = fileSystemWidget.createDefaultToolBar();
    // toolBar.addAction(self.actionSaveState)
    // toolBar.addAction(self.actionRestoreState)
    fileSystemWidget.setFeature(DockWidgetFeature.DockWidgetFloatable, false);
    append_feature_string_to_window_title(fileSystemWidget);
    this.#dockManager.addDockWidget(DockWidgetArea.BottomDockWidgetArea, fileSystemWidget)

    const fileSystemWidget2 = this.#createFileSystemTreeDockWidget();
    fileSystemWidget2.setFeature(DockWidgetFeature.DockWidgetMovable, false);
    fileSystemWidget2.setFeature(DockWidgetFeature.DockWidgetFloatable, false);
    append_feature_string_to_window_title(fileSystemWidget2);

    // CDockComponentsFactory.setFactory(CCustomComponentsFactory())
    const topDockArea = this.#dockManager.addDockWidget(DockWidgetArea.TopDockWidgetArea, fileSystemWidget2);

    const dockWidget3 = this.#createCalendarDockWidget();
    dockWidget3.setTabToolTip("Tab ToolTip\nHodie est dies magna");
    const dockArea = this.#dockManager.addDockWidget(DockWidgetArea.CenterDockWidgetArea, dockWidget3, topDockArea);

    const customButton = new QToolButton(dockArea);
    customButton.setText("Create Editor");
    customButton.setToolTip("Create Editor");
    customButton.setAutoRaise(true);

    const titleBar = dockArea.titleBar();
    const index = titleBar.indexOf(titleBar.tabBar());
    titleBar.insertWidget(index + 1, customButton);

    customButton.addEventListener('clicked', () => {
      const dockWidget = this.#createFileSystemTreeDockWidget();
      dockWidget.setFeature(DockWidgetFeature.DockWidgetDeleteOnClose, true);
      this.#dockManager.addDockWidgetTabToArea(dockWidget, dockArea);
      // dockWidget.addEventListener('closeRequested', () => {
      //   // self.on_editor_close_requested
      // });
    });

    // Test dock area docking
    const rightDockArea = this.#dockManager.addDockWidget(
      DockWidgetArea.RightDockWidgetArea,
      this.#createLongTextLabelDockWidget(), topDockArea);
    this.#dockManager.addDockWidget(
      DockWidgetArea.TopDockWidgetArea,
      this.#createLongTextLabelDockWidget(), rightDockArea)

    const bottomDockArea = this.#dockManager.addDockWidget(
      DockWidgetArea.BottomDockWidgetArea,
        this.#createLongTextLabelDockWidget(), rightDockArea)

    this.#dockManager.addDockWidget(
      DockWidgetArea.CenterDockWidgetArea,
        this.#createLongTextLabelDockWidget(), rightDockArea)
    this.#dockManager.addDockWidget(
      DockWidgetArea.CenterDockWidgetArea,
        this.#createLongTextLabelDockWidget(), bottomDockArea)
  }

  #createLongTextLabelDockWidget(): CDockWidget {
    const label = new QLabel();
    label.setWordWrap(true);
    label.setAlignment(AlignmentFlag.AlignTop | AlignmentFlag.AlignLeft);
    label.setText(`Label ${this.#labelCount} ${Date.now()} - Lorem ipsum dolor sit amet, consectetuer
  adipiscing elit.  Aenean commodo ligula eget dolor. Aenean massa. Cum
  sociis natoque penatibus et magnis dis parturient montes, nascetur
  ridiculus mus.  Donec quam felis, ultricies nec, pellentesque eu, pretium
  quis, sem.  Nulla consequat massa quis enim. Donec pede justo, fringilla
  vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut,
  imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis
  pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi.
  Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu,
  consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra
  quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet.
    `);
    const dockWidget = new CDockWidget(`Label ${this.#labelCount}`);
    this.#labelCount++;
    dockWidget.setWidget(label);

    // self.menuView.addAction(dock_widget.toggleViewAction())
    return dockWidget
  }

  #createCalendarDockWidget(): CDockWidget {
    const widget = new QCalendarWidget();

    const dock_widget = new CDockWidget(`Calendar ${this.#calendarCount}`);
    this.#calendarCount++;

    // The following lines are for testing the setWidget() and takeWidget()
    // functionality

    dock_widget.setWidget(widget);
    dock_widget.setWidget(widget);   // what happens if we set a widget if a widget is already set
    dock_widget.takeWidget();        // we remove the widget
    dock_widget.setWidget(widget);   // and set the widget again - there should be no error
    dock_widget.setToggleViewActionMode(eToggleViewActionMode.ActionModeShow);
    // dock_widget.setIcon(svg_icon(":/adsdemo/images/date_range.svg"))
    // self.menuView.addAction(dock_widget.toggleViewAction())
    return dock_widget;
  }

  #createFileSystemTreeDockWidget(): CDockWidget {
    const label = new QLabel();
    label.setWordWrap(true);
    label.setAlignment(AlignmentFlag.AlignTop | AlignmentFlag.AlignLeft);
    label.setText(`Label ${this.#labelCount} ${Date.now()}
    * one
    * two
    * three
    `);
    const dockWidget = new CDockWidget(`List Label ${this.#labelCount}`);
    this.#labelCount++;
    dockWidget.setWidget(label);
    return dockWidget
  }
}

function features_string(dockWidget: CDockWidget): string {
    const f = dockWidget.features();
    const closable = f & DockWidgetFeature.DockWidgetClosable;
    const movable = f & DockWidgetFeature.DockWidgetMovable;
    const floatable = f & DockWidgetFeature.DockWidgetFloatable;

    return `c${closable ? '+' : '-'} m${movable ? '+' : '-'} f${floatable ? '+' : '-'}`;
}

function append_feature_string_to_window_title(dock_widget: CDockWidget): void {
    dock_widget.setWindowTitle(dock_widget.windowTitle() + ` (${features_string(dock_widget)})`)
}

const demo = new Demo();
demo.run();
(global as any).demo = demo;
