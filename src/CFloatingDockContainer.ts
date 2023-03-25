import { checkIfNativeElement, NativeElement, QFrame, QFrameSignals, QWidget, QWidgetSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';


export class CFloatingDockContainer extends QWidget<CFloatingDockContainerSignals> {

  constructor(arg?: NativeElement) {
    let native: NativeElement;
    if (checkIfNativeElement(arg)) {
        native = arg as NativeElement;
    }
    super(native);
  }
}

wrapperCache.registerWrapper('CFloatingDockContainerWrap', CFloatingDockContainer);

export interface CFloatingDockContainerSignals extends QFrameSignals {
}
