

import * as Block from "../../../../../../../../node_modules/bs-platform/lib/es6/block.js";
import * as Curry from "../../../../../../../../node_modules/bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as ReasonReact from "../../../../../../../../node_modules/reason-react/lib/es6_global/src/ReasonReact.js";
import * as Modal$WonderEditor from "../../../../atom_component/modal/Modal.js";
import * as Copyright$WonderEditor from "../../../../../Copyright.js";
import * as DomHelper$WonderEditor from "../../../../external/DomHelper.js";
import * as LocalStorage$WonderEditor from "../../../../external/LocalStorage.js";

function getWelComeUserKey(param) {
  return "welcomeUser";
}

function getVersionKey(param) {
  return "version";
}

function buildWelComeUserModalContent(param) {
  return /* array */[
          React.createElement("div", {
                key: "text1",
                className: "content-text"
              }, DomHelper$WonderEditor.textEl(" 欢迎来到Wonder，你可以通过访问我们的"), React.createElement("a", {
                    href: "http://www.wonder-3d.com/",
                    target: "view_window"
                  }, DomHelper$WonderEditor.textEl("官方网站")), DomHelper$WonderEditor.textEl(" , 查看我们能为你提供什么服务")),
          React.createElement("div", {
                key: "text2",
                className: "content-white"
              }),
          React.createElement("div", {
                key: "text3",
                className: "content-text"
              }, DomHelper$WonderEditor.textEl("Wonder 科技为你服务"))
        ];
}

var Method = /* module */[
  /* getWelComeUserKey */getWelComeUserKey,
  /* getVersionKey */getVersionKey,
  /* buildWelComeUserModalContent */buildWelComeUserModalContent
];

var component = ReasonReact.reducerComponent("HeaderNotice");

function reducer(action, state) {
  return /* Update */Block.__(0, [/* record */[
              /* isShowWelComeUserModal */false,
              /* isShowVersionUpgradeModal */false
            ]]);
}

function render(param, param$1) {
  var send = param$1[/* send */3];
  var state = param$1[/* state */1];
  var match = state[/* isShowWelComeUserModal */0];
  var tmp;
  if (match) {
    tmp = ReasonReact.element(undefined, undefined, Modal$WonderEditor.make("Welcome to Wonder", buildWelComeUserModalContent(/* () */0), (function (param) {
                return Curry._1(send, /* HideWelComeUserModal */0);
              }), undefined, /* array */[]));
  } else {
    var match$1 = state[/* isShowVersionUpgradeModal */1];
    tmp = match$1 ? ReasonReact.element(undefined, undefined, Modal$WonderEditor.make("Version Upgrade", buildWelComeUserModalContent(/* () */0), (function (param) {
                  return Curry._1(send, /* HideVersionUpgradeModal */1);
                }), undefined, /* array */[])) : null;
  }
  return React.createElement("div", {
              className: "header-item"
            }, tmp);
}

function make(uiState, dispatchFunc, _children) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return render(/* tuple */[
                          uiState,
                          dispatchFunc
                        ], self);
            }),
          /* initialState */(function (param) {
              var match = LocalStorage$WonderEditor.getValue("welcomeUser");
              var match$1 = LocalStorage$WonderEditor.getValue("version");
              var tmp;
              if (match$1 !== undefined) {
                var match$2 = match$1 === Copyright$WonderEditor.getVersion(/* () */0);
                if (match$2) {
                  tmp = false;
                } else {
                  LocalStorage$WonderEditor.setValue("version", Copyright$WonderEditor.getVersion(/* () */0));
                  tmp = true;
                }
              } else {
                LocalStorage$WonderEditor.setValue("version", Copyright$WonderEditor.getVersion(/* () */0));
                tmp = true;
              }
              return /* record */[
                      /* isShowWelComeUserModal */match !== undefined ? match !== "ok" : (LocalStorage$WonderEditor.setValue("welcomeUser", "ok"), true),
                      /* isShowVersionUpgradeModal */tmp
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */reducer,
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

export {
  Method ,
  component ,
  reducer ,
  render ,
  make ,
  
}
/* component Not a pure module */