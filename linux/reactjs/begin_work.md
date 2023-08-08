```javascript
let didReceiveUpdate = false;

function beginWork(
  current: Fiber | null,
  workInProgress: Fiber,
  renderLanes: Lanes,
): Fiber | null {
  
  if (current !== null) {
    const oldProps = current.memoizedProps;
    const newProps = workInProgress.pendingProps;

    if (oldProps !== newProps) {
      // If props changed, mark the fiber as having performed work.
      didReceiveUpdate = true;
    } else {
      // Check if there's a pending update or context change.
      const hasScheduledUpdateOrContext = checkScheduledUpdateOrContext(
        current,
        renderLanes,
      );
      if (!hasScheduledUpdateOrContext) {
        // No pending updates or context. Bail out now.
        didReceiveUpdate = false;
        return attemptEarlyBailoutIfNoScheduledUpdate(
          current,
          workInProgress,
          renderLanes,
        );
      }
      didReceiveUpdate = false;
    }
  } else {
    didReceiveUpdate = false;
  }

  switch (workInProgress.tag) {
    case IndeterminateComponent: {
      return mountIndeterminateComponent(
        current,
        workInProgress,
        workInProgress.type,
        renderLanes,
      );
    }
    case FunctionComponent: {
      const Component = workInProgress.type;
      const unresolvedProps = workInProgress.pendingProps;
      const resolvedProps =
        workInProgress.elementType === Component
          ? unresolvedProps
          : resolveDefaultProps(Component, unresolvedProps);
      return updateFunctionComponent(
        current,
        workInProgress,
        Component,
        resolvedProps,
        renderLanes,
      );
    }
    case HostRoot:
      return updateHostRoot(current, workInProgress, renderLanes);
    case HostComponent:
      return updateHostComponent(current, workInProgress, renderLanes);
  }
}
```

```javascript

function updateHostRoot(
  current: Fiber,
  workInProgress: Fiber,
  renderLanes: Lanes,
) {
  const nextProps = workInProgress.pendingProps;
  const prevState = workInProgress.memoizedState;
  const prevChildren = prevState.element;
  cloneUpdateQueue(current, workInProgress);
  processUpdateQueue(workInProgress, nextProps, null, renderLanes);
  const nextState: RootState = workInProgress.memoizedState;
  const nextChildren = nextState.element;

  if (nextChildren === prevChildren) {
    return bailoutOnAlreadyFinishedWork(current, workInProgress, renderLanes);
  }
  reconcileChildren(current, workInProgress, nextChildren, renderLanes);
  // REWRITE
  // workInProgress.child = reconcileChildFibers(
  //   returnFiber=workInProgress,
  //   currentFirstChild=current.child,
  //   newChild=nextChildren,
  //   renderLanes,
  // );
  return workInProgress.child;
}
```

```javascript

function mountIndeterminateComponent(
  _current: null | Fiber,
  workInProgress: Fiber,
  Component: $FlowFixMe,
  renderLanes: Lanes,
) {
  const props = workInProgress.pendingProps;
  let value = renderWithHooks(
    current=null,
    workInProgress,
    Component,
    props,
    secondArgs=context,
    renderLanes,
  );
  let hasId = checkDidRenderIdHook();
  
  if (// Run these checks in production only if the flag is off.
    // Eventually we'll delete this branch altogether.
    !disableModulePatternComponents &&
    typeof value === 'object' &&
    value !== null &&
    typeof value.render === 'function' &&
    value.$$typeof === undefined
  ) {
    // Proceed under the assumption that this is a class instance
    // ...
  } else {
    // Proceed under the assumption that this is a function component
    workInProgress.tag = FunctionComponent;
    reconcileChildren(current=null, workInProgress, nextChildren=value, renderLanes);
    // REWRITE
    // workInProgress.child = mountChildFibers(
    //   returnFiber=workInProgress,
    //   currentFirstChild=null,
    //   newChild=value,
    //   renderLanes,
    // );
    return workInProgress.child;
  }
}
```