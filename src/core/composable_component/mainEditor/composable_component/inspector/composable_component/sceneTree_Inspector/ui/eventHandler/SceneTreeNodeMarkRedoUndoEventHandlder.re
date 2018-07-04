open AppStore;
open DiffType;

module MarkRedoUndoEventHandler = {
  include EmptyEventHandler.EmptyEventHandler;
  type prepareTuple = Wonderjs.GameObjectType.gameObject;
  type dataTuple = string;
  let onMarkRedoUndoByStackLastReturnStore =
      ((store, dispatchFunc), gameObject, newName) => {
    GameObjectEngineService.setGameObjectName(newName)
    |> StateLogicService.getAndRefreshEngineStateWithDiff([|
         {arguments: [|gameObject|], type_: GameObject},
       |]);

    let newSceneGraphData =
      store
      |> SceneTreeUtils.unsafeGetSceneGraphDataFromStore
      |> SceneTreeUtils.renameSceneGraphData(gameObject, newName);

    dispatchFunc(
      AppStore.SceneTreeAction(SetSceneGraph(Some(newSceneGraphData))),
    )
    |> ignore;
    {
      ...store,
      sceneTreeState: {
        ...store.sceneTreeState,
        sceneGraphData: newSceneGraphData |. Some,
      },
    };
  };
};

module MakeEventHandler =
  EventHandler.MakeEventHandler(MarkRedoUndoEventHandler);