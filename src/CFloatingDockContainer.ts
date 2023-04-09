import { checkIfNativeElement, NativeElement, QFrame, QFrameSignals, QWidget, QWidgetSignals, wrapperCache } from '@nodegui/nodegui';
import { CDockContainerWidget } from './CDockContainerWidget';
import { CDockWidget } from './CDockWidget';


export class CFloatingDockContainer extends QWidget<CFloatingDockContainerSignals> {

  constructor(arg?: NativeElement) {
    let native: NativeElement;
    if (checkIfNativeElement(arg)) {
        native = arg as NativeElement;
    }
    super(native);
  }

  dockContainer(): CDockContainerWidget {
    return wrapperCache.getWrapper(this.native.dockContainer()) as CDockContainerWidget;
  }

  isClosable(): boolean {
    return this.native.isClosable();
  }

  hasTopLevelDockWidget(): boolean {
    return this.native.hasTopLevelDockWidget();
  }

  topLevelDockWidget(): CDockWidget {
    return wrapperCache.getWrapper(this.native.centralWidget()) as CDockWidget;
  }

  dockWidgets(): CDockWidget[] {
    return this.native.dockWidgets().map((area: any) => wrapperCache.getWrapper(area));
  }
}

wrapperCache.registerWrapper('CFloatingDockContainerWrap', CFloatingDockContainer);

export interface CFloatingDockContainerSignals extends QFrameSignals {
}
