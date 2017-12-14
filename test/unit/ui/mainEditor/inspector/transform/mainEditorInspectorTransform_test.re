open Wonder_jest;

open ExpectJs;

external toObject : ReactTestRenderer.t => Js.t({..}) = "%identity";

let _ =
  describe(
    "mainEditor inspector transform component",
    (_) => {
      open Expect;
      open Expect.Operators;
      open Sinon;
      let sandbox = getSandboxDefaultVal();
      beforeEach(
        () => {
          sandbox := createSandbox();
          TestToolEngine.prepare(sandbox)
        }
      );
      afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
      test(
        "create mainEditor inspector transform snapshot",
        (_) => {
          TestToolUI.initMainEditor(sandbox);
          let component =
            ReactTestRenderer.create(
              <MainEditorTransform
                store=AppStore.state
                dispatch=(Reductive.Store.dispatch(IndexStore.store))
              />
            );
          let json = ReactTestRenderer.toJSON(component);
          toMatchSnapshot(expect(json))
        }
      )
    }
  );