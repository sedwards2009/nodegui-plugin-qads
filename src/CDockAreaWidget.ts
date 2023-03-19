import { checkIfNativeElement, NativeElement, QFrame, QFrameSignals, QWidget, QWidgetSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';
import { CDockAreaTitleBar, DockWidgetArea } from './main';


export class CDockAreaWidget extends QFrame<CDockAreaWidgetSignals> {

  constructor(titleOrNative: string | NativeElement, arg?: QWidget<QWidgetSignals>) {
    let native: NativeElement;
    if (checkIfNativeElement(titleOrNative)) {
        native = titleOrNative as NativeElement;
    } else {
      const title: string = titleOrNative;
      if (arg != null) {
          const parent = arg as QWidget;
          native = new addon.CDockAreaWidget(title, parent.native);
      } else {
          native = new addon.CDockAreaWidget(title);
      }
    }
    super(native);
  }

  setAllowedAreas(areas: DockWidgetArea): void {
    this.native.setAllowedAreas(areas);
  }

  titleBar(): CDockAreaTitleBar {
    return wrapperCache.getWrapper(this.native.titleBar()) as CDockAreaTitleBar;
  }
}

wrapperCache.registerWrapper('CDockAreaWidgetWrap', CDockAreaWidget);

export interface CDockAreaWidgetSignals extends QFrameSignals {
  tabBarClicked: (index: number) => void;
  currentChanging: (index: number) => void;
  currentChanged: (index: number) => void;
  viewToggled: (open: boolean) => void;
}
