```javascript
function commitMutationEffectsOnFiber(
  finishedWork: Fiber,
  root: FiberRoot,
  lanes: Lanes,
) {
  const current = finishedWork.alternate;
  const flags = finishedWork.flags;

  switch (finishedWork.tag) {
    case FunctionComponent: {
      recursivelyTraverseMutationEffects(root, finishedWork, lanes);
      commitReconciliationEffects(finishedWork);
      return;
    }
    case HostComponent: {
      recursivelyTraverseMutationEffects(root, finishedWork, lanes);
      commitReconciliationEffects(finishedWork);

      if (flags & Update) {
        const instance: Instance = finishedWork.stateNode;
        if (instance != null) {
          const newProps = finishedWork.memoizedProps;
          const oldProps = current !== null ? current.memoizedProps : newProps;
          const type = finishedWork.type;
          const updatePayload: null | UpdatePayload = finishedWork.updateQueue;
          finishedWork.updateQueue = null;
          if (updatePayload !== null) {
              commitUpdate(
                instance,
                updatePayload,
                type,
                oldProps,
                newProps,
                finishedWork,
              );
          }
        }
      }      
      return;
    }
    case HostRoot: {
      recursivelyTraverseMutationEffects(root, finishedWork, lanes);
      commitReconciliationEffects(finishedWork);
      return;
    }
  }
}
```

```javascript
function recursivelyTraverseMutationEffects(
  root: FiberRoot,
  parentFiber: Fiber,
  lanes: Lanes,
) {
  const deletions = parentFiber.deletions;
  if (deletions !== null) {
    for (let i = 0; i < deletions.length; i++) {
      const childToDelete = deletions[i];
      try {
        commitDeletionEffects(root, parentFiber, childToDelete);
      } catch (error) {
        captureCommitPhaseError(childToDelete, parentFiber, error);
      }
    }
  }

  if (parentFiber.subtreeFlags & MutationMask) {
    let child = parentFiber.child;
    while (child !== null) {
      commitMutationEffectsOnFiber(child, root, lanes);
      child = child.sibling;
    }
  }
}
```

```javascript
function commitReconciliationEffects(finishedWork: Fiber) {
  const flags = finishedWork.flags;
  // Placement effects (insertions, reorders) can be scheduled on any fiber
  // type. They needs to happen after the children effects have fired, but
  // before the effects on this fiber have fired.
  if (flags & Placement) {
    commitPlacement(finishedWork);
    finishedWork.flags &= ~Placement;
  }
}
```

```javascript
function commitPlacement(finishedWork: Fiber): void {
  // HostComponent | HostRoot
  const parentFiber = getHostParentFiber(finishedWork);

  switch (parentFiber.tag) {
    case HostComponent: {
      const parent: Instance = parentFiber.stateNode;
      const before = getHostSibling(finishedWork);
      insertOrAppendPlacementNode(finishedWork, before, parent);
      break;
    }
    case HostRoot: {
      const parent: Container = parentFiber.stateNode.containerInfo;
      const before = getHostSibling(finishedWork);
      insertOrAppendPlacementNodeIntoContainer(finishedWork, before, parent);
      break;
    }
  }
}

function insertOrAppendPlacementNode(
  node: Fiber,
  parent: Instance,
): void {
  const {tag} = node;
  if (tag === HostComponent) {
    const stateNode = node.stateNode;
    parent.appendChild(stateNode);
  } else {
    const child = node.child;
    if (child !== null) {
      insertOrAppendPlacementNode(child, before, parent);
      let sibling = child.sibling;
      while (sibling !== null) {
        insertOrAppendPlacementNode(sibling, before, parent);
        sibling = sibling.sibling;
      }
    }
  }
}

function insertOrAppendPlacementNodeIntoContainer(
  node: Fiber,
  parent: Container,
): void {
  const {tag} = node;
  if (tag === HostComponent) {
    const stateNode = node.stateNode;
    parent.appendChild(stateNode);
  } else {
    const child = node.child;
    if (child !== null) {
      insertOrAppendPlacementNodeIntoContainer(child, before, parent);
      let sibling = child.sibling;
      while (sibling !== null) {
        insertOrAppendPlacementNodeIntoContainer(sibling, before, parent);
        sibling = sibling.sibling;
      }
    }
  }
}
```

### On initial mount

```javascript
function commitMutationEffectsOnFiber(
  finishedWork: Fiber,
  root: FiberRoot,
  lanes: Lanes,
) {
  recursivelyTraverseMutationEffects(root, finishedWork, lanes);
  commitReconciliationEffects(finishedWork);
}

function recursivelyTraverseMutationEffects(
  root: FiberRoot,
  parentFiber: Fiber,
  lanes: Lanes,
) {
  if (parentFiber.subtreeFlags & MutationMask) {
    let child = parentFiber.child;
    while (child !== null) {
      commitMutationEffectsOnFiber(child, root, lanes);
      child = child.sibling;
    }
  }
}

function commitReconciliationEffects(finishedWork: Fiber) {
    commitPlacement(finishedWork);
}

// more ...

function commitMutationEffectsOnFiber(
  finishedWork: Fiber,
  root: FiberRoot,
  lanes: Lanes,
) {
  if (finishedWork.subtreeFlags & MutationMask) {
    let child = finishedWork.child;
    while (child !== null) {
      commitMutationEffectsOnFiber(child, root, lanes);
      child = child.sibling;
    }
  }
  commitPlacement(finishedWork);
}

function commitPlacement(finishedWork: Fiber): void {
  // HostComponent | HostRoot
  const parentFiber = getHostParentFiber(finishedWork);
  let parent;
  switch (parentFiber.tag) {
    case HostComponent: {
      parent: Instance = parentFiber.stateNode;
      break;
    }
    case HostRoot: {
      parent: Container = parentFiber.stateNode.containerInfo;
      break;
    }
  }
  insertOrAppendPlacementNode(finishedWork, parent);
}

// even more ...

function commitMutationEffectsOnFiber(
  finishedWork: Fiber,
  root: FiberRoot,
  lanes: Lanes,
) {
  if (finishedWork.subtreeFlags & MutationMask) {
    let child = finishedWork.child;
    while (child !== null) {
      commitMutationEffectsOnFiber(child, root, lanes);
      child = child.sibling;
    }
  }

  const parentFiber = getHostParentFiber(finishedWork);

  let parent;
  switch (parentFiber.tag) {
    case HostComponent: {
      parent: Instance = parentFiber.stateNode;
      break;
    }
    case HostRoot: {
      parent: Container = parentFiber.stateNode.containerInfo;
      break;
    }
  }
  insertOrAppendPlacementNode(finishedWork, parent);
}

function insertOrAppendPlacementNode(
  node: Fiber,
  parent: Instance,
): void {
  const {tag} = node;
  if (tag === HostComponent) {
    const stateNode = node.stateNode;
    parent.appendChild(stateNode);
  } else {
    const child = node.child;
    if (child !== null) {
      insertOrAppendPlacementNode(child, parent);
      let sibling = child.sibling;
      while (sibling !== null) {
        insertOrAppendPlacementNode(sibling, parent);
        sibling = sibling.sibling;
      }
    }
  }
}
```

### on update without deletions and placement effects

```javascript
function commitMutationEffectsOnFiber(
  finishedWork: Fiber,
  root: FiberRoot,
  lanes: Lanes,
) {
  const current = finishedWork.alternate;
  const flags = finishedWork.flags;

  switch (finishedWork.tag) {
    case HostRoot:
    case FunctionComponent: {
      recursivelyTraverseMutationEffects(root, finishedWork, lanes);
      commitReconciliationEffects(finishedWork);
      return;
    }
    case HostComponent: {
      recursivelyTraverseMutationEffects(root, finishedWork, lanes);
      commitReconciliationEffects(finishedWork);

      if (flags & Update) {
        const instance: Instance = finishedWork.stateNode;
        if (instance != null) {
          const newProps = finishedWork.memoizedProps;
          const oldProps = current !== null ? current.memoizedProps : newProps;
          const type = finishedWork.type;
          const updatePayload: null | UpdatePayload = finishedWork.updateQueue;
          finishedWork.updateQueue = null;
          if (updatePayload !== null) {
              commitUpdate(
                instance,
                updatePayload,
                type,
                oldProps,
                newProps,
                finishedWork,
              );
          }
        }
      }      
      return;
    }
  }
}

function recursivelyTraverseMutationEffects(
  root: FiberRoot,
  parentFiber: Fiber,
  lanes: Lanes,
) {
  if (parentFiber.subtreeFlags & MutationMask) {
    let child = parentFiber.child;
    while (child !== null) {
      commitMutationEffectsOnFiber(child, root, lanes);
      child = child.sibling;
    }
  }
}

function commitReconciliationEffects(finishedWork: Fiber) {
  const flags = finishedWork.flags;
  // if (flags & Placement) {
  //   commitPlacement(finishedWork);
  //   finishedWork.flags &= ~Placement;
  // }
}

// more ...

function commitMutationEffectsOnFiber(
  finishedWork: Fiber,
  root: FiberRoot,
  lanes: Lanes,
) {
  const current = finishedWork.alternate;
  const flags = finishedWork.flags;

  switch (finishedWork.tag) {
    case HostRoot:
    case FunctionComponent: {
      if (finishedWork.subtreeFlags & MutationMask) {
        let child = finishedWork.child;
        while (child !== null) {
          commitMutationEffectsOnFiber(child, root, lanes);
          child = child.sibling;
        }
      }
      return;
    }
    case HostComponent: {
      if (finishedWork.subtreeFlags & MutationMask) {
        let child = finishedWork.child;
        while (child !== null) {
          commitMutationEffectsOnFiber(child, root, lanes);
          child = child.sibling;
        }
      }

      if (flags & Update) {
        const instance: Instance = finishedWork.stateNode;
        if (instance != null) {
          const newProps = finishedWork.memoizedProps;
          const oldProps = current !== null ? current.memoizedProps : newProps;
          const type = finishedWork.type;
          const updatePayload: null | UpdatePayload = finishedWork.updateQueue;
          finishedWork.updateQueue = null;
          if (updatePayload !== null) {
              commitUpdate(
                instance,
                updatePayload,
                type,
                oldProps,
                newProps,
                finishedWork,
              );
          }
        }
      }      
      return;
    }
  }
}
```