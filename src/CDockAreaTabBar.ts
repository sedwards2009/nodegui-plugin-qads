import { checkIfNativeElement, NativeElement, QFrame, QFrameSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';
import { CDockAreaWidget } from './CDockAreaWidget';


export class CDockAreaTabBar extends QFrame<CDockAreaTabBarSignals> {

  constructor(arg?: CDockAreaWidget | NativeElement) {
    let native: NativeElement;
    if (checkIfNativeElement(arg)) {
        native = arg as NativeElement;
    } else if (arg != null) {
        const parent = arg as CDockAreaWidget;
        native = new addon.CDockAreaTabBar(parent.native);
    }
    super(native);
  }
}

wrapperCache.registerWrapper('CDockAreaTabBarWrap', CDockAreaTabBar);

export interface CDockAreaTabBarSignals extends QFrameSignals {

}
