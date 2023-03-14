import { checkIfNativeElement, NativeElement, QFrame, QFrameSignals, QWidget, QWidgetSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';
import { CDockAreaWidget } from './CDockAreaWidget';


export class CDockAreaTitleBar extends QFrame<CDockAreaTitleBarSignals> {

  constructor(arg?: CDockAreaWidget | NativeElement) {
    let native: NativeElement;
    if (checkIfNativeElement(arg)) {
        native = arg as NativeElement;
    } else if (arg != null) {
        const parent = arg as CDockAreaWidget;
        native = new addon.CDockAreaTitleBar(parent.native);
    }
    super(native);
  }
}

wrapperCache.registerWrapper('CDockAreaTitleBarWrap', CDockAreaTitleBar);

export interface CDockAreaTitleBarSignals extends QFrameSignals {

}
